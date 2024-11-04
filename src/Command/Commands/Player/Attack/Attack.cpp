/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Attack
*/

#include "Attack.hh"

void Rtype::Command::Player::Attack::set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int projectileID)
{
    _players = players;
    _projectileID = projectileID;
}

void Rtype::Command::Player::Attack::set_client(udp::endpoint endpoint, int projectileID)
{
    _endpoint = endpoint;
    _projectileID = projectileID;
}

Rtype::Command::Player::Attack::~Attack()
{
}

void Rtype::Command::Player::Attack::execute_client_side()
{
}

void Rtype::Command::Player::Attack::execute_server_side()
{
}
