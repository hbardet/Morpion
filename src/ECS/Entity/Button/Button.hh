/*
** EPITECH PROJECT, 2024
** Button.hh
** File description:
** Button entity class
*/
#pragma once

#include <cstddef>
#include <iostream>

namespace ECS {
    namespace Entities {
        class Button {

        public:
            Button(std::size_t id);
            ~Button() = default;

            operator std::size_t() const;
            std::size_t getId() const;

        private:
            std::size_t _id;
        };
    }
}
