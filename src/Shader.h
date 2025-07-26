#pragma once

class Shader {
public:
    Shader(const char *vertex_src, const char *fragment_src);

    auto bind() const -> void;

    auto unbind() const -> void;

private:
    int m_id;
};
