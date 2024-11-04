/*
** EPITECH PROJECT, 2024
** R-Type - Components : Position
** File description:
** Position Component
*/
#pragma once

#include <iostream>
#include <tuple>

namespace ECS {
    namespace Components {

        class Position {
        public:
            Position(float x, float y, float z = 0);
            ~Position() = default;

            float getX() const;
            float getY() const;
            float getZ() const;
            float getOriginalX() const;
            float getOriginalY() const;
            float getOriginalZ() const;
            void setX(float x);
            void setY(float y);
            void setZ(float z);
            std::pair<float, float> getPosPair() const;
            std::tuple<float, float, float> getPosition() const;
        private:
            float _xOriginalPos;
            float _yOriginalPos;
            float _zOriginalPos;
            float _x;
            float _y;
            float _z;
        };

        inline std::ostream & operator<< (std::ostream & stream, const Position & position) {
            stream << "(" << position.getX() << ", " << position.getY() << ")";
            return stream;
        }
    }
}
