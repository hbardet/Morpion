/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Hit_wall
*/

#include "Hit_wall.hh"

void Rtype::Command::Player::Hit_wall::set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int playerID)
{
    _players = players;
    _playerID = playerID;
}

void Rtype::Command::Player::Hit_wall::set_client(udp::endpoint endpoint)
{
    _endpoint = endpoint;
}

Rtype::Command::Player::Hit_wall::~Hit_wall()
{
}

void Rtype::Command::Player::Hit_wall::execute_client_side()
{
}

void Rtype::Command::Player::Hit_wall::execute_server_side()
{
}
