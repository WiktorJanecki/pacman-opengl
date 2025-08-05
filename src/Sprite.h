#pragma once

#include <glm/glm.hpp>

class Sprite {
public:
    glm::vec3 m_position{};
    glm::vec3 m_rotation{};
    glm::vec2 m_scale{1.0f,1.0f};
    glm::vec<4, unsigned int> m_sourceUV{0,0,0,0};
};

