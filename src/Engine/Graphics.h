#include "Utility/GLData.h"
#include "Window/Window.h"
#include "Window/Image.h"
#include "Utility/MatrixData.h"
#include "Window/Shader.h"
#include "Window/Text.h"
#include "Window/Framebuffer.h"
#include "Window/Camera.h"

#include <stack>
#include <tuple>
#include <functional>
#include <chrono>
#include <thread>
#include <string>
#include <iostream>
#include <vector>


#ifndef GRAPHICS_H
#define GRAPHICS_H

class Graphics {

    Camera camera;
    Image image;
    Shader* imageUniform = nullptr;
    Framebuffer framebuffer;

    Text text;
    GLData glData;

    void preDraw();

    int windowWidth, windowHeight;
    Window& window;
public:
    Graphics(Window& _window);
    ~Graphics();

    void draw();

};

#endif // !GRAPHICS_H
