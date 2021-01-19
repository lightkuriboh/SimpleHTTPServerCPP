sudo add-apt-repository ppa:ubuntu-toolchain-r/test
sudo apt-get install gcc-9
sudo apt-get install g++-9
wget https://github.com/Kitware/CMake/releases/download/v3.19.0-rc1/cmake-3.19.0-rc1.tar.gz
tar -xzvf cmake-3.19.0-rc1.tar.gz
cd cmake-3.19.0-rc1 || exit
chmod +x bootstrap
./bootstrap
make
sudo make install
./run.sh
