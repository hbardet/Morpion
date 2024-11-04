/*
** EPITECH PROJECT, 2024
** R-Type - Components : Scale
** File description:
** Scale Component
*/

#include "Scale.hh"

ECS::Components::Scale::Scale(float scale):
    _scale(scale)
{}

float ECS::Components::Scale::getScale() const
{
    return _scale;
}

void ECS::Components::Scale::setScale(float scale)
{
    _scale = scale;
}
