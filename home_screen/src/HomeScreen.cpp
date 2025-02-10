//
// Created by liamg on 2025-01-14.
//

#include "../include/HomeScreen.hpp"

#include "../../core/include/ScreenManager.hpp"
#include "../../snake_game/include/SnakeGame.hpp"

home_screen::HomeScreen::HomeScreen(core::Window* window, core::KeybindManager* keybindManager, core::ScreenManager* screenManager)
    : WindowScreen(window, keybindManager), _screenManager(screenManager) {}

home_screen::HomeScreen::~HomeScreen() {
    delete _screenManager;
}

std::string home_screen::HomeScreen::getGameIconPath(core::Game* game) const {
    if (!_screenManager->getGames().contains(game)) {
        std::cerr << "Game icon not found." << std::endl;
        return "";
    }

    auto imgName = std::string(_screenManager->getGames().at(game));
    std::ranges::transform(imgName, imgName.begin(),
    [](const unsigned char c) {
        return std::tolower(c);
    });

    return "assets/game_icons/" + imgName + ".png";
}

void home_screen::HomeScreen::onRender(sf::RenderTarget &target) {
    auto gamePair = _screenManager->getGames().begin();
    std::advance(gamePair, _scrollIndex);

    sf::Texture texture;
    if (!texture.loadFromFile(getGameIconPath(gamePair->first))) {
        std::cerr << "Failed to load icon " << getGameIconPath(gamePair->first) << std::endl;
        return;
    }

    const float imgScale = 9.0f;
    const float textTopPadding = 8.0f;

    sf::Sprite sprite(texture);
    sprite.setScale(imgScale, imgScale);
    sprite.setPosition(
        (sf::Vector2f(window->getWindowSize()) - _gameIconSize * imgScale) / 2.0f
    );

    sf::Text text;
    text.setFont(getFont());
    text.setString(gamePair->second);
    text.setCharacterSize(25);
    text.setFillColor(sf::Color::White);
    text.setPosition(sf::Vector2f{
        (static_cast<float>(window->getWindowSize().x) - text.getGlobalBounds().width) / 2.0f,
        (static_cast<float>(window->getWindowSize().y) + _gameIconSize.y * imgScale) / 2.0f + text.getGlobalBounds().height + textTopPadding
    });

    target.draw(sprite);
    target.draw(text);
}

void home_screen::HomeScreen::onKeyPressed(sf::Keyboard::Key key) {
    if (key == sf::Keyboard::Left && _scrollIndex > 0)
        _scrollIndex--;

    if (key == sf::Keyboard::Right && _scrollIndex < _screenManager->getGames().size() - 1)
        _scrollIndex++;

    if (key == keybindManager->keyBinds.at(core::Keybind::PLAY_GAME))
        _screenManager->launchGame(_scrollIndex);
}
