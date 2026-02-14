# 进入docker环境，并将当前目录映射到docker环境的/mGBA目录下

docker run -it --rm -v $PWD:/mGBA devkitpro/devkita64:20260202 /bin/bash


# cmake 命令
cmake -DCMAKE_TOOLCHAIN_FILE=../src/platform/switch/CMakeToolchain.txt ..