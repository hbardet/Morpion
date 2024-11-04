/*
** EPITECH PROJECT, 2024
** Missile.hh
** File description:
** EntityManeger class
*/
#pragma once

#include <cstddef>
#include <iostream>

namespace ECS {
    namespace Entities {
        class Missile {

        public:
            Missile(std::size_t id);
            ~Missile() = default;

            operator std::size_t() const;
            std::size_t getId() const;

        private:
            std::size_t _id;
        };
    }
}
