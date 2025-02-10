#include "core/include/ScreenManager.hpp"
#include "core/include/Window.hpp"

int main() {
    core::Window window;
    core::KeybindManager keybindManager;
    core::ScreenManager screen(&window, &keybindManager);

    while (window.isWindowOpen()) {
        window.onEvent([&screen](sf::Event& event) {
            if (event.type == sf::Event::KeyPressed)
            screen.onKeyPressed(event.key.code);
        });

        window.onUpdate([&screen]() {
            screen.onUpdate();
        });

        window.onRender([&screen, &window]() {
            screen.onRender(window.renderWindow);
        });
    }

    return 0;
}
