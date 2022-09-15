#include "MainMenu.h"
#include <iostream>
#include "SettingsPanel.h"
#include "LobbyPanel.h"

MainMenu::MainMenu(Engine& _engine) : Panel(_engine, "main_menu") {
    uiScript.addMethod("onSettings", [&]() {
        if (canSetChildPanel())
            setChildPanel(new SettingsPanel(engine));
        });
    uiScript.addMethod("onLobby", [&]() {
        if (canSetChildPanel())
            setChildPanel(new LobbyPanel(engine));
        });
}

void MainMenu::onEnter() {
    std::cout << "onEnter() MainMenu\n";

}

void MainMenu::update() {

}
void MainMenu::render() {

}



