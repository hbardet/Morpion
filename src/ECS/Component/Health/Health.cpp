/*
** EPITECH PROJECT, 2024
** R-Type - Components : Health
** File description:
** Health Component
*/

#include "Health.hh"

/**
 * @brief Constructor to health component.
 *
 * Constructor for the life component, which will represent the 
 * life of the entities in the video game, 
 * with an Integer parameter assigned to the private _health attribute.
 *
 * @tparam Integer to create health component.
 * @return void.
 */
ECS::Components::Health::Health(int health, int invincibility):
    _health(health), _invincibility(invincibility)
{}

/**
 * @brief Getter _health to health component.
 *
 * @tparam void.
 * @return Integer based on private attribute _health which represent life of an entity.
 */
int ECS::Components::Health::getHealth() const
{
    return _health;
}

/**
 * @brief Setter _health to health component.
 *
 * @tparam Integer health which represent life of an entity.
 * @return void.
 */
void ECS::Components::Health::setHealth(int health)
{
    _health = health;
}

void ECS::Components::Health::modifyHealthBy(int delta)
{
    _health += delta;
}

int ECS::Components::Health::getInvincibility() const
{
    return _invincibility;
}

void ECS::Components::Health::setInvincibility(int invincibility)
{
    _invincibility = invincibility;
}

void ECS::Components::Health::modifyInvincibilityBy(int delta)
{
    _invincibility += delta;
}

