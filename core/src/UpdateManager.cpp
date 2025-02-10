//
// Created by Willam Galvin on 2025-01-12.
//

#include "../include/UpdateManager.hpp"
core::UpdateManager::UpdateManager(std::chrono::milliseconds delay)
    : _delay(delay) {
    resetLastUpdate();
}

bool core::UpdateManager::isCycleOver() const {
    return getCurrentTime() - _lastUpdate >= _delay;
}

long long core::UpdateManager::getDelay() const {
    return _delay.count();
}

void core::UpdateManager::setDelay(std::chrono::milliseconds delay) {
    _delay = delay;
}

std::chrono::system_clock::time_point core::UpdateManager::getCurrentTime() const {
    return std::chrono::system_clock::now();
}

void core::UpdateManager::resetLastUpdate() {
    _lastUpdate = getCurrentTime();
}



