/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Score
*/

#include "Score.hh"

void Rtype::Command::Player::Score::set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int score)
{
    _players = players;
    _score = score;
}

void Rtype::Command::Player::Score::set_client(udp::endpoint endpoint)
{
    _endpoint = endpoint;
}

Rtype::Command::Player::Score::~Score()
{
}

void Rtype::Command::Player::Score::execute_client_side()
{
}

void Rtype::Command::Player::Score::execute_server_side()
{
}
