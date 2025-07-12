#include "GameLoop.h"

#include <iostream>

#include "Settings.h"
#include "Shader.h"
#include "VAO.h"
#include "VBO.h"

GameLoop::GameLoop() {
    glfwInit();

    // crash if 3.3 not supported
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

    // don't include IMMEDIATE subset of opengl (glBegin etc.)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    m_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE,nullptr,nullptr);
    glfwMakeContextCurrent(m_window);

    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glViewport(0,0,WINDOW_WIDTH,WINDOW_HEIGHT);

    loop();
}

auto GameLoop::loop() -> void {
    // TODO: move
    const char* default_frag = R"(
        #version 330 core
        out vec4 FragColor;

        void main()
        {
            FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);
        }
    )";
    const char* default_vert = R"(
        #version 330 core
        layout (location = 0) in vec3 aPos;

        void main()
        {
            gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);
        }
    )";
    Shader shader(default_vert,default_frag);

    std::array vertices = {
        -1.f,-1.f,0.0f,
         1.f,-1.f,0.0f,
         0.f, 1.f,0.0f
    };

    VBO vbo(vertices);
    VAO vao;

    // setup attr pointers
    vao.bind();
    vbo.bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
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


        shader.bind();
        vao.bind();

        glDrawArrays(GL_TRIANGLES,0,3);

        shader.unbind();
        vao.unbind();

        glfwSwapBuffers(m_window);
    }
}
