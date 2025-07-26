#include "Shader.h"

#include <iostream>
#include <glad/glad.h>
namespace {
    auto logShaderCompilationError(GLuint shader_id) {
        int success;
        int log_length;
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
        glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);
        if (!success) {
            std::string log(log_length, '\0');
            glGetShaderInfoLog(shader_id, log_length, nullptr, &log[0]);
            std::cout << log;
        }
    }
    auto logShaderLinkingError(GLuint shader_id) {
        int success;
        int log_length;
        glGetProgramiv(shader_id, GL_LINK_STATUS, &success);
        glGetProgramiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);
        if (!success) {
            std::string log(log_length, '\0');
            glGetProgramInfoLog(shader_id, log_length, nullptr, &log[0]);
            std::cout << log;
        }
    }
}
Shader::Shader(const char *vertex_src, const char *fragment_src) {
    const int vertex_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_id, 1, &vertex_src, nullptr);
    glCompileShader(vertex_id);
    logShaderCompilationError(vertex_id);

    const int fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_id, 1, &fragment_src, nullptr);
    glCompileShader(fragment_id);
    logShaderCompilationError(fragment_id);

    m_id = glCreateProgram();
    glAttachShader(m_id, vertex_id);
    glAttachShader(m_id, fragment_id);
    glLinkProgram(m_id);
    logShaderLinkingError(m_id);

    // free
    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);
}

auto Shader::bind() const -> void {
    glUseProgram(m_id);
}

auto Shader::unbind() const -> void {
    glUseProgram(0);
}
