//
// Created by Willam Galvin on 2025-01-11.
//

#ifndef UPDATEMANAGER_HPP
#define UPDATEMANAGER_HPP
#include <chrono>

namespace core {

    class UpdateManager {
        std::chrono::system_clock::time_point _lastUpdate;
        std::chrono::milliseconds _delay;

        std::chrono::system_clock::time_point getCurrentTime() const;
    public:
        UpdateManager(std::chrono::milliseconds delay);

        bool isCycleOver() const;
        void resetLastUpdate();

        long long getDelay() const;
        void setDelay(std::chrono::milliseconds delay);
    };

}

#endif //UPDATEMANAGER_HPP
