#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

Texture::Texture(const char *path) {
    const auto data = stbi_load(path,&m_width,&m_height,&m_channels,0);
    glGenTextures(1,&m_id);
    glBindTexture(GL_TEXTURE_2D,m_id);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_width, m_height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
    stbi_image_free(data);
}

auto Texture::bind() const -> void {
    glBindTexture(GL_TEXTURE_2D,m_id);
}

auto Texture::unbind() const -> void {
    glBindTexture(GL_TEXTURE_2D,0);
}

auto Texture::getWidth() const -> int32_t{
	return m_width;
}

auto Texture::getHeight() const -> int32_t{
	return m_height;
}
