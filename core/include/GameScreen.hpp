//
// Created by liamg on 2025-02-12.
//

#ifndef GAMESCREEN_HPP
#define GAMESCREEN_HPP
#include "Game.hpp"
#include "WindowScreen.hpp"

namespace core {

    class GameScreen : public WindowScreen {
        Game* _currentGame;

    public:
        GameScreen(Game* game, Window* window, KeybindManager* keybindManager);
        ~GameScreen() override;

        void onUpdate() override;

        void onRender(sf::RenderTarget &target) override;

        void onKeyPressed(sf::Keyboard::Key key) override;
    };

}

#endif //GAMESCREEN_HPP
