/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Attack
*/

#include "Attack.hh"

void Rtype::Command::Enemy::Attack::set_server(std::map<int, std::shared_ptr<Rtype::client_info>> players, int mobID)
{
    _players = players;
    _mobID = mobID;
}

void Rtype::Command::Enemy::Attack::set_client()
{
}

Rtype::Command::Enemy::Attack::~Attack()
{
}

void Rtype::Command::Enemy::Attack::execute_client_side()
{
}

void Rtype::Command::Enemy::Attack::execute_server_side()
{
}
