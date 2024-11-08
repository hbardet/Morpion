/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SetPawn
*/

#include "SetPawn.hh"

void Rtype::Command::Player::SetPawn::set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int coo, int id)
{
    _players = players;
    _coo = coo;
    _id = id;
}

void Rtype::Command::Player::SetPawn::set_client(int coo)
{
    _coo = coo;
}

Rtype::Command::Player::SetPawn::~SetPawn()
{
}

void Rtype::Command::Player::SetPawn::execute_client_side()
{
    sendToEndpoint(Utils::InfoTypeEnum::Player, Utils::PlayerEnum::SetPawn, _coo);
}

void Rtype::Command::Player::SetPawn::execute_server_side()
{
    for (auto player: *_players) {
        _endpoint = udp::endpoint(address::from_string(player.second->getAddr()), player.second->getPort());
        sendToEndpoint(*player.second, _endpoint, Utils::InfoTypeEnum::Player, Utils::PlayerEnum::SetPawn, _coo, _id);
    }
}
