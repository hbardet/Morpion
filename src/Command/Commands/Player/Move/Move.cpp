/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Move
*/

#include "Move.hh"

void Rtype::Command::Player::Move::set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int playerID, double x, double y)
{
    _players = players;
    _playerID = playerID;
    _x = x;
    _y = y;
}

void Rtype::Command::Player::Move::set_client(double x, double y)
{
    _x = x;
    _y = y;
}

Rtype::Command::Player::Move::~Move()
{
}

void Rtype::Command::Player::Move::execute_client_side()
{
    sendToEndpoint(Utils::InfoTypeEnum::Player, Utils::PlayerEnum::PlayerMove, _x, _y);
}

void Rtype::Command::Player::Move::execute_server_side()
{
    udp::endpoint endpoint;

    _players->at(_playerID)->moveX(_x);
    _players->at(_playerID)->moveY(_y);
    for (auto player: *_players) {
        endpoint = udp::endpoint(address::from_string(player.second->getAddr()), player.second->getPort());
        if (player.first != _playerID)
            sendToEndpoint(*player.second, endpoint, Utils::InfoTypeEnum::Player, Utils::PlayerEnum::PlayerMove, _playerID, _x, _y);
    }
    // _game->movePlayer(_playerID, _x, _y); //! Issue : no player created on server side
}
