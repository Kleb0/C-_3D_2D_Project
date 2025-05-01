#pragma once

#include <string>
#include <glm/glm.hpp>

class GizmoShader
{
public:
    GizmoShader() = default;
    GizmoShader(const std::string &vertexPath, const std::string &fragmentPath);

    void use() const;
    unsigned int getID() const;

    void setMat4(const std::string &name, const glm::mat4 &mat) const;
    void setVec3(const std::string &name, const glm::vec3 &vec) const;
    void setFloat(const std::string &name, float value) const;
    void setInt(const std::string &name, int value) const;

private:
    unsigned int ID = 0;

    std::string loadFile(const std::string &path);
    void checkCompileErrors(unsigned int shader, const std::string &type);
};
