
#include "App.h"
#include <iostream>
#include "Drawables/Button.h"

Image image;
Button button;

App::App() {
    button.onPressCallback = []() { std::cout << "button clicked (lambda)...\n"; };
}

App::~App() {

}

void App::run()
{
    while (!engine.window.hasQuit())
    {
        if (updateTimer.isRenderUpdate())
            update();
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}

void App::resizeWindow(int _width, int _height)
{
    engine.window.resizeWindow(_width, _height);
}

void App::update(){
    if (updateTimer.isLogicUpdate()) {
        updateLogic();
        engine.window.pollEvents();
    }
    render();
}

void App::updateLogic() {
    int x = engine.window.mouse.x;
    int y = engine.window.mouse.y;
    std::pair<int, int> pos = engine.graphics.getPixelPosition(x, y);
    button.onHover(pos.first, pos.second);
    if (engine.window.mouse.isLeftPress) {
        std::cout << "mouse down L " << "x: " << pos.first << " y: " << pos.second << "\n";
        button.onPress(pos.first, pos.second);
    }
    if (engine.window.mouse.isLeftReleased) {
        std::cout << "mouse up L " << "x: " << pos.first << " y: " << pos.second << "\n";
        button.onRelease(pos.first, pos.second);
    }
    if (engine.window.mouse.isRightReleased) {
        std::cout << "mouse up R " << "x: " << pos.first << " y: " << pos.second << "\n";
    }
    image.isHighlighted = false;
    if (engine.window.keyboard.isPressed[GLFW_KEY_A]) {
        std::cout << "A isPressed" << std::endl;
        image.isHighlighted = true;
    }
    if (engine.window.keyboard.isDownClick[GLFW_KEY_A]) {
        std::cout << "A down press" << std::endl;
    }
    if (engine.window.keyboard.isUpClick[GLFW_KEY_A]) {
        std::cout << "A up press" << std::endl;
    }

}

void App::render() {
    engine.graphics.clearViews();
    renderViews();
    engine.graphics.display();
}

void App::renderViews(){
    Text text, text2;
    Rectangle rectangle;
    rectangle.x = 150;
    rectangle.y = 500;
    text2.text = "another text";
    text2.color = glm::vec4(1.0f, 1.0f, 0.0f, 1.0f);
    text2.rotation = 45.0f;
    text2.y = 400;
    text2.x = 100;
    image.x = 300;
    image.y = 300;
    engine.graphics.drawImage(image);
    engine.graphics.drawRectangle(rectangle);
    engine.graphics.drawText(text);
    engine.graphics.drawText(text2);

    button.setPosition(600, 100);
    Image btnImage = button.getImage();
    Text btnText = button.getText();
    engine.graphics.drawImage(btnImage);
    engine.graphics.drawText(btnText);
}