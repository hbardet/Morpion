/*
** EPITECH PROJECT, 2024
** R-Type - Components : Velocity
** File description:
** Velocity Component
*/
#pragma once

#include <iostream>

namespace ECS {
    namespace Components {

        class Velocity {
        public:
            Velocity(float x, float y);
            Velocity(std::pair<float, float> vel);
            ~Velocity() = default;

            float getX() const;
            float getY() const;
            void setX(float x);
            void setY(float y);
            std::pair<float, float> getVelPair() const;

            void setVelPair(std::pair<float, float> vel);

        private:
            float _x;
            float _y;
        };

        inline std::ostream & operator<< (std::ostream & stream, const Components::Velocity & velocity) {
            stream << "(" << velocity.getX() << ", " << velocity.getY() << ")";
            return stream;
        }
    }
}
