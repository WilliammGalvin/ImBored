//
// Created by Willam Galvin on 2025-01-11.
//

#ifndef GAME_HPP
#define GAME_HPP

#include "GameState.hpp"
#include "UpdateManager.hpp"
#include "WindowScreen.hpp"

namespace core {

    struct Game : WindowScreen {
        Game(Window* window, std::chrono::milliseconds updateDelay);
        Game(Window* window);
        ~Game() override;

        void onUpdate() override;
        void onRender(sf::RenderTarget& target) override;

    protected:
        virtual void onStartUpdate() {}
        virtual void onStartRender(sf::RenderTarget& target) {}

        virtual void onGameUpdate() {}
        virtual void onGameRender(sf::RenderTarget& target) {}

        virtual void onEndUpdate() {}
        virtual void onEndRender(sf::RenderTarget& target) {}

        virtual sf::Vector2f getGameSize() const = 0;
        sf::Vector2f& getGameOffset();

    private:
        UpdateManager _updateManager;
        GameState _gameState;
        sf::Vector2f* _gameOffset = nullptr;

        std::map<GameState, std::function<void()>> _updateStateMap{};
        std::map<GameState, std::function<void(sf::RenderTarget&)>> _renderStateMap{};

        void initUpdateStateMap();
        void initRenderStateMap();
    };

}

#endif //GAME_HPP
