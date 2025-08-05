#include "TextureAtlas.h"


TextureAtlas::TextureAtlas(const char* path)
	:m_texture{path}
{
	
}


auto TextureAtlas::getUv(uint32_t x, uint32_t y, uint32_t w, uint32_t h) const -> std::pair<glm::vec2, glm::vec2>{
	auto width = static_cast<float>(m_texture.getWidth());
	auto height = static_cast<float>(m_texture.getHeight());
	auto start = glm::vec2{x/width,y/height};
	auto end = glm::vec2{(x+w)/width, (y+h)/height}; 
	return std::make_pair(start,end);
}


auto TextureAtlas::bind() const -> void{
	m_texture.bind();
}
