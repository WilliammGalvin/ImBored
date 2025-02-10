//
// Created by Willam Galvin on 2025-01-11.
//

#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <functional>
#include <SFML/Graphics.hpp>

namespace core {

    struct Window {
        sf::RenderWindow renderWindow;

        Window();

        void onRender(const std::function<void()>& func);
        void onUpdate(const std::function<void()>& func);
        void onEvent(const std::function<void(sf::Event& event)>& func);

        bool isWindowOpen() const;
        const sf::Vector2i& getWindowSize() const;
    private:
        sf::Vector2i _windowSize;
    };

}

#endif //WINDOW_HPP
