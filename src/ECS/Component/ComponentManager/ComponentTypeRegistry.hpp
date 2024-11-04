/*
** EPITECH PROJECT, 2024
** R-Type - ComponentManager : ComponentTypeRegistry
** File description:
** The Component Registry assigns a unique index to each component type when the static function getTypeId<T> is called.
*/

/**
 * @file ComponentTypeRegistry.hpp
 * @brief ComponentTypeRegisty class declaration.
 * It manages the Ids of the different component types 
 *
 * This class assigns a unique std:size_t id to the given type when the 
 * getTypeId<Component> function is called for the first time for a type.
 * It retrieves the corresponding id if the component type has already been registered.
 */

#pragma once

#include <iostream>
#include <unordered_map>
#include <functional>
#include <memory>
#include <typeindex>

namespace ECS {
    namespace ComponentManager {

        /**
         * @brief ComponentTypeRegisty class declaration.
         * It manages the Ids of the different component types 
         *
         * This class assigns a unique std:size_t id to the given type when the 
         * getTypeId<Component> function is called for the first time for a type.
         * It retrieves the corresponding id if the component type has already been registered.
         */
        class ComponentTypeRegistry {
        public:

            /**
             * @brief TypeId static access.
             *
             * Returns a new index for the given type if it's the first time it's called.
             * Returns the corresponding index if it has already been mapped.
             *
             * @tparam Component Component Type to be mapped or returned.
             * @return Index of the mapped type.
             */
            template <typename Component>
            static std::size_t getTypeId() {
                static std::size_t index = nextTypeIndex++;
                if (indexToTypeMap.count(index) == 0) {
                    // Enregistrement dans la map inverse
                    indexToTypeMap[index] = []() -> std::type_index {
                        return std::type_index(typeid(Component));
                    };
                }
                return index;
            }

            static std::type_index getTypeFromId(std::size_t id) {
                if (indexToTypeMap.count(id) == 0) {
                    throw std::runtime_error("Invalid TypeId: no such type registered.");
                }
                return indexToTypeMap.at(id)();
            }
        
        private:
            /**
             * @brief Static variable used to assign a new index to each new type.
             *
             * It is incremented each time getTypeId() is called with a new type.
             */
            static std::size_t nextTypeIndex; // Utilisé pour générer des ID uniques
            static std::unordered_map<std::size_t, std::function<std::type_index()>> indexToTypeMap;
        };
    }

    /**
     * @brief ComponentManager::ComponentTypeRegistry namespace access
     *
     * Used mainly for easier access and code clarity.
     */
    using CTypeRegistry = ComponentManager::ComponentTypeRegistry;
}
