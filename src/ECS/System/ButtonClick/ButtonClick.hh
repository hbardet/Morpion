/*
** EPITECH PROJECT, 2024
** RenderText class.hh
** File description:
** ButtonClick system class
*/

#pragma once

#include "../System/System.hpp"
#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/Button/Button.hh"

namespace ECS {
    namespace Systems {
        class ButtonClickSystem : public System {
            public:
                void update(ECS::ComponentManager::SparseArray<ECS::Components::Button> &buttons,
                        const std::vector<std::size_t> &entities);

            private:
        };
    };
}
