/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Damage
*/

#include "Damage.hh"

void Rtype::Command::Enemy::Damage::set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int mobID)
{
    _players = players;
    _mobID = mobID;
}

void Rtype::Command::Enemy::Damage::set_client(int mobID)
{
    _mobID = mobID;
}

Rtype::Command::Enemy::Damage::~Damage()
{
}

void Rtype::Command::Enemy::Damage::execute_client_side()
{
//    std::cout << "i m about to take damages: " << _mobID << std::endl;
    sendToEndpoint(Utils::InfoTypeEnum::Enemy, Utils::EnemyEnum::EnemyDamage, _mobID);
}

void Rtype::Command::Enemy::Damage::execute_server_side()
{
    for (auto player: *_players) {
        _endpoint = udp::endpoint(address::from_string(player.second->getAddr()), player.second->getPort());
        sendToEndpoint(*player.second, _endpoint, Utils::InfoTypeEnum::Enemy, Utils::EnemyEnum::EnemyDamage, _mobID);
    }
}
