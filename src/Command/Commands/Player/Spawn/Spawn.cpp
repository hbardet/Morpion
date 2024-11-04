/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Spawn
*/

#include "Spawn.hh"

void Rtype::Command::Player::Spawn::set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int playerID, int roomId, double x, double y)
{
    _players = players;
    _playerID = playerID;
    _roomId = roomId;
    _x = x;
    _y = y;
}

void Rtype::Command::Player::Spawn::set_client()
{
}

Rtype::Command::Player::Spawn::~Spawn()
{
}

void Rtype::Command::Player::Spawn::execute_client_side()
{
    std::cerr << "This command have no client side" << std::endl;
}

void Rtype::Command::Player::Spawn::execute_server_side()
{
    _players->at(_playerID)->setX(_x);
    _players->at(_playerID)->setY(_y);
    for (auto player: *_players) {
        _endpoint = udp::endpoint(address::from_string(player.second->getAddr()), player.second->getPort());
        if (player.first != _playerID)
            sendToEndpoint(*player.second, _endpoint, Utils::InfoTypeEnum::Player, Utils::PlayerEnum::PlayerSpawnOnGame, _playerID, _x, _y);
        else
            for (auto tmp: *_players)
                if (tmp.first != _playerID)
                    sendToEndpoint(*tmp.second, _endpoint, Utils::InfoTypeEnum::Player, Utils::PlayerEnum::PlayerSpawnOnGame, tmp.first, _players->at(tmp.first)->getX(), _players->at(tmp.first)->getY());
    }
    _game->createOtherPlayer(_playerID, _x, _y); //! Issue
}
