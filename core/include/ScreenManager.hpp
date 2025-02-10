//
// Created by liamg on 2025-01-14.
//

#ifndef SCREENMANAGER_HPP
#define SCREENMANAGER_HPP

#include "Game.hpp"
#include "WindowScreen.hpp"
#include "../../home_screen/include/HomeScreen.hpp"

namespace core {

    class ScreenManager : public WindowScreen {
        std::map<Game*, std::string> _games{};
        home_screen::HomeScreen _homeScreen;

        WindowScreen* _currentScreen = nullptr;
        bool _inGame = false;

        Game* getCurrentGame(int gameIndex);
        WindowScreen& getCurrentScreen();

    public:
        ScreenManager(Window* window, KeybindManager* keybindManager);
        ~ScreenManager() override;

        void onUpdate() override;
        void onRender(sf::RenderTarget &target) override;

        void onKeyPressed(sf::Keyboard::Key key) override;

        void launchGame(int gameIndex);
        void exitGame();

        std::map<Game*, std::string>& getGames();
    };

}

#endif //SCREENMANAGER_HPP
