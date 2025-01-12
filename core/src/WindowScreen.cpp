//
// Created by Willam Galvin on 2025-01-11.
//

#include "../include/WindowScreen.hpp"

core::WindowScreen::WindowScreen(Window *window) : window(window) {}

core::WindowScreen::~WindowScreen() {
    delete window;
}

