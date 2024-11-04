/*
** EPITECH PROJECT, 2024
** R-Type - Components : Rotate
** File description:
** Position Component
*/
#pragma once

#include <iostream>

namespace ECS {
    namespace Components {

        class Rotate {
        public:
            Rotate(float x, float y, float z);
            ~Rotate() = default;

            float getRoll() const;
            float getPitch() const;
            float getYaw() const;
            void setRotate(float roll, float pitch, float yaw);
            void setRoll(float roll);
            void setPitch(float pitch);
            void setYaw(float yaw);

        private:
            float _roll;
            float _pitch;
            float _yaw;
        };
    }
}
