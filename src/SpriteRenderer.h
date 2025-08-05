#pragma once

#include <span>

#include "Shader.h"
#include "VAO.h"

class Sprite;
class TextureAtlas;

class SpriteRenderer {
public:
    SpriteRenderer();

    auto render(const std::span<Sprite>& sprites, const TextureAtlas& atlas) const -> void;

    Shader m_shader;
private:
    VAO m_vao{};
};
