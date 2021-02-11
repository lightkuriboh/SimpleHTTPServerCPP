mkdir -p build
cmake -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - Unix Makefiles" -B build
cd build || exit
make
