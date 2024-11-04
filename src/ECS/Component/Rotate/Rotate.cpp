/*
** EPITECH PROJECT, 2024
** R-Type - Components : Rotate
** File description:
** Position Component
*/

#include "Rotate.hh"

ECS::Components::Rotate::Rotate(float roll, float pitch, float yaw):
    _roll(roll), _pitch(pitch), _yaw(yaw)
{}

float ECS::Components::Rotate::getRoll() const
{
    return _roll;
}

float ECS::Components::Rotate::getPitch() const
{
    return _pitch;
}

float ECS::Components::Rotate::getYaw() const
{
    return _yaw;
}

void ECS::Components::Rotate::setRotate(float roll, float pitch, float yaw)
{
    _roll = roll;
    _pitch = pitch;
    _yaw = yaw;
}

void ECS::Components::Rotate::setRoll(float roll)
{
    _roll = roll;
}

void ECS::Components::Rotate::setPitch(float pitch)
{
    _pitch = pitch;
}

void ECS::Components::Rotate::setYaw(float yaw)
{
    _yaw = yaw;
}
