#include "TextureAtlas.h"


TextureAtlas::TextureAtlas(unsigned int width, unsigned int height)
: m_width{width}, m_height{height}{

}


std::pair<glm::vec2, glm::vec2> TextureAtlas::getUv(uint32_t x, uint32_t y, uint32_t w, uint32_t h){
	auto width = static_cast<float>(m_width);
	auto height = static_cast<float>(m_height);
	auto start = glm::vec2{x/width,y/height};
	auto end = glm::vec2{(x+w)/width, (y+h)/height}; 
	return std::make_pair(start,end);
}
