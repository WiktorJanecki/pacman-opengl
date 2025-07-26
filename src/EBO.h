#pragma once
#include <array>
#include <glad/glad.h>

template<std::size_t S>
class EBO {
    using T = GLuint;

public:
    explicit EBO(const std::array<T, S> &source);

    auto bind() const -> void {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    }

    auto unbind() const -> void {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }

    auto id() const { return m_id; }

private:
    std::array<T, S> m_data;
    GLuint m_id = 0;
};

template<std::size_t S>
EBO<S>::EBO(const std::array<T, S> &source) : m_data{source} {
    glGenBuffers(1, &m_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(m_data), &m_data, GL_STATIC_DRAW);
}
