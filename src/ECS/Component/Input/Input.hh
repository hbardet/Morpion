/*
** EPITECH PROJECT, 2024
** R-Type - Components : Input
** File description:
** Input Component
*/
#pragma once

#include <iostream>
#include <vector>

namespace ECS {
    namespace Components {

        class Input {
        public:
            Input();
            ~Input() = default;

            void setInputs(const std::vector<std::size_t> & inputs);
            std::vector<std::size_t> getInputs() const;

            bool contains(std::size_t toSearch);

        private:
            std::vector<std::size_t> _lastInputs;
        };
    }
}
