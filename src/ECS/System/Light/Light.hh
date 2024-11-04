/*
** EPITECH PROJECT, 2024
** SystemLight.hh
** File description:
** SystemLight class
*/
#pragma once

#include <vector>
#include "../System/System.hpp"
#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/Position/Position.hpp"
#include "../../Component/Light/Light.hh"
#include "../../RessourcePool/RessourcePool.hh"
#include "../../Utils/Utils.hh"

namespace ECS {
    namespace Systems {

        /**
        * @brief System to render 2D entities.
        *
        * The SystemLight class is responsible for rendering entities in a 2D space. It retrieves
        * the position and 2D rendering components (Light) of each entity and draws the png using
        * the `raylib` library.
        */
        class SystemLight: public System {
        public:
            /**
            * @brief Default constructor for SystemLight.
            */
            SystemLight() = default;

            /**
            * @brief Default destructor for SystemLight.
            */
            ~SystemLight() = default;

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
            void update(
                        ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
                        ECS::ComponentManager::SparseArray<ECS::Components::Light> &lights,
                        std::vector<std::size_t> &entities,
                        ECS::RessourcePool &ressourcePool
                        );
        };
    }
}
