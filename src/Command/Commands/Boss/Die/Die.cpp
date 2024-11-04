/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Die
*/

#include "Die.hh"

void Rtype::Command::Boss::Die::set_server(std::map<int, std::shared_ptr<Rtype::client_info>> players, int bossType)
{
    _players = players;
    _bossType = bossType;
}

void Rtype::Command::Boss::Die::set_client()
{
}

Rtype::Command::Boss::Die::~Die()
{
}

void Rtype::Command::Boss::Die::execute_client_side()
{
}

void Rtype::Command::Boss::Die::execute_server_side()
{
}
