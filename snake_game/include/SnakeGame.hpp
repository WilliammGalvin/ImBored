//
// Created by Willam Galvin on 2025-01-11.
//

#ifndef SNAKEGAME_HPP
#define SNAKEGAME_HPP
#include "SnakeDir.hpp"
#include "../../core/include/Game.hpp"

namespace snake_game {

    class SnakeGame final : public core::Game {
        std::vector<sf::Vector2i> _segments{};
        SnakeDir _dir;

        const int _gridDim = 15;
        const int _startingSegments = 3;
        const int _startingHealth = 3;

        const float _tileSize = 32;

        void initSegments(const sf::Vector2i& startingPos);
        void renderGrid(sf::RenderTarget& target);
        void renderSnake(sf::RenderTarget& target);
        bool hasCollidedWithSelfOrWall() const;

        void onGameUpdate() override;
        void onGameRender(sf::RenderTarget &target) override;
    public:
        SnakeGame(core::Window* window);
        ~SnakeGame() override = default;

        void onKeyPressed(sf::Keyboard::Key key) override;
    };

}

#endif //SNAKEGAME_HPP
