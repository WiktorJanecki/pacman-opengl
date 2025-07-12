@echo off
conan install -of build .
cd build
cmake --preset conan-default ..
cd ..
cmake --build --preset conan-release