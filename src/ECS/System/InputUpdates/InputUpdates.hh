/*
** EPITECH PROJECT, 2024
** R-Type - Systems : InputUpdates
** File description:
** Update informations based on inputs.
*/
#pragma once

#include "../System/System.hpp"

#include "../../Component/ComponentManager/SparseArray.hpp"
#include "../../Component/Input/Input.hh"
#include "../../Component/Velocity/Velocity.hh"
#include <cstddef>

namespace ECS {
    namespace Systems {

        /**
        * @brief System for handling updates based on user inputs.
        *
        * The InputUpdates system is responsible for updating components of entities based on the
        * inputs provided.
        */
        class InputUpdates : public System{
        public:
            /**
            * @brief Default constructor for InputUpdates.
            */
            InputUpdates() = default;

            /**
            * @brief Default destructor for InputUpdates.
            */
            ~InputUpdates() = default;

            /**
            * @brief Updates the input components of entities based on provided inputs.
            *
            * This method processes the input components of entities and updates them according
            * to the user input values. It checks the input array and associates them with
            * the respective entities.
            *
            * @param inputs Vector of input entity IDs to process.
            * @param inputComponents SparseArray containing the Input components of the entities.
            * @param entities Vector of entity IDs whose input components need to be updated.
            * @return The ID of the entity whose inputs were successfully updated.
            */
            std::size_t updateInputs(const std::vector<std::size_t> & inputs,
                              ECS::ComponentManager::SparseArray<ECS::Components::Input> & inputComponents,
                              std::vector<std::size_t> entities);

            /**
            * @brief Updates the velocity of entities based on their input components.
            *
            * This method updates the velocity components of entities based on their respective
            * input components.
            *
            * @param inputs SparseArray containing the Input components of entities.
            * @param velocities SparseArray containing the Velocity components of entities.
            * @param entities Vector of entity IDs to update the velocity for.
            * @return void.
            */
            void updateInputedVelocity(
                ECS::ComponentManager::SparseArray<ECS::Components::Input> & inputs,
                ECS::ComponentManager::SparseArray<ECS::Components::Velocity> & velocitites,
                std::vector<std::size_t> entities);

        };
    }
}
