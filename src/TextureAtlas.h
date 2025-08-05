#pragma once

#include <glm/vec2.hpp>
#include <utility>

class TextureAtlas{
public:
	TextureAtlas(unsigned int width, unsigned int height);
	std::pair<glm::vec2, glm::vec2> getUv(uint32_t x, uint32_t y, uint32_t w, uint32_t h);
private:
	unsigned int m_width;
	unsigned int m_height;

};
