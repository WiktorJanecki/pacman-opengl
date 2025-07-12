#pragma once

class VAO{
public:
    VAO();
    auto bind() -> void;
    auto unbind() -> void;
private:
    unsigned int m_id;
};