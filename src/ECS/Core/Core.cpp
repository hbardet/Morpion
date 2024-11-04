/*
** EPITECH PROJECT, 2024
** R-Type - Core : Core
** File description:
** Core class is the main class of the ECS.
** It will coordinate the different managers.
*/

#include "Core.hpp"

/**
 * @brief Constructor for the Core class.
 *
 * Initializes the entity manager, system manager, and component manager.
 *
 * @tparam void
 * @return void
 */
ECS::Core::Core::Core()
{
    _entityManager = std::make_shared<EntityManager::EntityManager>();
    _systemManager = std::make_shared<SystemManager::SystemManager>();
    _componentManager = std::make_shared<ComponentManager::ComponentManager>();
}

/**
 * @brief Creates a new entity.
 *
 * @tparam void
 * @return std::size_t The ID of the new created entity.
 */
std::size_t ECS::Core::Core::createEntity()
{
    std::size_t temp = _entityManager->createEntity();

    return temp;
}

/**
 * @brief Destroys an entity.
 *
 * This function destroys the entity with the given ID and informs the system manager about the entity destruction.
 *
 * @param entity The ID of the entity to be destroyed.
 * @tparam std::size_t entity
 * @return void
 */
void ECS::Core::Core::destroyEntity(std::size_t entity)
{
    Signature signature = _entityManager->getSignature(entity);
    _entityManager->destroyEntity(entity);
    _systemManager->entityDestroyed(entity);
    _componentManager->entityDestroyed(entity, signature);

}

/**
 * @brief Gets the signature of an entity.
 *
 * Retrieves the signature that represents the components associated with the entity.
 *
 * @param entity The ID of the entity whose signature is being requested.
 * @tparam std::size_t entity
 * @return Signature The signature of the entity.
 */
Signature ECS::Core::Core::getSignature(std::size_t entity) const
{
    return _entityManager->getSignature(entity);
}
