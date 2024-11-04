/*
** EPITECH PROJECT, 2024
** R-Type - Components : Hitbox
** File description:
** Hitbox Component
*/
#pragma once

#include <iostream>

namespace ECS {
    namespace Components {

        class Hitbox {
        public:
            Hitbox(float width, float height);
            ~Hitbox() = default;
            float getWidth() const;
            float getHeight() const;
            void setWidth(float width);
            void setHeight(float height);

        private:
            float _width;
            float _height;
        };
    }
}
