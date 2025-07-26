#include "VAO.h"

#include <glad/glad.h>

VAO::VAO() {
    glGenVertexArrays(1, &m_id);
}

auto VAO::bind() const -> void {
    glBindVertexArray(m_id);
}

auto VAO::unbind() const -> void {
    glBindVertexArray(0);
}
