/*
** EPITECH PROJECT, 2024
** R-Type - Components : Position
** File description:
** Position Component
*/

#include "Position.hpp"
#include <ostream>

/**
 * @brief Constructor of Position component.
 *
 * @tparam float x, float y, float z.
 * @return void.
 */
ECS::Components::Position::Position(float x, float y, float z):
    _xOriginalPos(x), _yOriginalPos(y), _zOriginalPos(z), _x(x),  _y(y), _z(z)
{}

/**
 * @brief Getter _X to Position component.
 *
 * @tparam void.
 * @return Float based on private attribute _x which represent position in row of an position entity.
 */
float ECS::Components::Position::getX() const
{
    return _x;
}

/**
 * @brief Getter _Y to Position component.
 *
 * @tparam void.
 * @return Float based on private attribute _y which represent position in column of an position entity.
 */
float ECS::Components::Position::getY() const
{
    return _y;
}

/**
 * @brief Getter _Z to Position component.
 *
 * @tparam void.
 * @return Float based on private attribute _z which represent position in depth of an position entity.
 */

float ECS::Components::Position::getZ() const
{
    return _z;
}

/**
 * @brief Getter _X to Position component.
 *
 * @tparam void.
 * @return Float based on private attribute _xOriginalPos which represent original position in row of an position entity.
 */
float ECS::Components::Position::getOriginalX() const
{
    return _xOriginalPos;
}

/**
 * @brief Getter _Y to Position component.
 *
 * @tparam void.
 * @return Float based on private attribute _yOriginalPos which represent original position in column of an position entity.
 */
float ECS::Components::Position::getOriginalY() const
{
    return _yOriginalPos;
}

/**
 * @brief Getter _Z to Position component.
 *
 * @tparam void.
 * @return Float based on private attribute _zOriginalPos which represent original position in depth of an position entity.
 */
float ECS::Components::Position::getOriginalZ() const
{
    return _zOriginalPos;
}

/**
 * @brief Setter _X to Position component.
 *
 * @tparam float x.
 * @return void.
 */
void ECS::Components::Position::setX(float x)
{
    _x = x;
}

/**
 * @brief Setter _Y to Position component.
 *
 * @tparam float y.
 * @return void.
 */
void ECS::Components::Position::setY(float y)
{
    _y = y;
}

/**
 * @brief Setter _Z to Position component.
 *
 * @tparam float z.
 * @return void.
 */
void ECS::Components::Position::setZ(float z)
{
    _z = z;
}

/**
 * @brief Getter _X and _Y to Position component.
 *
 * @tparam void.
 * @return std::pair<float, float> based on private attribute _x and _y
 * which represent position in row and column of an position entity
 */
std::pair<float, float> ECS::Components::Position::getPosPair() const
{
    return std::make_pair(_x, _y);
}

/**
 * @brief Getter _X, _Y and _Z to Position component.
 *
 * @tparam void.
 * @return std::tuple<float, float, float> based on private attribute _x, _y and _z
 * which represent position in row, column and depth of an position entity
 */
std::tuple<float, float, float> ECS::Components::Position::getPosition() const
{
    return std::make_tuple(_x, _y, _z);
}
