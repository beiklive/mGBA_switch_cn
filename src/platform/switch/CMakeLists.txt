find_program(ELF2NRO elf2nro)
find_program(NACPTOOL nacptool)
find_program(BUILD_ROMFS build_romfs)
find_library(GLAPI_LIBRARY glapi REQUIRED)
find_library(EGL_LIBRARY EGL REQUIRED)

set(OS_DEFINES _GNU_SOURCE IOAPI_NO_64)
list(APPEND CORE_VFS_SRC ${CMAKE_SOURCE_DIR}/src/util/vfs/vfs-fd.c ${CMAKE_SOURCE_DIR}/src/util/vfs/vfs-dirent.c)
# list(APPEND GUI_SRC ${CMAKE_CURRENT_SOURCE_DIR}/gui-font.c)

include_directories(AFTER ${OPENGLES3_INCLUDE_DIR} ${OPENGL_EGL_INCLUDE_DIR})
include_directories(AFTER ${CMAKE_SOURCE_DIR}/src/platform/switch/include)

if(${CMAKE_BUILD_TYPE} STREQUAL Debug OR ${CMAKE_BUILD_TYPE} STREQUAL RelWithDebInfo)
	find_library(NOUVEAU_LIBRARY drm_nouveaud REQUIRED)
	list(APPEND OS_LIB nxd)
else()
	find_library(NOUVEAU_LIBRARY drm_nouveau REQUIRED)
	list(APPEND OS_LIB nx)
endif()


# 查找 FreeType 库（用于字体渲染）
find_path(FREETYPE_INCLUDE_DIR ft2build.h PATHS ${DEVKITPRO}/portlibs/switch/include/freetype2 NO_DEFAULT_PATH)
find_library(FREETYPE_LIBRARY freetype PATHS ${DEVKITPRO}/portlibs/switch/lib NO_DEFAULT_PATH)
if(FREETYPE_INCLUDE_DIR AND FREETYPE_LIBRARY)
    include_directories(${FREETYPE_INCLUDE_DIR})
    list(APPEND OS_LIB ${FREETYPE_LIBRARY})
    message(STATUS "Found FreeType: ${FREETYPE_LIBRARY}")
else()
    message(FATAL_ERROR "FreeType library not found. Please install switch-freetype.")
endif()

# ===== 查找 HarfBuzz =====
find_path(HARFBUZZ_INCLUDE_DIR hb.h PATHS ${DEVKITPRO}/portlibs/switch/include/harfbuzz NO_DEFAULT_PATH)
find_library(HARFBUZZ_LIBRARY harfbuzz PATHS ${DEVKITPRO}/portlibs/switch/lib NO_DEFAULT_PATH)
if(HARFBUZZ_INCLUDE_DIR AND HARFBUZZ_LIBRARY)
    include_directories(${HARFBUZZ_INCLUDE_DIR})
    list(APPEND OS_LIB ${HARFBUZZ_LIBRARY})
    message(STATUS "Found HarfBuzz: ${HARFBUZZ_LIBRARY}")
else()
    message(FATAL_ERROR "HarfBuzz library not found. Please install switch-harfbuzz.")
endif()

# ===== 查找 bzip2 =====
find_path(BZIP2_INCLUDE_DIR bzlib.h PATHS ${DEVKITPRO}/portlibs/switch/include NO_DEFAULT_PATH)
find_library(BZIP2_LIBRARY bz2 PATHS ${DEVKITPRO}/portlibs/switch/lib NO_DEFAULT_PATH)
if(BZIP2_INCLUDE_DIR AND BZIP2_LIBRARY)
    include_directories(${BZIP2_INCLUDE_DIR})
    list(APPEND OS_LIB ${BZIP2_LIBRARY})
    message(STATUS "Found Bzip2: ${BZIP2_LIBRARY}")
else()
    message(FATAL_ERROR "Bzip2 library not found. Please install switch-bzip2.")
endif()

# ===== Plutonium 路径直接指定 =====
set(PLUTONIUM_ROOT "${CMAKE_SOURCE_DIR}/src/platform/switch/Plutonium")
set(PLUTONIUM_INCLUDE_DIR "${PLUTONIUM_ROOT}/Plutonium/include")
set(PLUTONIUM_LIBRARY "${PLUTONIUM_ROOT}/Plutonium/lib/libpu.a")

if(EXISTS ${PLUTONIUM_INCLUDE_DIR}/pu/pu_Include.hpp AND EXISTS ${PLUTONIUM_LIBRARY})
    include_directories(${PLUTONIUM_INCLUDE_DIR})
    list(APPEND OS_LIB ${PLUTONIUM_LIBRARY})
    message(STATUS "Found Plutonium: ${PLUTONIUM_LIBRARY}")
else()
    message(FATAL_ERROR "Plutonium library not found. Please ensure Plutonium is built in ${PLUTONIUM_ROOT}")
endif()

# ===== 查找 Plutonium 依赖的其他库（已通过 dkp-pacman 安装）=====
# 设置 devkitPro 的 portlibs 路径
set(DEVKITPRO_PORTLIBS "${DEVKITPRO}/portlibs/switch")

# SDL2 及相关库
find_library(SDL2_LIBRARY SDL2 PATHS ${DEVKITPRO_PORTLIBS}/lib NO_DEFAULT_PATH)
find_library(SDL2_TTF_LIBRARY SDL2_ttf PATHS ${DEVKITPRO_PORTLIBS}/lib NO_DEFAULT_PATH)
find_library(SDL2_IMAGE_LIBRARY SDL2_image PATHS ${DEVKITPRO_PORTLIBS}/lib NO_DEFAULT_PATH)
find_library(SDL2_GFX_LIBRARY SDL2_gfx PATHS ${DEVKITPRO_PORTLIBS}/lib NO_DEFAULT_PATH)
find_library(SDL2_MIXER_LIBRARY SDL2_mixer PATHS ${DEVKITPRO_PORTLIBS}/lib NO_DEFAULT_PATH)

# 音频相关
find_library(OPUSFILE_LIBRARY opusfile PATHS ${DEVKITPRO_PORTLIBS}/lib NO_DEFAULT_PATH)
find_library(OPUS_LIBRARY opus PATHS ${DEVKITPRO_PORTLIBS}/lib NO_DEFAULT_PATH)
find_library(MODPLUG_LIBRARY modplug PATHS ${DEVKITPRO_PORTLIBS}/lib NO_DEFAULT_PATH)
find_library(MPG123_LIBRARY mpg123 PATHS ${DEVKITPRO_PORTLIBS}/lib NO_DEFAULT_PATH)
find_library(VORBISIDEC_LIBRARY vorbisidec PATHS ${DEVKITPRO_PORTLIBS}/lib NO_DEFAULT_PATH)
find_library(OGG_LIBRARY ogg PATHS ${DEVKITPRO_PORTLIBS}/lib NO_DEFAULT_PATH)

# 图像相关
find_library(PNG_LIBRARY png PATHS ${DEVKITPRO_PORTLIBS}/lib NO_DEFAULT_PATH)
find_library(JPEG_LIBRARY jpeg PATHS ${DEVKITPRO_PORTLIBS}/lib NO_DEFAULT_PATH)
find_library(WEBP_LIBRARY webp PATHS ${DEVKITPRO_PORTLIBS}/lib NO_DEFAULT_PATH)

# OpenGL/EGL 相关（可能已有）
find_library(GLESV2_LIBRARY GLESv2 PATHS ${DEVKITPRO_PORTLIBS}/lib NO_DEFAULT_PATH)
find_library(EGL_LIBRARY EGL PATHS ${DEVKITPRO_PORTLIBS}/lib NO_DEFAULT_PATH)
find_library(GLAPI_LIBRARY glapi PATHS ${DEVKITPRO_PORTLIBS}/lib NO_DEFAULT_PATH)
find_library(DRM_NOUVEAU_LIBRARY drm_nouveau PATHS ${DEVKITPRO_PORTLIBS}/lib NO_DEFAULT_PATH)

# libnx
find_library(NX_LIBRARY nx PATHS ${DEVKITPRO}/libnx/lib NO_DEFAULT_PATH)

# FreeType（如果之前没找到，这里再补）
find_library(FREETYPE_LIBRARY freetype PATHS ${DEVKITPRO_PORTLIBS}/lib NO_DEFAULT_PATH)

# 将所有找到的库添加到 OS_LIB（避免重复）
foreach(LIB IN ITEMS
    SDL2_LIBRARY
    SDL2_TTF_LIBRARY
    SDL2_IMAGE_LIBRARY
    SDL2_GFX_LIBRARY
    SDL2_MIXER_LIBRARY
    OPUSFILE_LIBRARY
    OPUS_LIBRARY
    MODPLUG_LIBRARY
    MPG123_LIBRARY
    VORBISIDEC_LIBRARY
    OGG_LIBRARY
    PNG_LIBRARY
    JPEG_LIBRARY
    WEBP_LIBRARY
    GLESV2_LIBRARY
    EGL_LIBRARY
    GLAPI_LIBRARY
    DRM_NOUVEAU_LIBRARY
    NX_LIBRARY
    FREETYPE_LIBRARY
)
    if(${LIB})
        list(APPEND OS_LIB ${${LIB}})
    endif()
endforeach()

set(CORE_VFS_SRC ${CORE_VFS_SRC} PARENT_SCOPE)
set(OS_DEFINES ${OS_DEFINES} PARENT_SCOPE)
set(OS_LIB ${OS_LIB} PARENT_SCOPE)

if(BUILD_PERF)
	add_custom_target(${BINARY_NAME}-perf.nro ALL
	                  ${ELF2NRO} ../${BINARY_NAME}-perf ${BINARY_NAME}-perf.nro
	                  DEPENDS ${BINARY_NAME}-perf)
	install(FILES
		    ${CMAKE_CURRENT_BINARY_DIR}/${BINARY_NAME}-perf.nro
		    DESTINATION . COMPONENT ${BINARY_NAME}-perf)
endif()

set(BEIKLIVE_SRC
    src/App.cpp
    src/EglManager.cpp
    src/OpenGLManager.cpp
    src/Utils.cpp
	)

add_executable(${BINARY_NAME}.elf ${GUI_SRC} ${PLATFORM_SRC} main.cpp ${BEIKLIVE_SRC})
set_target_properties(${BINARY_NAME}.elf PROPERTIES COMPILE_DEFINITIONS "${OS_DEFINES};${FEATURE_DEFINES};${FUNCTION_DEFINES}")
target_link_libraries(${BINARY_NAME}.elf ${BINARY_NAME} ${M_LIBRARY} ${EGL_LIBRARY} ${OPENGLES3_LIBRARY} ${GLAPI_LIBRARY} ${NOUVEAU_LIBRARY} stdc++ ${OS_LIB})

add_custom_command(OUTPUT control.nacp
                   COMMAND ${NACPTOOL} --create "mGBA中文版" "endrift, 魔改: beiklive" "0.10.5_CN" control.nacp)

add_custom_command(OUTPUT romfs.bin
                   COMMAND ${CMAKE_COMMAND} -E make_directory romfs
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/res/font-new.png" romfs/
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/res/font-cn.png" romfs/
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_SOURCE_DIR}/res/switchbg.png" romfs/
                   COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/fileassoc.cfg.in" romfs/
                   COMMAND ${BUILD_ROMFS} romfs romfs.bin
                   COMMAND ${CMAKE_COMMAND} -E remove_directory romfs
               DEPENDS "${CMAKE_SOURCE_DIR}/res/font-new.png" "${CMAKE_CURRENT_SOURCE_DIR}/fileassoc.cfg.in")

add_custom_target(${BINARY_NAME}.nro ALL
                  ${ELF2NRO} ${BINARY_NAME}.elf ${BINARY_NAME}.nro --romfs=romfs.bin --nacp=control.nacp --icon="${CMAKE_CURRENT_SOURCE_DIR}/icon.png"
                  DEPENDS ${BINARY_NAME}.elf control.nacp ${CMAKE_CURRENT_SOURCE_DIR}/icon.png romfs.bin)

install(TARGETS ${BINARY_NAME}.elf DESTINATION . COMPONENT ${BINARY_NAME}-dbg)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${BINARY_NAME}.nro DESTINATION . COMPONENT ${BINARY_NAME}-switch)
