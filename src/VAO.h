#pragma once
#include <glad/glad.h>

class VAO{
public:
    explicit VAO();
    auto bind() const-> void;
    auto unbind() const-> void;
private:
    GLuint m_id = 0;
};
