/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Destroy
*/

#include "Destroy.hh"

void Rtype::Command::Enemy::Destroy::set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int mobID, int roomId)
{
    _players = players;
    _mobID = mobID;
    _roomID = roomId;
}

void Rtype::Command::Enemy::Destroy::set_client()
{
}

Rtype::Command::Enemy::Destroy::~Destroy()
{
}

void Rtype::Command::Enemy::Destroy::execute_client_side()
{
}

void Rtype::Command::Enemy::Destroy::execute_server_side()
{
    for (auto player: *_players) {
        if (player.second->getRoom() == _roomID) {
            _endpoint = udp::endpoint(address::from_string(player.second->getAddr()), player.second->getPort());
            sendToEndpoint(*player.second, _endpoint, Utils::InfoTypeEnum::Enemy, Utils::EnemyEnum::EnemyDestroy, _mobID);
        }
    }
}
