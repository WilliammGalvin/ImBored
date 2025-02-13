//
// Created by liamg on 2025-01-14.
//

#ifndef FROGGERGAME_HPP
#define FROGGERGAME_HPP
#include "LaneTypes.hpp"
#include "../../core/include/Game.hpp"

namespace frogger_game {

    class FroggerGame : public core::Game {
        std::map<int, LaneTypes> _laneTypes{};
        std::vector<std::vector<sf::Vector2i>> _tiles{};
        sf::Vector2i _frogPos{};
        int _score = 0;

        const int _hazardLanes = 2;
        const int _hazardSize = 4;
        const int _rowSize = 11;
        const int _tileSize = 40;

        void generateLaneTypes();
        void generateTiles();
        void spawnFrog();

        sf::Color getColorFromLaneType(LaneTypes laneType) const;

        void renderTiles(sf::RenderTarget& target);
        void renderFrog(sf::RenderTarget& target);
        void renderUI(sf::RenderTarget& target);

        void onGameUpdate() override;
        void onGameRender(sf::RenderTarget& target) override;

        void onKeyPressed(sf::Keyboard::Key key) override;

        int getTotalLaneCount() const;
        sf::Vector2f getGameSize() const override;

    public:
        FroggerGame(core::Window* window, core::KeybindManager* keybindManager, core::ScreenManager* screenManager);
        ~FroggerGame() override = default;

        Game* createNewInstance() const override;
    };

}

#endif //FROGGERGAME_HPP
