/*
** EPITECH PROJECT, 2024
** R-Type - Components : Background
** File description:
** Background Component
*/

#pragma once

#include <iostream>

namespace ECS {
    namespace Components {

        class Background {
        public:
            Background(float width, float speed) {
                _width = width;
                _speed = speed;
            }
            ~Background() = default;
            void setWidth(float width) { _width = width; }
            void setSpeed(float speed) { _speed = speed; }
            float getWidth() const { return _width; }
            float getSpeed() const { return _speed; }

        private:
            float _width;
            float _speed;
        };
    }
}
