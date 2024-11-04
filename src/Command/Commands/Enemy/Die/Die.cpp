/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Die
*/

#include "Die.hh"

void Rtype::Command::Enemy::Die::set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int mobID)
{
    _players = players;
    _mobID = mobID;
}

void Rtype::Command::Enemy::Die::set_client()
{
}

Rtype::Command::Enemy::Die::~Die()
{
}

void Rtype::Command::Enemy::Die::execute_client_side()
{
}

void Rtype::Command::Enemy::Die::execute_server_side()
{
    for (auto player: *_players) {
        _endpoint = udp::endpoint(address::from_string(player.second->getAddr()), player.second->getPort());
        sendToEndpoint(*player.second, _endpoint, Utils::InfoTypeEnum::Enemy, Utils::EnemyEnum::EnemyDamage, _mobID);
    }
}
