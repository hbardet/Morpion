/*
** EPITECH PROJECT, 2024
** R-Type - Components : Pod
** File description:
** Pod Component
*/
#pragma once

#include <iostream>

namespace ECS {
    namespace Components {

        class Pod {
        public:
            Pod(std::size_t player = 10000);

            std::size_t getPlayer();
            void setPlayer(std::size_t player);

            int getLevel();
            void setLevel(int level);

            bool isUp();
            void setIsUp(bool isUp);

            int getCooldown();
            void setCooldown(int cooldown);

        private:
            std::size_t _player;
            int _level;
            bool _isUp;
            std::size_t _cooldown;
        };
    }
}
