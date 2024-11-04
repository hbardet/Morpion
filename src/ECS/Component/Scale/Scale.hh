/*
** EPITECH PROJECT, 2024
** R-Type - Components : Scale
** File description:
** Scale Component
*/
#pragma once

#include <iostream>

namespace ECS {
    namespace Components {

        class Scale {
        public:
            Scale(float scale);
            ~Scale() = default;

            float getScale() const;
            void setScale(float scale);

        private:
            float _scale;
        };
    }
}
