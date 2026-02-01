#include <beiklive/beiklive.h>

bk_shaderList_t* bk_global_shaders = NULL;

// 获取目录下所有包含 manifest.ini 的子目录路径
// 参数为 shader 根目录路径     子目录路径数组  子目录个数

bool bk_shader_get_div_list(const char* path, char*** outList, ssize_t* outCount) {
	if (!path || !outList || !outCount) {
		return false;
	}
	ssize_t count = 0;
	struct VDir* dir = VDirOpen(path);
	if (!dir) {
		return false;
	}
	size_t pathLen = strlen(path);
	int needsSlash = 0;
	if (pathLen > 0 && path[pathLen - 1] != '/') {
		needsSlash = 1;
	}
	struct VDirEntry* de;
	while ((de = dir->listNext(dir))) {
		const char* name = de->name(de);
		if (name[0] == '.') {
			continue;
		}
		if (de->type(de) != VFS_DIRECTORY) {
			continue;
		}
		size_t nameLen = strlen(name);
		// 为完整路径分配内存: path + '/' (如果需要) + name + '/' + "manifest.ini" + '\0'
		char* fullPath = malloc(pathLen + needsSlash + nameLen + 1); // +1 for '\0'
		if (!fullPath) {
			continue;
		}
		strcpy(fullPath, path);
		if (needsSlash) {
			strcat(fullPath, "/");
		}
		strcat(fullPath, name);
		char* manifestPath = malloc(pathLen + needsSlash + nameLen + 14); // +14 for "/manifest.ini" and '\0'
		if (!manifestPath) {
			free(fullPath);
			continue;
		}
		strcpy(manifestPath, fullPath);
		strcat(manifestPath, "/manifest.ini");
		struct VFile* vf = VFileOpen(manifestPath, O_RDONLY);
		free(manifestPath);

		if (vf) {
			vf->close(vf);
			count++;
		}
		free(fullPath);
	}
	dir->close(dir);
	if (count == 0) {
		*outList = NULL;
		*outCount = 0;
		return false;
	}
	char** dirList = malloc(sizeof(char*) * count);
	if (!dirList) {
		*outList = NULL;
		*outCount = 0;
		return false;
	}
	dir = VDirOpen(path);
	if (!dir) {
		free(dirList);
		*outList = NULL;
		*outCount = 0;
		return false;
	}
	ssize_t index = 0;
	while ((de = dir->listNext(dir))) {
		const char* name = de->name(de);
		if (name[0] == '.') {
			continue;
		}

		if (de->type(de) != VFS_DIRECTORY) {
			continue;
		}
		size_t nameLen = strlen(name);
		char* fullPath = malloc(pathLen + needsSlash + nameLen + 1);
		if (!fullPath) {
			continue;
		}
		strcpy(fullPath, path);
		if (needsSlash) {
			strcat(fullPath, "/");
		}
		strcat(fullPath, name);
		char* manifestPath = malloc(pathLen + needsSlash + nameLen + 14);
		if (!manifestPath) {
			free(fullPath);
			continue;
		}
		strcpy(manifestPath, fullPath);
		strcat(manifestPath, "/manifest.ini");

		struct VFile* vf = VFileOpen(manifestPath, O_RDONLY);
		free(manifestPath);

		if (vf) {
			vf->close(vf);
			dirList[index] = fullPath; // 直接使用fullPath，不需要再次分配
			index++;
		} else {
			free(fullPath);
		}
		if (index >= count) {
			break;
		}
	}
	dir->close(dir);
	if (index < count) {
		if (index > 0) {
			char** newList = realloc(dirList, sizeof(char*) * index);
			if (newList) {
				dirList = newList;
				count = index;
			}
		} else {
			free(dirList);
			dirList = NULL;
			count = 0;
		}
	}
	*outList = dirList;
	*outCount = count;
	return count > 0;
}


void bk_shader_list_init(void)
{
    char** shaderList = NULL;
    ssize_t shaderCount = 0;

    if (!bk_shader_get_div_list(BK_SHADER_PATH, &shaderList, &shaderCount)) {
        return;
    }

    struct BKVideoShader** tempShaders =
        malloc(sizeof(struct BKVideoShader*) * shaderCount);
    int validCount = 0;

    for (ssize_t i = 0; i < shaderCount; i++) {
        struct BKVideoShader* shader =
            malloc(sizeof(struct BKVideoShader));
        if (!shader) {
            continue;
        }

        struct VDir* dir = VDirOpen(shaderList[i]);
        if (!dir) {
            free(shader);
            continue;
        }

        if (mBKGLES2ShaderLoad(shader, dir)) {
            tempShaders[validCount++] = shader;
        } else {
            free(shader);
        }

        dir->close(dir);
    }

    /* 创建全局 shader 列表 */
    bk_global_shaders = malloc(sizeof(bk_shaderList_t));
    bk_global_shaders->count = validCount;
    bk_global_shaders->shaders =
        malloc(sizeof(struct BKVideoShader*) * validCount);

    for (int i = 0; i < validCount; i++) {
        bk_global_shaders->shaders[i] = tempShaders[i];
    }

    /* 清理临时数据 */
    free(tempShaders);

    for (ssize_t i = 0; i < shaderCount; i++) {
        free(shaderList[i]);
    }
    free(shaderList);

    printf("Loaded %d shaders\n", bk_global_shaders->count);
}



void bk_shader_list_deinit(void)
{
    if (!bk_global_shaders) {
        return;
    }

    for (int i = 0; i < bk_global_shaders->count; i++) {
        struct BKVideoShader* shader = bk_global_shaders->shaders[i];
        if (shader) {
            free((void*) shader->name);
            free((void*) shader->author);
            free((void*) shader->description);
            shader->name = 0;
            shader->author = 0;
            shader->description = 0;
            struct mBKGLES2Shader* shaders = shader->passes;
            size_t n;
            for (n = 0; n < shader->nPasses; ++n) {
                mBKGLES2ShaderDeinit(&shaders[n]);
                size_t u;
                for (u = 0; u < shaders[n].nUniforms; ++u) {
                    free((void*) shaders[n].uniforms[u].name);
                    free((void*) shaders[n].uniforms[u].readableName);
                }
            }
            free(shaders);
            shader->passes = 0;
            shader->nPasses = 0;
        }
    }

    free(bk_global_shaders->shaders);
    free(bk_global_shaders);
    bk_global_shaders = NULL;
}

int bk_shader_get_count(void)
{
    if (!bk_global_shaders) {
        return 0;
    }
    return bk_global_shaders->count;
}

char** bk_shader_get_names(void)
{
    if (!bk_global_shaders || bk_global_shaders->count == 0) {
        return NULL;
    }

    int count = bk_global_shaders->count;
    char** names = malloc(sizeof(char*) * count);
    if (!names) {
        return NULL;
    }

    for (int i = 0; i < count; i++) {
        names[i] = bk_global_shaders->shaders[i]->name;
        printf("Shader %d: %s\n", i, bk_global_shaders->shaders[i]->name);
    }

    return names;
}

