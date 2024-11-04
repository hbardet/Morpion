/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Position.cpp
*/

#include "Position.hh"

Rtype::Command::Player::Position::~Position()
{
}

void Rtype::Command::Player::Position::set_client()
{
}

void Rtype::Command::Player::Position::set_server(int player_id, double x, double y)
{
    _player_id = player_id;
    _x = x;
    _y = y;
}

void Rtype::Command::Player::Position::execute_client_side()
{
}

void Rtype::Command::Player::Position::execute_server_side()
{
    sendToEndpoint(*_clientInfo, Utils::InfoTypeEnum::Player, Utils::PlayerEnum::Position, _player_id, _x, _y);
}
