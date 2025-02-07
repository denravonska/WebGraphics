#include "Drawables/Drawable.h"
#include "Engine/Engine.h"

Drawable::Drawable(Shader& _shader) : shader(&_shader), objectContainer(ObjectContainer::getInstance())
{

};

Drawable::~Drawable() {

}

void Drawable::setCenterPosition(int _x, int _y) {
    setPosition(_x - getWidth() / 2, _y - getHeight() / 2);
}

void Drawable::setPosition(int _x, int _y) {
    model.setPosition({ _x, _y, 0 });
}

void Drawable::setSize(int _width, int _height) {
    model.setScale({ _width, _height, 1 });
}

void Drawable::setColor(glm::vec3 _color) {
    shader->color = _color;
}

void Drawable::setAlpha(float _alpha) {
    shader->alpha = _alpha;
}

void Drawable::setRotation(glm::vec3 _rotation) {
    model.setRotation(_rotation);
}

int Drawable::getX() {
    return model.getX();
}
int Drawable::getY() {
    return model.getY();
}
int Drawable::getWidth() {
    return model.getWidth();
}
int Drawable::getHeight() {
    return model.getHeight();
}

void Drawable::setCamera(std::shared_ptr<Camera> camera) {
    shader->setCamera(camera);
}

std::shared_ptr<Camera> Drawable::getCamera() {
    return shader->getCamera();
}

void Drawable::setShaderProgram(std::string shaderProgramName) {
    shader->setProgram(shaderProgramName);
}
void Drawable::setEffect(float _effect) {
    shader->effect = _effect;
}

void Drawable::setUniform(std::string key, float value) {
    shader->setFloatUniform(key, value);
}


