#include <iostream>
#include <GLFW/glfw3.h>

int main() {
    std::cout << "Hello\n";
    glfwInit();
    const auto window = glfwCreateWindow(1280, 720, "Joł,", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();

        glClearColor(1, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT);

        glfwSwapBuffers(window);
    }
    return 0;
}
