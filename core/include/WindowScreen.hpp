//
// Created by Willam Galvin on 2025-01-11.
//

#ifndef WINDOWSCREEN_HPP
#define WINDOWSCREEN_HPP

#include "Window.hpp"

namespace core {

    struct WindowScreen {
        WindowScreen(Window* window);
        virtual ~WindowScreen();

        virtual void onUpdate() = 0;
        virtual void onRender(sf::RenderTarget& target) = 0;

        virtual void onKeyPressed(sf::Keyboard::Key key) {}
    protected:
        Window* window;
    };

}

#endif //WINDOWSCREEN_HPP
