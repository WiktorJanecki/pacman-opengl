#pragma once

#include <utility>
#include <glm/vec2.hpp>

#include "Texture.h"

class TextureAtlas{
public:
	TextureAtlas(const char* path);
	auto getUv(uint32_t x, uint32_t y, uint32_t w, uint32_t h) const -> std::pair<glm::vec2, glm::vec2>;
	auto bind() const -> void;
private:
	uint32_t m_width;
	uint32_t m_height;
	Texture m_texture;

};
