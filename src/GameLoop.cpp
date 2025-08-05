#include "GameLoop.h"

#include <glad/glad.h> // before glfw
#include <GLFW/glfw3.h>
#include <iostream>
#include <stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Settings.h"
#include "Sprite.h"
#include "SpriteRenderer.h"
#include "TextureAtlas.h"

GameLoop::GameLoop() {
    glfwInit();

    // crash if 3.3 not supported
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(1280, 720);

    // don't include IMMEDIATE subset of opengl (glBegin etc.)
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    stbi_set_flip_vertically_on_load(true);

    m_window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, WINDOW_TITLE, nullptr, nullptr);
    glfwMakeContextCurrent(m_window);
	
	// vsync
	glfwSwapInterval(0);

    gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
    glEnable(GL_BLEND);;
    // glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    loop();
}

auto GameLoop::loop() -> void {
    SpriteRenderer renderer;
	TextureAtlas atlas{"assets/player.png"};
    Sprite sprite1{};
    sprite1.m_position.x = 2.0f;
    sprite1.m_rotation.x = 45.0f;
    Sprite sprite2{};
    sprite1.m_position.x = -1.0f;
    sprite1.m_position.y = -1.0f;
    sprite1.m_position.z = -1.0f;
    sprite1.m_rotation.z = 45.0f;
	sprite2.m_sourceUV = {0,32,64,32};
    std::array sprites{sprite1,sprite2};
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

        renderer.render(sprites, atlas);

        glfwSwapBuffers(m_window);
    }
}
