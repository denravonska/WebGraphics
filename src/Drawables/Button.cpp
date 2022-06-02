#include "Button.h"
#include <iostream>

void Button::onPress(int _x, int _y) {
    if (isPointerInside(_x, _y)) {
        isPressed = true;
        image.extraColor = glm::vec3(0.0f, 1.0f, 0.0f);
    }
    else {
        isPressed = false;
        image.extraColor = glm::vec3(0.0f, 0.0f, 0.0f);
    }
}
void Button::onRelease(int _x, int _y) {
    if (isPressed && isPointerInside(_x, _y) && onPressCallback) {
        onPressCallback();
    }
    image.extraColor = glm::vec3(0.0f, 0.0f, 0.0f);
    isPressed = false;
    onHover(_x, _y);
}

void Button::onHover(int _x, int _y) {
    if (isPointerInside(_x, _y)) {
        image.isHighlighted = true;
        if(!isPressed)
            image.extraColor = glm::vec3(1.0f, 0.0f, 0.0f);
    }
    else {
        image.isHighlighted = false;
        if(!isPressed)
            image.extraColor = glm::vec3(0.0f, 0.0f, 0.0f);
    }
}

bool Button::isPointerInside(int _x, int _y) {
    int x = image.x;
    int y = image.y;
    int w = image.width;
    int h = image.height;
    return _x >= x && _x <= x + w && _y >= y && _y <= y + h;
}

void Button::setSize(int _width, int _height) {
    image.width = _width;
    image.height = _height;
}

void Button::setPosition(int _x, int _y) {
    image.x = _x;
    image.y = _y;
    text.x = _x;
    text.y = _y;
}

Image Button::getImage() {
    return image;
}

Text Button::getText() {
    return text;
}
