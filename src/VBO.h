#pragma once
#include <array>
#include <glad/glad.h>

template<typename T, std::size_t S>
class VBO {
public:
    explicit VBO(const std::array<T, S> &source);

    auto bind() const -> void {
        glBindBuffer(GL_ARRAY_BUFFER, m_id);
    }

    auto unbind() const -> void {
        glBindBuffer(0, m_id);
    };

    auto id() { return m_id; }

private:
    std::array<T, S> m_data;
    GLuint m_id = 0;
};

template<typename T, std::size_t S>
VBO<T, S>::VBO(const std::array<T, S> &source) : m_data{source} {
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ARRAY_BUFFER, m_id);
    glBufferData(GL_ARRAY_BUFFER, sizeof(m_data), &m_data, GL_STATIC_DRAW);
}
