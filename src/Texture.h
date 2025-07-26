#pragma once

#include <glad/glad.h>

class Texture {
public:
    explicit Texture(const char *path);

    auto bind() const -> void;
    auto unbind() const -> void;

private:
    int m_width;
    int m_height;
    int m_channels;
    GLuint m_id;
};
