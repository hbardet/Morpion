/*
** EPITECH PROJECT, 2024
** SystemRender3D.hh
** File description:
** SystemRender3D class
*/
#pragma once

#include <vector>
#include "../System/System.hpp"
#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/Position/Position.hpp"
#include "../../Component/Rotate/Rotate.hh"
#include "../../Component/Scale/Scale.hh"
#include "../../Component/Render3D/Render3D.hh"
#include "../../RessourcePool/RessourcePool.hh"
#include "../../Utils/Utils.hh"

namespace ECS {
    namespace Systems {

        /**
        * @brief System to render 3D entities.
        *
        * The SystemRender3D class is responsible for rendering entities in a 3D space. It retrieves
        * the position and 3D rendering components (Render3D) of each entity and draws the models using
        * the `raylib` library.
        */
        class SystemRender3D: public System {
        public:
            /**
            * @brief Default constructor for SystemRender3D.
            */
            SystemRender3D() = default;

            /**
            * @brief Default destructor for SystemRender3D.
            */
            ~SystemRender3D() = default;

            /**
            * @brief Updates and renders 3D entities.
            *
            * This method updates the rendering of entities in a 3D environment. It retrieves the
            * position and render components for each entity and renders the models using the
            * appropriate resources from the resource pool.
            *
            * @param positions SparseArray of Position components, where the positions of entities are stored.
            * @param renders SparseArray of Render3D components, where the render information of entities is stored.
            * @param entities Vector of entity indices that need to be rendered.
            * @param ressourcePool The resource pool that holds models and textures used for rendering.
            * @param camera The 3D camera used for rendering the scene.
            * @return void.
            */
            void update(ECS::ComponentManager::SparseArray<ECS::Components::Position> &positions,
                        ECS::ComponentManager::SparseArray<ECS::Components::Rotate> &rotates,
                        ECS::ComponentManager::SparseArray<ECS::Components::Scale> &scales,
                        ECS::ComponentManager::SparseArray<ECS::Components::Render3D> &renders,
                        std::vector<std::size_t> &entities,
                        ECS::RessourcePool &ressourcePool,
                        raylib::Camera3D &camera);
        };
    }
}
