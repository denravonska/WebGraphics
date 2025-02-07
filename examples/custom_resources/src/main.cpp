﻿
#include "Engine/Engine.h"
#include "Engine/Looper.h"
#include "Drawables/Image.h"
#include "Drawables/Text.h"
#include "Drawables/View.h"
#include <vector>
#include <string>
#include <iostream>

int main(int argc, char* argv[]) {

    Looper looper;
    auto& engine = Engine::getInstance();
    engine.resources.loadDefaultResourceFiles();
    engine.setIconImage();

    Image image("background1");
    image.setShaderProgram("background");
    image.setSize(1920, 1080);   
  
    Text text;
    text.setText(L"Okay bro こんにちは世界 北島 美奈");
    text.setFont("Hosohuwafont");
    text.setPosition(100, 100);

    View view(200, 200);
    view.clear();
    view.setPosition(-100, -100);
    view.paint(image);
    view.paint(text);

    auto camera = view.getCamera();
    camera->setProjectionType(false);
    camera->setPosition({ 0.f, 0, -50.0f });
    camera->setYaw(90.0f);

    camera->setOrbitTarget({ 0, 0, 0 });
    camera->setOrbitDistance(700.0f);

    float r = 1.0f;
    looper.onRender = [&]() {

        auto& mouse = engine.window.mouse;
        float scroll = mouse.scrollDelta;

        float zoom = 0.f;
        bool zoomIn = mouse.isLeftPressed;
        bool zoomOut = mouse.isRightPressed;
        if (zoomIn)
            zoom = 10.0f;
        if (zoomOut)
            zoom = -10.0f;
        camera->orbit(scroll * 10.0f, 0.f, zoom);
    

        view.clear();
        view.paint(image);
        view.paint(text);
        view.setRotation({r,r,r});
        r = r + 1.0f;
        view.render();


    };

    looper.loop();

    return 0;
}



