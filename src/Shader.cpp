//
// Created by Wigtor on 12.07.2025.
//

#include "Shader.h"

#include <iostream>
#include <glad/glad.h>

auto logShaderError(int shader_id) -> void {
    int success;
    int log_length;
    glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);
    glGetShaderiv(shader_id, GL_INFO_LOG_LENGTH, &log_length);
    if (!success) {
        std::string log(log_length,'\0');
        glGetShaderInfoLog(shader_id, 1024, &log_length, &log[0]);
        std::cout << log;
    }
}

Shader::Shader(const char *vertex_src, const char *fragment_src) {
    const int vertex_id = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex_id,1,&vertex_src,nullptr);
    glCompileShader(vertex_id);

    // if debug
    logShaderError(vertex_id);

    const int fragment_id = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment_id,1,&fragment_src,nullptr);
    glCompileShader(fragment_id);

    //if debug
    logShaderError(fragment_id);

    m_id = glCreateProgram();
    glAttachShader(m_id,vertex_id);
    glAttachShader(m_id,fragment_id);
    glLinkProgram(m_id);

    // if debug
    int success;
    glGetProgramiv(m_id, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(m_id, 512, NULL, infoLog);
        std::cout << infoLog;
    }

    // free
    glDeleteShader(vertex_id);
    glDeleteShader(fragment_id);
}

auto Shader::bind() -> void {
    glUseProgram(m_id);
}

auto Shader::unbind() -> void {
    glUseProgram(0);
}
