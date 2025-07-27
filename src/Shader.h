#pragma once
#include <glm/fwd.hpp>

class Shader {
public:
    Shader(const char *vertex_src, const char *fragment_src);

    auto bind() const -> void;

    auto unbind() const -> void;

    auto setUniform(const char* name, glm::mat4 value) const -> void;
    auto setUniform(const char* name, float value) const -> void;
    auto setUniform(const char* name, int value) const -> void;

private:
    int m_id;
};
