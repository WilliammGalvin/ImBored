//
// Created by Willam Galvin on 2025-01-11.
//

#ifndef WINDOWSCREEN_HPP
#define WINDOWSCREEN_HPP

#include "FontManager.hpp"
#include "KeybindManager.hpp"
#include "Window.hpp"

namespace core {

    class WindowScreen {
        FontManager _fontManager{};

    protected:
        Window* window;
        KeybindManager* keybindManager;

    public:
        WindowScreen(Window* window, KeybindManager* keybindManager);
        virtual ~WindowScreen();

        virtual void onUpdate() = 0;
        virtual void onRender(sf::RenderTarget& target) = 0;

        virtual void onKeyPressed(sf::Keyboard::Key key) {}

        sf::Font& getFont();
    };

}

#endif //WINDOWSCREEN_HPP
