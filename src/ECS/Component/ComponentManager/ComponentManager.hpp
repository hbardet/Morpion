/*
** EPITECH PROJECT, 2024
** R-Type - ComponentManager : ComponentManager
** File description:
** ComponentManager handles the management of component SparseArrays.
*/
#include "SparseArray.hpp"
#include "ComponentTypeRegistry.hpp"
#include <functional>
#include <unordered_map>
#include <typeindex>
#include <bitset>
#include <any>
#include <optional>
#include <iostream>

using Signature = std::bitset<32>;

namespace ECS {
    namespace ComponentManager {

        class ComponentManager {
        public:
            template <class Component>
            void registerComponent() {
                std::type_index typeIndex = std::type_index(typeid(Component));
                if (_sparseArrays.count(typeIndex) != 0) {
                    std::cerr << "A SparseArray of this type already exists." << std::endl;
                    throw std::runtime_error("SparseArray for this component type already registered.");
                }

                _sparseArrays[typeIndex] = SparseArray<Component>();

                _resetHandlers[typeIndex] = [this, typeIndex](std::size_t entity) {
                    auto& sparseArray = std::any_cast<SparseArray<Component>&>(_sparseArrays.at(typeIndex));
                    if (entity < sparseArray.size()) {
                        sparseArray[entity] = std::nullopt;
                    }
                };
            }

            template <class Component>
            SparseArray<Component>& getComponents() {
                return std::any_cast<SparseArray<Component>&>(_sparseArrays.at(std::type_index(typeid(Component))));
            }

            void entityDestroyed(std::size_t entity, const Signature& signature) {
                for (std::size_t i = 0; i < signature.size(); i++) {
                    if (signature[i]) {
                        std::type_index componentType = ECS::CTypeRegistry::getTypeFromId(i);
                        auto it = _resetHandlers.find(componentType);
                        if (it != _resetHandlers.end()) {
                            it->second(entity);
                        } else {
                            std::cerr << "No reset handler found for component type: " << componentType.name() << std::endl;
                        }
                    }
                }
            }

        private:
            std::unordered_map<std::type_index, std::any> _sparseArrays;
            std::unordered_map<std::type_index, std::function<void(std::size_t)>> _resetHandlers;
        };
    }
}
