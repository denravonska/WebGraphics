#include "Graphics/Shaders/Shader.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "IO/Files/IOContainer.h"


Shader::Shader(std::string programName) : color({}), ioShader(IOContainer::getInstance().ioShader) {
    setProgram(programName);
    camera = std::make_shared<Camera>(1920, 1080);
}

Shader::~Shader() {

}

void Shader::setModel(Model _model) {
    model = _model;
}

void Shader::setCamera(std::shared_ptr<Camera> _camera) {
    camera = _camera;
}

std::shared_ptr<Camera> Shader::getCamera() {
    return camera;
}

void Shader::setProgram(std::string _programName) {
    programName = _programName;
}

void Shader::setUniforms() {
    GLuint programID = ioShader.getProgram(programName);
    glUseProgram(programID);
    setMatrixUniforms();
    setColorUniforms();
    setCustomUniforms();
    setExtraUniforms();
    glUniform1f(glGetUniformLocation(programID, "effect"), effect);
}

void Shader::setExtraUniforms() {
    GLuint programID = ioShader.getProgram(programName);
    for (const auto& [key, value] : extraFloatUniforms) {
        glUniform1f(glGetUniformLocation(programID, key.c_str()), value);
    }
}

void Shader::setColorUniforms()
{
    GLuint programID = ioShader.getProgram(programName);
    glUniform1f(glGetUniformLocation(programID, "alpha"), alpha);
    glUniform3fv(glGetUniformLocation(programID, "color"), 1, &color[0]);
}

void Shader::setMatrixUniforms()
{
    GLuint programID = ioShader.getProgram(programName);
    glm::mat4 M = model.getModel();
    auto V = camera->getView();
    auto P = camera->getProjection();
    auto VP = P * V;
    glm::mat4 MVP = VP * M;
    glm::mat4 MV = V * M;
    glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(programID, "MV"), 1, GL_FALSE, &MV[0][0]);
}

void Shader::setFloatUniform(std::string name, float value) {
    extraFloatUniforms[name] = value;
}

