#include "core/include/Window.hpp"
#include "snake_game/include/SnakeGame.hpp"

int main() {
    core::Window window;
    snake_game::SnakeGame game(&window);

    while (window.isWindowOpen()) {
        window.onEvent([&game](sf::Event& event) {
            if (event.type == sf::Event::KeyPressed)
            game.onKeyPressed(event.key.code);
        });

        window.onUpdate([&game]() {
            game.onUpdate();
        });

        window.onRender([&game, &window]() {
            game.onRender(window.renderWindow);
        });
    }

    return 0;
}
