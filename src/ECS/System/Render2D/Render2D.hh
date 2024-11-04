/*
** EPITECH PROJECT, 2024
** SystemRender2D.hh
** File description:
** SystemRender2D class
*/
#pragma once

#include <vector>
#include "../System/System.hpp"
#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/Position/Position.hpp"
#include "../../Component/Render2D/Render2D.hh"
#include "../../RessourcePool/RessourcePool.hh"
#include "../../Utils/Utils.hh"

namespace ECS {
    namespace Systems {

        /**
        * @brief System to render 2D entities.
        *
        * The SystemRender2D class is responsible for rendering entities in a 2D space. It retrieves
        * the position and 2D rendering components (Render2D) of each entity and draws the png using
        * the `raylib` library.
        */
        class SystemRender2D: public System {
        public:
            /**
            * @brief Default constructor for SystemRender2D.
            */
            SystemRender2D() = default;

            /**
            * @brief Default destructor for SystemRender2D.
            */
            ~SystemRender2D() = default;

            /**
            * @brief Updates and renders 2D entities.
            *
            * This method updates the rendering of entities in a 2D environment. It retrieves the
            * position and render components for each entity and renders the models using the
            * appropriate resources from the resource pool.
            *
            * @param positions SparseArray of Position components, where the positions of entities are stored.
            * @param renders SparseArray of Render3D components, where the render information of entities is stored.
            * @param entities Vector of entity indices that need to be rendered.
            * @param ressourcePool The resource pool that holds models and textures used for rendering.
            * @return void.
            */
            void update(ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
                        ECS::ComponentManager::SparseArray<ECS::Components::Render2D> &renders,
                        std::vector<std::size_t> &entities,
                        ECS::RessourcePool &ressourcePool
                        );
        };
    }
}
