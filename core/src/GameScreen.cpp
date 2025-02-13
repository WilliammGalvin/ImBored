//
// Created by liamg on 2025-02-12.
//

#include "../include/GameScreen.hpp"

core::GameScreen::GameScreen(Game* game, Window* window, KeybindManager* keybindManager) :
    WindowScreen(window, keybindManager), _currentGame(game) {}

core::GameScreen::~GameScreen() {
    delete _currentGame;
}

void core::GameScreen::onUpdate() {
    _currentGame->onUpdate();
}

void core::GameScreen::onRender(sf::RenderTarget& target) {
    _currentGame->onRender(target);
}

void core::GameScreen::onKeyPressed(sf::Keyboard::Key key) {
    _currentGame->onKeyPressed(key);
}
