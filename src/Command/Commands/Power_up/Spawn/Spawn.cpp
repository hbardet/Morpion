/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Spawn
*/

#include "Spawn.hh"

Rtype::Command::PowerUp::Spawn::~Spawn()
{
}

void Rtype::Command::PowerUp::Spawn::set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int podID, double x, double y)
{
	_players = players;
	_podID = podID;
	_x = x;
	_y = y;
}

void Rtype::Command::PowerUp::Spawn::set_client(double x, double y)
{
	_x = x;
	_y = y;
}

void Rtype::Command::PowerUp::Spawn::execute_client_side()
{
    sendToEndpoint(_endpoint, Utils::InfoTypeEnum::PowerUp, Utils::PowerUpEnum::PowerUpSpawn, _x, _y);
}

void Rtype::Command::PowerUp::Spawn::execute_server_side()
{
	for (auto player: *_players) {
        _endpoint = udp::endpoint(address::from_string(player.second->getAddr()), player.second->getPort());
        sendToEndpoint(*player.second, _endpoint, Utils::InfoTypeEnum::PowerUp, Utils::PowerUpEnum::PowerUpSpawn, _podID, _x, _y);
    }
}
