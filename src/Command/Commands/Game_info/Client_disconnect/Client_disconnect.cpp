/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Client_disconnect
*/

#include "Client_disconnect.hh"

void Rtype::Command::GameInfo::Client_disconnect::set_client()
{
}

void Rtype::Command::GameInfo::Client_disconnect::set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int id)
{
    _id = id;
    _players = players;
}

Rtype::Command::GameInfo::Client_disconnect::~Client_disconnect()
{
}

void Rtype::Command::GameInfo::Client_disconnect::execute_client_side()
{
    sendToEndpoint(Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::ClientDisconnect);
}

void Rtype::Command::GameInfo::Client_disconnect::execute_server_side()
{
    for (auto player: *_players) {
        if (player.first != _id) {
            _endpoint = udp::endpoint(address::from_string(player.second->getAddr()), player.second->getPort());
            sendToEndpoint(*player.second, _endpoint, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::ClientDisconnect, _id);
        }
    }
}
