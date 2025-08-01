#pragma once

#include <vector>

#include "Shader.h"
#include "Texture.h"
#include "VAO.h"

class Sprite;

class SpriteRenderer {
public:
    SpriteRenderer();

    auto render() const -> void;

    Shader m_shader;
    std::vector<Sprite> m_sprites;
private:
    Texture m_texture;
    VAO m_vao{};
};
