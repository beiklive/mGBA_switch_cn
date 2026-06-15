mkdir build_switch
cd build_switch
cmake -DCMAKE_TOOLCHAIN_FILE=../src/platform/switch/CMakeToolchain.txt ..
make -j$(sysctl -n hw.ncpu)