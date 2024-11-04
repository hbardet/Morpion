/*
** EPITECH PROJECT, 2024
** SystemManager.hpp
** File description:
** SystemManager class
*/
#pragma once

#include <cstddef>
#include <memory>
#include <iostream>
#include <unordered_map>
#include <typeinfo>
#include <bitset>
#include <unordered_set>

#include "../System/System.hpp"

using Signature = std::bitset<32>;

namespace ECS {
    namespace SystemManager {

        /**
        * @brief Manages the registration and updating of systems in the ECS architecture.
        *
        * The SystemManager class is responsible for registering systems, managing their signatures,
        * and handling entity updates when an entity is destroyed or its signature changes.
        */
        class SystemManager {
        public:

            /**
            * @brief Registers a system of type T.
            *
            * This method registers a new system of type T and stores it in the system map.
            * If the system type is already registered, it returns nullptr.
            *
            * @tparam T The system type to register.
            * @return A shared pointer to the newly registered system of type T.
            */
            template<typename T>
            std::shared_ptr<T> registerSystem() {
                std::string typeName = typeid(T).name();
                if (_mSystems.find(typeName) != _mSystems.end())
                    return nullptr;
                auto system = std::make_shared<T>();
                _mSystems[typeName] = system;
                return system;
            }

            /**
            * @brief Sets the signature for a system of type T.
            *
            * Associates a specific signature with a system of type T. The signature is used to
            * determine which entities the system should track.
            *
            * @tparam T The system type to associate the signature with.
            * @param signature The signature to associate with the system.
            * @return void.
            */
            template<typename T>
            void setSignature(Signature signature) {
                std::string typeName = typeid(T).name();
                if (_mSystems.find(typeName) == _mSystems.end())
                    return;
                _mSignatures[typeName] = signature;
            }

            /**
            * @brief An entity has been destroyed.
            *
            * This method removes the destroyed entity from all systems that track it.
            *
            * @param entity The ID of the destroyed entity.
            * @return void.
            */
            void entityDestroyed(std::size_t entity) {
                for (auto const& pair : _mSystems) {
                    auto const& system = pair.second;
                    system->_entities.erase(entity);
                }
            }

            /**
            * @brief An entity's signature has changed.
            *
            * This method updates the entity's signature and updates all systems that track the entity.
            *
            * @param entity The ID of the entity whose signature has changed.
            * @param entitySignature The new signature of the entity.
            * @return void.
            */
            void entitySignatureChanged(std::size_t entity, Signature entitySignature) {
                for (auto const& pair : _mSystems) {
                    auto const& type = pair.first;
                    auto const& system = pair.second;
                    auto const& systemSignature = _mSignatures[type];

                    if ((entitySignature & systemSignature) == systemSignature) {
                        system->_entities.insert(entity);
                    } else {
                        system->_entities.erase(entity);
                    }
                }
            }

            /**
            * @brief Gets the signature associated with a system of type T.
            *
            * This method returns the signature associated with a system of type T.
            * If the system type is not registered, it returns an empty signature.
            *
            * @tparam T The system type to get the signature for.
            * @return The signature associated with the system of type T.
            */
            template<typename T>
            Signature getSignature() {
                std::string typeName = typeid(T).name();
                if (_mSignatures.find(typeName) != _mSignatures.end()) {
                    return _mSignatures[typeName];
                }
                return Signature();
            }

            /**
            * @brief Gets a system of type T.
            *
            * This method returns a shared pointer to a system of type T.
            * If the system type is not registered, it returns nullptr.
            *
            * @tparam T The system type to get.
            * @return A shared pointer to the system of type T.
            */
            template<typename T>
            std::shared_ptr<T> getSystem() {
                std::string typeName = typeid(T).name();
                if (_mSystems.find(typeName) != _mSystems.end()) {
                    return std::static_pointer_cast<T>(_mSystems[typeName]);
                }
                return nullptr;
            }

        private:
            /**
            * @brief Stores the signature associated with each system type.
            *
            * This map associates a system type (as a string) with its corresponding signature.
            */
            std::unordered_map<std::string, Signature> _mSignatures;

            /**
            * @brief Stores the systems registered with the manager.
            *
            * This map associates a system type (as a string) with a shared pointer to the system.
            */
            std::unordered_map<std::string, std::shared_ptr<Systems::System> > _mSystems;
        };
    }
}
