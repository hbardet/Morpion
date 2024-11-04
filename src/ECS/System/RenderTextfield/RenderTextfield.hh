/*
** EPITECH PROJECT, 2024
** R-Type - Systems : TextFieldRender
** File description:
** System to handle TextField render
*/

#pragma once

#include "raylib-cpp.hpp"
#include "../../Component/Textfield/Textfield.hh"
#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/Text/Text.hh"
#include "../../Component/Position/Position.hpp"
#include "../System/System.hpp"

namespace ECS {
    namespace Systems {
        class RenderTextFieldSystem : public System {
        public:
            void update(
                ECS::ComponentManager::SparseArray<ECS::Components::TextField> &textFields,
                ECS::ComponentManager::SparseArray<ECS::Components::Text> &texts,
                ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
                const std::vector<std::size_t> &entities
            );
        };
    }
}
