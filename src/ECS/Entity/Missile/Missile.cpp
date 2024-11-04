/*
** EPITECH PROJECT, 2024
** Missile.cpp
** File description:
** Missile class implementation
*/

#include "Missile.hh"

ECS::Entities::Missile::Missile(std::size_t id):
    _id(id)
{}

ECS::Entities::Missile::operator std::size_t() const {
    return _id;
};

std::size_t ECS::Entities::Missile::getId() const
{
    return _id;
}
