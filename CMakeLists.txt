cmake_minimum_required(VERSION 3.30)
project(pacman_opengl)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package(glad REQUIRED)
find_package(glfw3 REQUIRED)
find_package(stb REQUIRED)
find_package(glm REQUIRED)

add_executable(pacman_opengl src/main.cpp src/GameLoop.cpp src/Shader.cpp src/VAO.cpp src/Texture.cpp src/SpriteRenderer.cpp src/Sprite.cpp)
target_link_libraries(pacman_opengl glfw glad::glad stb::stb glm::glm)

file(COPY assets DESTINATION ${CMAKE_BINARY_DIR})
