#pragma once

#include <glad/glad.h>

class Texture {
public:
    explicit Texture(const char *path);

    auto bind() const -> void;
    auto unbind() const -> void;

	auto getWidth() const -> int32_t;
	auto getHeight() const-> int32_t;

private:
    int m_width;
    int m_height;
    int m_channels;
    GLuint m_id;
};
