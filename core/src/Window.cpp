//
// Created by Willam Galvin on 2025-01-11.
//

#include <SFML/Graphics.hpp>
#include "../include/Window.hpp";

#include <iostream>

core::Window::Window() {
    _windowSize = sf::Vector2i{ 800, 600 };

    renderWindow.create(
        sf::VideoMode(
            getWindowSize().x,
            getWindowSize().y
            ),
        "Im Bored."
    );
}

void core::Window::onRender(const std::function<void()>& func) {
    renderWindow.clear(sf::Color::Black);
    func();
    renderWindow.display();
}

void core::Window::onUpdate(const std::function<void()>& func) {
    func();
}

void core::Window::onEvent(const std::function<void(sf::Event& event)> &func) {
    sf::Event e{};

    while (renderWindow.pollEvent(e)) {
        if (e.type == sf::Event::Closed) {
            renderWindow.close();
            return;
        }

        func(e);
    }
}


bool core::Window::isWindowOpen() const {
    return renderWindow.isOpen();
}

const sf::Vector2i& core::Window::getWindowSize() const {
    return _windowSize;
}
