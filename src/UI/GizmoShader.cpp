#include "UI/GizmoShader.hpp"
#include <glm/gtc/type_ptr.hpp>
#include <glad/glad.h>
#include <fstream>
#include <sstream>
#include <iostream>

GizmoShader::GizmoShader(const std::string &vertexPath, const std::string &fragmentPath)
{
    std::string vertexCode = loadFile(vertexPath);
    std::string fragmentCode = loadFile(fragmentPath);

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();

    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, nullptr);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");

    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, nullptr);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");

    ID = glCreateProgram();
    glAttachShader(ID, vertex);
    glAttachShader(ID, fragment);
    glLinkProgram(ID);
    checkCompileErrors(ID, "PROGRAM");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void GizmoShader::use() const
{
    glUseProgram(ID);
}

unsigned int GizmoShader::getID() const
{
    return ID;
}

void GizmoShader::setMat4(const std::string &name, const glm::mat4 &mat) const
{
    glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, glm::value_ptr(mat));
}

void GizmoShader::setVec3(const std::string &name, const glm::vec3 &vec) const
{
    glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, glm::value_ptr(vec));
}

void GizmoShader::setFloat(const std::string &name, float value) const
{
    glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void GizmoShader::setInt(const std::string &name, int value) const
{
    glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

std::string GizmoShader::loadFile(const std::string &path)
{
    std::ifstream file(path);
    std::stringstream buffer;
    if (file)
    {
        buffer << file.rdbuf();
        file.close();
    }
    else
    {
        std::cerr << "[Shader] Erreur de chargement : " << path << std::endl;
    }
    return buffer.str();
}

void GizmoShader::checkCompileErrors(unsigned int shader, const std::string &type)
{
    int success;
    char infoLog[1024];

    if (type != "PROGRAM")
    {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if (!success)
        {
            glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "[Shader Compile Error] (" << type << "):\n"
                      << infoLog << std::endl;
        }
    }
    else
    {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if (!success)
        {
            glGetProgramInfoLog(shader, 1024, nullptr, infoLog);
            std::cerr << "[Shader Linking Error] (" << type << "):\n"
                      << infoLog << std::endl;
        }
    }
}
