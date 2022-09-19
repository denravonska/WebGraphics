#include "GameView.h"
#include <Drawables/Rect.h>

GameView::GameView(Engine& _engine, Game& _game) : engine(_engine), game(_game), view(_engine, 1920, 1080) {
}

void GameView::render() {
    view.clear();
    paint();
    view.render();
}

void GameView::addZoomStep(float _zoom) {
    if (_zoom > 0)
        zoom = zoom + 0.5f;
    if (_zoom < 0)
        zoom = zoom - 0.5f;
    zoom = std::clamp<float>(zoom, -0.5f, 5.0f);
}

void GameView::resetZoom() {
    zoom = 1.0f;
    view.setSize(zoom * view.getPixelWidth(), zoom * view.getPixelHeight());
}

void GameView::paint() {
    float r = 0.0f;
    float g = 0.0f;
    float b = 0.0f;
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 70; j++) {
            Rect rect(engine);
            rect.setSize(100, 100);
            rect.setColor(glm::vec3(r, g, b));
            rect.setPosition(i * 100 + game.getPlayerX(), j * 100 + game.getPlayerY());
            rect.setRadius(0.2f);
            view.paint(rect);
            r += 0.001f;
            g = 1.0f - (1.0f * r);
            b += 0.005f;
        }
    }
}