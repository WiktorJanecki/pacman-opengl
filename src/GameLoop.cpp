#include "GameLoop.h"

#include <glad/glad.h> // before glfw
#include <GLFW/glfw3.h>
#include <iostream>

#include "Settings.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"
#include "EBO.h"

GameLoop::GameLoop() {
    glfwInit();

    // crash if 3.3 not supported
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // don't include IMMEDIATE subset of opengl (glBegin etc.)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
    glfwMakeContextCurrent(m_window);

    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    loop();
}

auto GameLoop::loop() -> void {
    // TODO: move
    const auto default_frag = R"(
        #version 330 core
        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
        }
    )";
    const auto default_vert = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;

        void main()
        {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
    )";
    Shader shader(default_vert, default_frag);

    std::array vertices = {
        -1.f, -1.f, 0.0f,
        -1.f, 1.f, 0.0f,
        1.f, 1.f, 0.0f,
        1.f, -1.f, 0.0f
    };
    for (auto &v: vertices) { v *= 0.5f; }

    std::array<unsigned int, 6> indices = {
        0, 1, 2,
        0, 2, 3
    };


    VAO vao;
    VBO vbo{vertices};
    EBO ebo{indices};

    // setup vao
    vao.bind();

    ebo.bind();
    vbo.bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    vao.unbind();


    m_timer = glfwGetTime();

    while (!glfwWindowShouldClose(m_window)) {
        glfwPollEvents();

        double current_time = glfwGetTime();
        if (current_time - m_timer >= 1.0) {
            m_timer = current_time;
            std::cout << m_frames << '\n';
            m_frames = 0;
        }
        m_frames++;

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        shader.bind();
        vao.bind();

        glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT, nullptr);
        shader.unbind();
        vao.unbind();

        glfwSwapBuffers(m_window);
    }
}
