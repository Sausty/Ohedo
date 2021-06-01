cmake -G "MinGW Makefiles" -B build
cmake -G "Visual Studio 16 2019" -B vs2019
cd build
mingw32-make
cd examples
MeshLoading
cd ../../