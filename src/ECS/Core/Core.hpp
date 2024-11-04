/*
** EPITECH PROJECT, 2024
** R-Type - Core : Core
** File description:
** Core class is the main class of the ECS.
** It will coordinate the behaviors of the managers.
*/
#pragma once

#include "../Component/ComponentManager/ComponentManager.hpp"
#include "../System/SystemManager/SystemManager.hpp"
#include "../Entity/EntityManager/EntityManager.hh"
#include "../Component/ComponentManager/ComponentTypeRegistry.hpp"
#include <cstddef>
#include <iostream>
#include <memory>

namespace ECS {
    namespace Core {

        /**
         * @brief The Core class coordinates the managers in the ECS (Entity-Component-System).
         *
         * It provides functions to manage entities, components, and systems within the ECS architecture.
         */
        class Core {

        public:
            Core();
            ~Core() = default;
            std::size_t createEntity();
            void destroyEntity(std::size_t entity);
            Signature getSignature(std::size_t entity) const;

            /**
             * @brief Registers a component type within the ECS.
             *
             * @tparam T The component type to be registered.
             */
            template<typename T>
            void registerComponent() {
                _componentManager->registerComponent<T>();
            }

            /**
             * @brief Retrieves a component from a specific entity.
             *
             * @tparam T The type of the component.
             * @param entity The ID of the entity to retrieve the component.
             * @return T& A reference to the component.
             */
            template<typename T>
            T& getComponent(std::size_t entity) {
                return _componentManager->getComponents<T>()[entity].value();
            }

            /**
             * @brief Retrieves all components of a specific type.
             *
             * @tparam T The type of the components.
             * @return ComponentManager::SparseArray<T>& A reference to the sparse array of components.
             */
            template<typename T>
            ComponentManager::SparseArray<T>& getComponents() {
                return _componentManager->getComponents<T>();
            }

            /**
             * @brief Registers a new system in the ECS.
             *
             * @tparam T The system type to be registered.
             * @return std::shared_ptr<T> A shared pointer to the newly registered system.
             */
            template<typename T>
            std::shared_ptr<T> registerSystem() {
                return _systemManager->registerSystem<T>();
            }

            /**
             * @brief Adds a component to an entity.
             *
             * Updates the entity's signature and notifies the system manager of the change.
             *
             * @tparam T The type of the component to be added.
             * @param entity The ID of the entity.
             * @param component The component to be added.
             */
            template<typename T>
            void addComponent(std::size_t entity, T component) {
                auto signature = _entityManager->getSignature(entity);

                signature.set(CTypeRegistry::getTypeId<T>(), true);
                _entityManager->setSignature(entity, signature);
                _systemManager->entitySignatureChanged(entity, signature);
                _componentManager->getComponents<T>().insertAt(entity, component);
            }

            template<typename... T>
            std::vector<std::size_t> getEntitiesWithComponent() const {
                std::vector<std::size_t> matchingEntities;
                auto entities = _entityManager->getEntities();
                std::bitset<32> temp;

                (temp.set(ECS::CTypeRegistry::getTypeId<T>(), true), ...);
                for (auto &entity : entities)
                    if ((getSignature(entity) & temp) == temp)
                        matchingEntities.push_back(entity);
                return matchingEntities;
            };
            
            /**
             * @brief Retrieves all entities with a matching signature.
             *
             * @param systemSignature The signature to match entities against.
             * @return std::vector<std::size_t> A vector of entity IDs with the matching signature.
             */
            std::vector<std::size_t> getEntitiesWithSignature(Signature systemSignature) const {
                std::vector<std::size_t> matchingEntities;
                auto entities = _entityManager->getEntities();

                for (auto &entity : entities) {
                    if ((getSignature(entity) & systemSignature) == systemSignature) {
                        matchingEntities.push_back(entity);
                    }
                }
                return matchingEntities;
            }

            /**
             * @brief Sets the signature for a specific system.
             *
             * @tparam T The system type.
             * @param signature The signature that the system should operate on.
             */
            template<typename T>
            void setSystemSignature(Signature signature) {
                _systemManager->setSignature<T>(signature);
            }

            /**
             * @brief Updates the signature of an entity.
             *
             * Notifies the system manager of any changes to the entity's signature.
             *
             * @param entity The ID of the entity.
             * @param signature The new signature for the entity.
             */
            void setEntitySignature(std::size_t entity, Signature signature) {
                _entityManager->setSignature(entity, signature);
                _systemManager->entitySignatureChanged(entity, signature);
            }

            template<typename T>
            Signature getSystemSignature() const {
                return _systemManager->getSignature<T>();
            }

            template<typename T>
            std::shared_ptr<T> getSystem() const {
                return _systemManager->getSystem<T>();
            }

        private:
            std::shared_ptr<ComponentManager::ComponentManager> _componentManager;
            std::shared_ptr<EntityManager::EntityManager> _entityManager;
            std::shared_ptr<SystemManager::SystemManager> _systemManager;
        };
    }
}
