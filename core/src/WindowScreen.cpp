//
// Created by Willam Galvin on 2025-01-11.
//

#include "../include/WindowScreen.hpp"

core::WindowScreen::WindowScreen(Window* window, KeybindManager* keybindManager)
    : window(window), keybindManager(keybindManager) {}

core::WindowScreen::~WindowScreen() {
    delete window;
    delete keybindManager;
}

sf::Font& core::WindowScreen::getFont() {
    return _fontManager.getFont();
}

