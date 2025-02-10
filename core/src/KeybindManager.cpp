//
// Created by liamg on 2025-01-14.
//

#include "../include/KeybindManager.hpp"

core::KeybindManager::KeybindManager() {
    keyBinds.insert(std::pair{ PLAY_GAME, sf::Keyboard::Space });
    keyBinds.insert(std::pair{ EXIT_GAME, sf::Keyboard::Escape });
    keyBinds.insert(std::pair{ PAUSE_GAME, sf::Keyboard::P });
    keyBinds.insert(std::pair{ SETTINGS, sf::Keyboard::O });
}
