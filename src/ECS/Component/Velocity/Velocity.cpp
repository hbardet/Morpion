/*
** EPITECH PROJECT, 2024
** R-Type - Components : Velocity
** File description:
** Velocity Component
*/

#include "Velocity.hh"

/**
 * @brief Constructor of Velocity component.
 *
 * @tparam float x, float y.
 * @return void.
 */
ECS::Components::Velocity::Velocity(float x, float y):
    _x(x), _y(y)
{}

/**
 * @brief Constructor of Velocity component.
 *
 * @tparam std::pair<float, float> vel.
 * @return void.
 */
ECS::Components::Velocity::Velocity(std::pair<float, float> vel):
    _x(vel.first), _y(vel.second)
{}

/**
 * @brief Getter _x of Velocity component.
 *
 * @tparam void.
 * @return float _x.
 */
float ECS::Components::Velocity::getX() const
{
    return _x;
}

/**
 * @brief Getter _y of Velocity component.
 *
 * @tparam void.
 * @return float _y.
 */
float ECS::Components::Velocity::getY() const
{
    return _y;
}

/**
 * @brief Setter _x of Velocity component.
 *
 * @tparam float x.
 * @return void.
 */
void ECS::Components::Velocity::setX(float x)
{
    _x = x;
}

/**
 * @brief Setter _y of Velocity component.
 *
 * @tparam float y.
 * @return void.
 */
void ECS::Components::Velocity::setY(float y)
{
    _y = y;
}

/**
 * @brief Getter _x and _y of Velocity component.
 *
 * @tparam void.
 * @return std::pair<float, float> _x and _y.
*/
std::pair<float, float> ECS::Components::Velocity::getVelPair() const
{
    return std::make_pair(_x, _y);
}

/**
 * @brief Getter _x and _y of Velocity component.
 *
 * @tparam void.
 * @return std::pair<float, float> _x and _y.
*/
void ECS::Components::Velocity::setVelPair(std::pair<float, float> vel)
{
    _x = vel.first;
    _y = vel.second;
}
