mkdir -p build
cmake -DCMAKE_BUILD_TYPE=Release -G "CodeBlocks - Unix Makefiles" -B build
cp config.cfg build/config.cfg
cd build || exit
make
