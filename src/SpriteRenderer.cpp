#include "SpriteRenderer.h"

#include <array>
#include <span>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "EBO.h"
#include "Settings.h"
#include "Sprite.h"
#include "TextureAtlas.h"
#include "VBO.h"

namespace {
    constexpr char vertex_src[] = R"(
        #version 330 core
        layout (location = 0) in vec3 pos;
		layout (location = 1) in vec2 uv;

        uniform mat4 u_model;
        uniform mat4 u_view;
        uniform mat4 u_projection;

        out vec2 out_uv;

        void main()
        {
            out_uv = uv;
            gl_Position = u_projection * u_view * u_model * vec4(pos.xyz, 1.0);
        }
    )";
    constexpr char fragment_src[] = R"(
        #version 330 core
        in vec2 out_uv;
        out vec4 FragColor;

        uniform sampler2D ourTexture;


        void main()
        {
            vec4 color = texture(ourTexture,out_uv);
            FragColor = color;
        }
    )";
    constexpr std::array vertices{
        -1.f, -1.f, 0.0f,
        -1.f, 1.f, 0.0f,
        1.f, 1.f, 0.0f,
        1.f, -1.f, 0.0f
    };
    constexpr std::array uv{
        0.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f
    };
    constexpr std::array indices{
        0u, 1u, 2u,
        0u, 2u, 3u
    };
}

SpriteRenderer::SpriteRenderer() : m_shader{vertex_src, fragment_src},
                                   m_texture{Texture{"assets/player.png"}} {

    VBO vbo{vertices};
    VBO tbo{uv};
    EBO ebo{indices};

    m_vao.bind();

    vbo.bind();
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);
    // tbo.bind();
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
    // glEnableVertexAttribArray(1);
    ebo.bind();
    glActiveTexture(GL_TEXTURE0);
    m_texture.bind();

    m_vao.unbind();

    auto fov{glm::radians(45.0f)};
    auto aspect_ratio = static_cast<float>(WINDOW_WIDTH) / static_cast<float>(WINDOW_HEIGHT);
    glm::mat4 proj = glm::perspective(fov, aspect_ratio, 0.1f, 100.0f);
    m_shader.setUniform("u_projection", proj);

    auto view = glm::identity<glm::mat4>();
    view = glm::translate(view, {0.0f,0.0f,-5.0f});
    m_shader.setUniform("u_view", view);

}

auto SpriteRenderer::render(const std::span<Sprite>& sprites) const -> void {
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    // glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	auto atlas = TextureAtlas(64,64);
    m_shader.bind();
    m_vao.bind();

    for (const auto & sprite : sprites ) {

		auto [start, end] = atlas.getUv(sprite.m_sourceUV.x,sprite.m_sourceUV.y,sprite.m_sourceUV.z,sprite.m_sourceUV.w);
		std::array uvs = {
			start.x, start.y,
			start.x, end.y,
			end.x,   end.y,
			end.x,   start.y
		};
		VBO tbo{uvs};
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
		glEnableVertexAttribArray(1);

        auto transformation = glm::identity<glm::mat4>();
        auto scale = glm::vec3{sprite.m_scale,1.0f};
        transformation = glm::scale(transformation,scale);
        transformation = glm::translate(transformation,sprite.m_position);
        transformation = glm::rotate(transformation,glm::radians(sprite.m_rotation.x),{1.0f,0.0f,0.0f});
        transformation = glm::rotate(transformation,glm::radians(sprite.m_rotation.y),{0.0f,1.0f,0.0f});
        transformation = glm::rotate(transformation,glm::radians(sprite.m_rotation.z),{0.0f,0.0f,1.0f});
        m_shader.setUniform("u_model",transformation);

        glDrawElements(GL_TRIANGLES, 6,GL_UNSIGNED_INT, nullptr);
		tbo.unbind();
    }

    m_shader.unbind();
    m_vao.unbind();
}
