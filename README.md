# Pacman in OpenGL

A simple implementation of **Pacman** using **OpenGL** and **GLFW3**, created for educational purposes.

---

## ⚙️ Installation

### Requirements

- [Conan](https://conan.io/)
- [CMake](https://cmake.org/)
- C++ compiler (supporting C++17 or newer)

### Build Steps

```bash
# Install dependencies
conan install -of build .

# Generate build files
cd build
cmake --preset conan-default ..
cd ..

# Compile the project
cmake --build --preset conan-release
```
