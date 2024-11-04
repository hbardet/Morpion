/*
** EPITECH PROJECT, 2024
** R-Type - Systems : TextFieldInput
** File description:
** System to handle TextField input
*/

#pragma once

#include <vector>
#include "../../Component/Textfield/Textfield.hh"
#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../System/System.hpp"
#include "raylib-cpp.hpp"

namespace ECS {
    namespace Systems {

        class TextFieldInputSystem : public System {
        public:
            void update(ECS::ComponentManager::SparseArray<ECS::Components::TextField> &textFields,
                        const std::vector<std::size_t> &entities);

        private:
            void handleKeyboardInput(ECS::Components::TextField &textField);
        };

    }
}
