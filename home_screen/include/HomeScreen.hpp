//
// Created by liamg on 2025-01-14.
//

#ifndef HOMESCREEN_HPP
#define HOMESCREEN_HPP

#include "../../core/include/Game.hpp"

namespace core {
    class ScreenManager;
}

namespace home_screen {

    class HomeScreen : public core::WindowScreen {
        core::ScreenManager* _screenManager;
        int _scrollIndex = 0;

        const sf::Vector2f _gameIconSize = sf::Vector2f{ 32, 32 };

        std::string getGameIconPath(core::Game* game) const;

    public:
        HomeScreen(core::Window* window, core::KeybindManager* keybindManager, core::ScreenManager* screenManager);
        ~HomeScreen() override;

        void onUpdate() override {}
        void onRender(sf::RenderTarget &target) override;

        void onKeyPressed(sf::Keyboard::Key key) override;
    };

}

#endif //HOMESCREEN_HPP
