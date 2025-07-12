//
// Created by Wigtor on 13.07.2025.
//

#include "VAO.h"

#include <glad/glad.h>

VAO::VAO() {
    glGenVertexArrays(1,&m_id);
}

auto VAO::bind() -> void {
    glBindVertexArray(m_id);
}

auto VAO::unbind() -> void {
    glBindVertexArray(0);
}
