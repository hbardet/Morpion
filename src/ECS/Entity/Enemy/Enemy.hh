/*
** EPITECH PROJECT, 2024
** Enemy.hh
** File description:
** Enemy class
*/
#pragma once

#include <cstddef>
#include <iostream>

namespace ECS {
    namespace Entities {
        class Enemy {

        public:
            Enemy(std::size_t id);
            ~Enemy() = default;

            operator std::size_t() const;
            std::size_t getId() const;

        private:
            std::size_t _id;
        };
    }
}
