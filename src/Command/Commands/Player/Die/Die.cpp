/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Die
*/

#include "Die.hh"

void Rtype::Command::Player::Die::set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int playerID)
{
    _players = players;
    _playerID = playerID;
}

void Rtype::Command::Player::Die::set_client()
{
}

Rtype::Command::Player::Die::~Die()
{
}

void Rtype::Command::Player::Die::execute_client_side()
{
    std::cerr << "This command have no client side" << std::endl;
}

void Rtype::Command::Player::Die::execute_server_side()
{
    CONSOLE_INFO(_playerID, ": die (RIP)")
    for (auto player: *_players) {
        _endpoint = udp::endpoint(address::from_string(player.second->getAddr()), player.second->getPort());
        sendToEndpoint(*player.second, _endpoint, Utils::InfoTypeEnum::Player, Utils::PlayerEnum::PlayerDie, _playerID);
    }
    _players->at(_playerID)->setAliveStatus(false);
}
