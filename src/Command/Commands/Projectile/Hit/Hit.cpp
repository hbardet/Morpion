/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Hit
*/

#include "Hit.hh"

void Rtype::Command::Projectile::Hit::set_server(std::map<int, std::shared_ptr<Rtype::client_info>> players, int projectileID)
{
    _players = players;
    _projectileID = projectileID;
}

void Rtype::Command::Projectile::Hit::set_client()
{
}

Rtype::Command::Projectile::Hit::~Hit()
{
}

void Rtype::Command::Projectile::Hit::execute_client_side()
{
}

void Rtype::Command::Projectile::Hit::execute_server_side()
{
}
