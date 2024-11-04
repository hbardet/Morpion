/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Power_up
*/

#include "Power_up.hh"

void Rtype::Command::Player::Power_up::set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int playerID, int powerUpID)
{
    _players = players;
    _playerID = playerID;
    _powerUpID = powerUpID;
}

void Rtype::Command::Player::Power_up::set_client(int podId)
{
    _powerUpID = podId;
}

Rtype::Command::Player::Power_up::~Power_up()
{
}

void Rtype::Command::Player::Power_up::execute_client_side()
{
    sendToEndpoint(Utils::InfoTypeEnum::Player, Utils::PlayerEnum::PlayerGotPowerUp, _powerUpID);
}

void Rtype::Command::Player::Power_up::execute_server_side()
{
    for (auto player: *_players) {
        _endpoint = udp::endpoint(address::from_string(player.second->getAddr()), player.second->getPort());
        sendToEndpoint(*player.second, _endpoint, Utils::InfoTypeEnum::Player, Utils::PlayerEnum::PlayerGotPowerUp, _playerID, _powerUpID);
    }
}
