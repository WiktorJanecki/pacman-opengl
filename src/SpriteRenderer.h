#pragma once

#include <span>

#include "Shader.h"
#include "Texture.h"
#include "VAO.h"

class Sprite;

class SpriteRenderer {
public:
    SpriteRenderer();

    auto render(const std::span<Sprite>& sprites) const -> void;

    Shader m_shader;
private:
    Texture m_texture;
    VAO m_vao{};
};
