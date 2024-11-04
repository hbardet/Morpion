/*
** EPITECH PROJECT, 2024
** R-Type - Components : Hitbox
** File description:
** Hitbox Component
*/

#include "Hitbox.hh"

/**
 * @brief Constructor of Hitbox component.
 *
 * @tparam float width that represents width of an hitbox entity.
 * @tparam float height that represents height of an hitbox entity.
 * @return void.
 */
ECS::Components::Hitbox::Hitbox(float width, float height):
    _width(width), _height(height)
{}

/**
 * @brief Getter _width to Hitbox component.
 *
 * @tparam void.
 * @return Float based on private attribute _width which represent with of an hitbox entity.
 */
float ECS::Components::Hitbox::getWidth() const
{
    return _width;
}

/**
 * @brief Getter _height to Hitbox component.
 *
 * @tparam void.
 * @return Float based on private attribute _height which represent height of an hitbox entity.
 */
float ECS::Components::Hitbox::getHeight() const
{
    return _height;
}


/**
 * @brief Setter _width to Hitbox component.
 *
 * @tparam Float width that represents width of an hitbox entity.
 * @return void.
 */
void ECS::Components::Hitbox::setWidth(float width)
{
    _width = width;
}

/**
 * @brief Setter _height to Hitbox component.
 *
 * @tparam Float height that represents height of an hitbox entity.
 * @return void.
 */
void ECS::Components::Hitbox::setHeight(float height)
{
    _height = height;
}
