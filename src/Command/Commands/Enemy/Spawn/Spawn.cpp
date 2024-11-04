/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Spawn
*/

#include "Spawn.hh"

void Rtype::Command::Enemy::Spawn::set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int mobType, int mobID, double x, double y, int health)
{
    _players = players;
    _mobType = mobType;
    _mobID = mobID;
    _x = x;
    _y = y;
    _health = health;
}

void Rtype::Command::Enemy::Spawn::set_client()
{
}

Rtype::Command::Enemy::Spawn::~Spawn()
{
}

void Rtype::Command::Enemy::Spawn::execute_client_side()
{
}

void Rtype::Command::Enemy::Spawn::execute_server_side()
{
    for (auto player: *_players) {
        _endpoint = udp::endpoint(address::from_string(player.second->getAddr()), player.second->getPort());
        sendToEndpoint(*player.second, _endpoint, Utils::InfoTypeEnum::Enemy, Utils::EnemyEnum::EnemySpawn, _mobType, _mobID, _x, _y, _health);
    }
}
