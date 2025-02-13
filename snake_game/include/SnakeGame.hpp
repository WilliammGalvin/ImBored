//
// Created by Willam Galvin on 2025-01-11.
//

#ifndef SNAKEGAME_HPP
#define SNAKEGAME_HPP

#include "SnakeDir.hpp"
#include "../../core/include/Game.hpp"

namespace snake_game {

    class SnakeGame final : public core::Game {
        std::vector<sf::Vector2i> _segments{}, _apples{};
        SnakeDir _dir;
        int _score = 0;

        const int _gridDim = 15;
        const int _startingSegments = 3;
        const int _maxAppleCount = 1;

        const float _tileSize = 32;

        void initSegments(const sf::Vector2i& startingPos);
        sf::Vector2f getGameSize() const override;

        void renderGrid(sf::RenderTarget& target);
        void renderSnake(sf::RenderTarget& target);
        void renderApples(sf::RenderTarget& target);
        void renderUI(sf::RenderTarget& target);

        void onGameEnd();

        bool hasCollidedWithSelfOrWall() const;
        int hasCollidedWithApple(const sf::Vector2i& headPos) const;

        sf::Vector2i getNewApplePos() const;
        void checkAndAddApples();

        void onGameUpdate() override;
        void onGameRender(sf::RenderTarget &target) override;

    public:
        SnakeGame(core::Window* window, core::KeybindManager* keybindManager, core::ScreenManager* screenManager);
        ~SnakeGame() override = default;

        void onKeyPressed(sf::Keyboard::Key key) override;

        Game* createNewInstance() const override;

    };

}

#endif //SNAKEGAME_HPP
