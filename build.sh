#!/bin/bash

conan install . --build missing -of build
cmake --preset conan-release -G "Ninja"
cmake --build --preset conan-release
