/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Spawn
*/

#include "Spawn.hh"

void Rtype::Command::Boss::Spawn::set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int bossType, int bossId, double x, double y, int health)
{
    _players = players;
    _mobType = bossType;
    _mobID = bossId;
    _x = x;
    _y = y;
    _health = health;
}

void Rtype::Command::Boss::Spawn::set_client()
{
}

Rtype::Command::Boss::Spawn::~Spawn()
{
}

void Rtype::Command::Boss::Spawn::execute_client_side()
{
}

void Rtype::Command::Boss::Spawn::execute_server_side()
{
    for (auto player: *_players) {
        _endpoint = udp::endpoint(address::from_string(player.second->getAddr()), player.second->getPort());
        sendToEndpoint(*player.second, _endpoint, Utils::InfoTypeEnum::Boss, Utils::BossEnum::BossSpawn, _mobType, _mobID, _x, _y, _health);
    }
}
