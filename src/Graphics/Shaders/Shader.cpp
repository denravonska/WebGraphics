#include "Graphics/Shaders/Shader.h"
#include <iostream>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "IO/Files/IOContainer.h"

glm::mat4 Shader::getViewMatrix()
{
    glm::vec3 Position = glm::vec3(0.0f, 0.0f, 3.0f);
    glm::vec3 Up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::vec3 front;
    const float Yaw = -90.0f;
    const float Pitch = 0.0f;
    front.x = cos(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    front.y = sin(glm::radians(Pitch));
    front.z = sin(glm::radians(Yaw)) * cos(glm::radians(Pitch));
    glm::vec3 Front = glm::normalize(front);
    return glm::lookAt(Position, Position + Front, Up);
}

glm::mat4 Shader::getOrthographicProjectionMatrix(int windowWidth, int windowHeight)
{
    return glm::ortho(0.0f, (float)windowWidth, 0.0f, (float)windowHeight, 0.01f, 100.0f);
}

Shader::Shader(std::string programName) : P(glm::mat4()), V(glm::mat4()), VP(glm::mat4()), color({}), rotateOffset({}), ioShader(IOContainer::getInstance().ioShader) {
    scale = glm::vec3(1.0f, 1.0f, 1.0f);
    position = glm::vec3(0.f, 0.f, 0.f);
    setProgram(programName);
    setViewProjectionMatrix(screenWidth, screenHeight);
}

Shader::~Shader() {

}

void Shader::setProgram(std::string _programName) {
    programName = _programName;
}

void Shader::setScale(int _width, int _height) {
    scale = glm::vec3((float)_width, (float)_height, 1.0f);
}

glm::mat4 Shader::getScaleMatrix(glm::vec3 scale, bool mirror) {
    if (mirror) {
        scale.x = -scale.x;
    }
    return glm::scale(glm::mat4(1.0f), scale);
}
glm::mat4 Shader::getRotationMatrix(float rotation, glm::vec3 rotationAxis, glm::vec2 rotateOffset) {
    glm::quat rotationQuat = glm::angleAxis(glm::radians(rotation), rotationAxis);
    glm::mat4 rotateMat = glm::toMat4(rotationQuat);

    glm::mat4 offsetToMiddle = glm::translate(glm::mat4(1.0f),
        glm::vec3(-rotateOffset.x / 2.0f, -rotateOffset.y / 2.0f, 0.0f));
    glm::mat4 revertOffsetToMiddle = glm::translate(glm::mat4(1.0f),
        glm::vec3(rotateOffset.x / 2.0f, rotateOffset.y / 2.0f, 0.0f));

    return revertOffsetToMiddle * rotateMat * offsetToMiddle;
}

glm::mat4 Shader::getTranslationMatrix(glm::vec3 position, glm::vec3 scale) {
    glm::vec3 adjustedPosition = glm::vec3(position.x + scale.x / 2.0f, position.y + scale.y / 2.0f, position.z);
    return glm::translate(glm::mat4(1.0f), adjustedPosition);
}

glm::mat4 Shader::getModel()
{
    glm::vec3 rotationAxis(0, 0, 1.0f);
    glm::mat4 scaleMat = getScaleMatrix(scale, mirror);
    glm::mat4 rotateMat = getRotationMatrix(rotation, rotationAxis, rotateOffset);
    glm::mat4 translateMat = getTranslationMatrix(position, scale);
    glm::mat4 modModel = translateMat * rotateMat * scaleMat;
    return modModel;
}

void Shader::setRotation(float _rotation) {
    rotation = _rotation;
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

void Shader::setPosition(int _x, int _y)
{
    position.x = _x;
    position.y = _y;
}

void Shader::setViewProjectionMatrix(int _width, int _height) {
    P = getOrthographicProjectionMatrix(_width, _height);
    V = getViewMatrix();
    VP = P * V;
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
    glm::mat4 M = getModel();
    glm::mat4 MVP = VP * M;
    glm::mat4 MV = V * M;
    glUniformMatrix4fv(glGetUniformLocation(programID, "MVP"), 1, GL_FALSE, &MVP[0][0]);
    glUniformMatrix4fv(glGetUniformLocation(programID, "MV"), 1, GL_FALSE, &MV[0][0]);
}

int Shader::getX() {
    return position.x;
}
int Shader::getY() {
    return position.y;
}
int Shader::getWidth() {
    return scale.x;
}
int Shader::getHeight() {
    return scale.y;
}

void Shader::setFloatUniform(std::string name, float value) {
    extraFloatUniforms[name] = value;
}

