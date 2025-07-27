@echo off
conan install -of build .
cd build
cmake --preset conan-release ..
cd ..
cmake --build --preset conan-release