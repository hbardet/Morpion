/*
** EPITECH PROJECT, 2024
** Enemy.cpp
** File description:
** Enemy class
*/
#include "Enemy.hh"

ECS::Entities::Enemy::Enemy(std::size_t id):
    _id(id)
{}

ECS::Entities::Enemy::operator std::size_t() const
{
    return _id;
}

std::size_t ECS::Entities::Enemy::getId() const
{
    return _id;
}
