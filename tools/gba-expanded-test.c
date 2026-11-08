/* Standalone regression checks, linked against a host libmgba build.
 * Pass a 64 MiB ROM path to also check the default expanded-memory mode.
 * No commercial ROM or save data is embedded in this test. */
#include <mgba/core/core.h>
#include <mgba/gba/core.h>
#include <mgba/internal/gba/gba.h>
#include <mgba/internal/gba/serialize.h>
#include <mgba-util/vfs.h>
#include <assert.h>

static void quiet(struct mLogger* logger, int category, enum mLogLevel level,
                  const char* format, va_list args) {
	UNUSED(logger); UNUSED(category); UNUSED(level); UNUSED(format); UNUSED(args);
}

static void command(struct GBASavedata* save, uint8_t value) {
	GBASavedataWriteFlash(save, 0x5555, 0xAA);
	GBASavedataWriteFlash(save, 0x2AAA, 0x55);
	GBASavedataWriteFlash(save, 0x5555, value);
}

static void bank(struct GBASavedata* save, uint8_t value) {
	command(save, FLASH_COMMAND_SWITCH_BANK);
	GBASavedataWriteFlash(save, 0, value);
}

int main(int argc, char** argv) {
	static struct mLogger logger = { .log = quiet };
	mLogSetDefaultLogger(&logger);
	struct mCore* core = GBACoreCreate();
	assert(core && core->init(core));
	mCoreInitConfig(core, NULL);
	struct GBA* gba = core->board;
	const size_t sizes[] = { 0x1000000, 0x2000000, 0x3000000, 0x4000000 };
	for (unsigned i = 0; i < sizeof(sizes) / sizeof(*sizes); ++i) {
		struct VFile* vf = VFileMemChunk(NULL, sizes[i]);
		assert(vf);
		uint8_t* rom = vf->map(vf, sizes[i], MAP_WRITE);
		rom[0xAC] = 'B'; rom[0] = 0x11;
		if (sizes[i] > SIZE_CART0) { rom[SIZE_CART0] = 0x33; }
		rom[sizes[i] - 4] = 0x44;
		assert(core->loadROM(core, vf));
		core->reset(core);
		bool expanded = sizes[i] == SIZE_CART_EXTENDED;
		assert(gba->memory.wramSize == (expanded ? SIZE_WORKING_RAM_EXTENDED : SIZE_WORKING_RAM));
		core->busWrite32(core, 0x02000000, 0x12345678);
		assert(core->busRead32(core, 0x02040000) == (expanded ? 0 : 0x12345678));
		if (expanded) { assert(GBASavedataSize(&gba->memory.savedata) == SIZE_CART_FLASH4M); }
		unsigned expected = sizes[i] > SIZE_CART0 ? 0x33 : 0x11;
		assert(core->busRead8(core, 0x0A000000) == expected);
		assert(core->busRead16(core, 0x0A000000) == expected);
		assert(core->busRead32(core, 0x0A000000) == expected);
		uint32_t end = 0x08000000 + sizes[i] - 4;
		assert(core->busRead32(core, end) == 0x44);
		GBAPatch32(gba->cpu, end, 0x78563412, NULL);
		assert(core->busRead32(core, end) == 0x78563412);
		assert(core->busRead8(core, 0x08000000) == 0x11);
		void* state = malloc(core->stateSize(core));
		assert(core->stateSize(core) == sizeof(struct GBASerializedState) + (expanded ? SIZE_WORKING_RAM : 0));
		assert(core->saveState(core, state) && core->loadState(core, state));
		free(state);
		core->unloadROM(core);
	}
	puts("PASS: 16/32/48 MiB normal memory; arbitrary 64 MiB ROM expands by default");

	if (argc > 1) {
		assert(core->loadROM(core, VFileOpen(argv[1], O_RDONLY)));
		core->reset(core);
		assert(gba->pristineRomSize == SIZE_CART_EXTENDED);
		assert(gba->memory.wramSize == SIZE_WORKING_RAM_EXTENDED);
		assert(GBASavedataSize(&gba->memory.savedata) == SIZE_CART_FLASH4M);
		core->busWrite32(core, 0x02000000, 0x11223344);
		core->busWrite32(core, 0x02040000, 0x55667788);
		assert(core->busRead32(core, 0x02000000) == 0x11223344);
		assert(core->busRead32(core, 0x02040000) == 0x55667788);
		puts("PASS: 64 MiB default mode; independent upper EWRAM");
	} else {
		assert(core->loadROM(core, VFileMemChunk(NULL, SIZE_CART0)));
		core->reset(core);
	}

	struct mCoreConfig settings;
	mCoreConfigInit(&settings, "switch");
	mCoreConfigSetUIntValue(&settings, "gba.rom64Special512", 0);
	mCoreConfigSetIntValue(&settings, "gba.saveType", SAVEDATA_AUTODETECT);
	struct VFile* settingsFile = VFileMemChunk(NULL, 0);
	assert(mCoreConfigSaveVFile(&settings, settingsFile));
	settingsFile->seek(settingsFile, 0, SEEK_SET);
	struct mCoreConfig restoredSettings;
	mCoreConfigInit(&restoredSettings, "switch");
	assert(mCoreConfigLoadVFile(&restoredSettings, settingsFile));
	bool restoredSwitch = true;
	int restoredType = SAVEDATA_FORCE_NONE;
	assert(mCoreConfigGetBoolValue(&restoredSettings, "gba.rom64Special512", &restoredSwitch));
	assert(mCoreConfigGetIntValue(&restoredSettings, "gba.saveType", &restoredType));
	assert(!restoredSwitch && restoredType == SAVEDATA_AUTODETECT);
	mCoreConfigDeinit(&restoredSettings);
	settingsFile->close(settingsFile);
	size_t activeWramSize = gba->memory.wramSize;
	mCoreLoadForeignConfig(core, &settings);
	assert(gba->memory.wramSize == activeWramSize); // Settings wait until the game is reopened.
	core->reset(core);
	assert(gba->memory.wramSize == activeWramSize); // Reset must not change rewind/state buffer sizes.
	core->unloadROM(core);
	struct VFile* generic = VFileMemChunk(NULL, SIZE_CART_EXTENDED);
	assert(core->loadROM(core, generic)); core->reset(core);
	assert(gba->memory.wramSize == SIZE_WORKING_RAM);
	assert(gba->memory.savedata.type == SAVEDATA_AUTODETECT);
	core->unloadROM(core);
	mCoreConfigSetUIntValue(&settings, "gba.rom64Special512", 1);
	mCoreConfigSetIntValue(&settings, "gba.saveType", SAVEDATA_FLASH1M);
	mCoreLoadForeignConfig(core, &settings);
	assert(core->loadROM(core, VFileMemChunk(NULL, SIZE_CART_EXTENDED))); core->reset(core);
	assert(gba->memory.wramSize == SIZE_WORKING_RAM_EXTENDED);
	assert(GBASavedataSize(&gba->memory.savedata) == SIZE_CART_FLASH1M);
	core->unloadROM(core);
	mCoreConfigSetIntValue(&settings, "gba.saveType", SAVEDATA_AUTODETECT);
	mCoreLoadForeignConfig(core, &settings);
	assert(core->loadROM(core, argc > 1 ? VFileOpen(argv[1], O_RDONLY) : VFileMemChunk(NULL, SIZE_CART0)));
	core->reset(core);
	if (argc > 1) {
		core->busWrite32(core, 0x02000000, 0x11223344);
		core->busWrite32(core, 0x02040000, 0x55667788);
	}
	mCoreConfigDeinit(&settings);
	puts("PASS: foreign settings copy, disabled automatic mode, manual save-type priority");

	struct GBASavedata* save = &gba->memory.savedata;
	GBASavedataForceType(save, SAVEDATA_FLASH4M);
	for (unsigned i = 0; i < 8; ++i) {
		bank(save, i);
		command(save, FLASH_COMMAND_PROGRAM);
		GBASavedataWriteFlash(save, 0x1234, 0x80 + i);
	}
	for (unsigned i = 0; i < 8; ++i) {
		bank(save, i);
		assert(GBASavedataReadFlash(save, 0x1234) == 0x80 + i);
	}
	bank(save, 8); // Invalid bank must leave bank 7 selected.
	assert(save->currentBank == save->data + 0x70000);
	void* state = malloc(core->stateSize(core));
	assert(core->saveState(core, state));
	bank(save, 0);
	core->busWrite32(core, 0x02040000, 0);
	assert(core->loadState(core, state));
	assert(save->currentBank == save->data + 0x70000);
	if (argc > 1) { assert(core->busRead32(core, 0x02040000) == 0x55667788); }
	free(state);
	struct VFile* clone = VFileMemChunk(NULL, 0);
	assert(GBASavedataClone(save, clone));
	assert(clone->size(clone) == SIZE_CART_FLASH4M);
	memset(save->data, 0, SIZE_CART_FLASH4M);
	assert(GBASavedataLoad(save, clone));
	clone->close(clone);
	assert(save->data[0x71234] == 0x87 && save->data[0x1234] == 0x80);
	command(save, FLASH_COMMAND_ERASE);
	GBASavedataWriteFlash(save, 0x5555, 0xAA);
	GBASavedataWriteFlash(save, 0x2AAA, 0x55);
	GBASavedataWriteFlash(save, 0x1000, FLASH_COMMAND_ERASE_SECTOR);
	assert(save->data[0x71234] == 0xFF && save->data[0x1234] == 0x80);
	command(save, FLASH_COMMAND_ERASE);
	command(save, FLASH_COMMAND_ERASE_CHIP);
	for (size_t i = 0; i < SIZE_CART_FLASH4M; ++i) { assert(save->data[i] == 0xFF); }
	puts("PASS: all 8 Flash banks, invalid bank, state/backup restore, sector/chip erase");
	GBASavedataDeinit(save);
	uint8_t* previous = malloc(SIZE_CART_FLASH1M);
	memset(previous, 0x5A, SIZE_CART_FLASH1M);
	struct VFile* media = VFileMemChunk(previous, SIZE_CART_FLASH1M);
	free(previous);
	GBASavedataInit(save, media);
	GBASavedataForceType(save, SAVEDATA_FLASH4M);
	assert(media->size(media) == SIZE_CART_FLASH4M);
	assert(save->data[0] == 0x5A && save->data[SIZE_CART_FLASH1M - 1] == 0x5A);
	assert(save->data[SIZE_CART_FLASH1M] == 0xFF && save->data[SIZE_CART_FLASH4M - 1] == 0xFF);
	bank(save, 7);
	GBASavedataRTCWrite(save);
	assert(save->currentBank == save->data + 0x70000);
	assert(media->size(media) == SIZE_CART_FLASH4M + sizeof(struct GBASavedataRTCBuffer));
	puts("PASS: existing 128 KiB save expansion preserves data; RTC remap preserves bank 7");
	core->unloadROM(core);
	mCoreConfigDeinit(&core->config);
	core->deinit(core);
	return 0;
}
