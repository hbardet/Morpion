/*
** EPITECH PROJECT, 2024
** Button.cpp
** File description:
** Button class implementation
*/

#include "Button.hh"

ECS::Entities::Button::Button(std::size_t id):
    _id(id)
{}

ECS::Entities::Button::operator std::size_t() const
{
    return _id;
}

std::size_t ECS::Entities::Button::getId() const
{
    return _id;
}
