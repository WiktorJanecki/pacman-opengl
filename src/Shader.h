#pragma once

class Shader{
public:
    Shader(const char* vertex_src, const char* fragment_src);
    auto bind() -> void;
    auto unbind() -> void;
private:
    int m_id;
};