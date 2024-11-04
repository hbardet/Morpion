/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Attack
*/

#include "Attack.hh"

void Rtype::Command::Boss::Attack::set_server(std::map<int, std::shared_ptr<Rtype::client_info>> players, int bossType, int bossAttackType)
{
    _players = players;
    _bossType = bossType;
    _bossAttackType = bossAttackType;
}

void Rtype::Command::Boss::Attack::set_client()
{
}

Rtype::Command::Boss::Attack::~Attack()
{
}

void Rtype::Command::Boss::Attack::execute_client_side()
{
}

void Rtype::Command::Boss::Attack::execute_server_side()
{
}
