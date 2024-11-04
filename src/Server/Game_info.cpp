/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game_info
*/

#include "../Utils/Network/Network.hpp"
#include "../Client/Game/Game.hh"
#include "Game_info.hh"
#include <iostream>
#include <memory>
#include <vector>

Rtype::Game_info::Game_info():
	_id(-1), _players(), _toSetNetwork(true)
{
}

Rtype::Game_info::Game_info(int id):
	_id(id), _players(), _toSetNetwork(true)
{
    for (int i = 0; i < 9; i++)
        _map[i] = 0;
}

Rtype::Game_info::~Game_info()
{
	if (_gameThread.joinable()) {
        _gameThread.join();
    }
}

// }
void Rtype::Game_info::placePawn(int coo, int player)
{
    if (coo >= 9 || _map[coo] != 0)
        return;
    _map[coo] = player;
}

bool Rtype::Game_info::getToSetNetwork()
{
	return _toSetNetwork;
}

void Rtype::Game_info::setNetwork(std::shared_ptr<Rtype::Network> network)
{
	_toSetNetwork = false;
	_network = network;
    _game = std::make_shared<Rtype::Game>(_network, false);
}

std::shared_ptr<Rtype::Game> Rtype::Game_info::getGame()
{
	return _game;
}

void Rtype::Game_info::runGame()
{
	_gameThread = std::thread([this]() { _game->runServer(); });
}

char Rtype::Game_info::gameStatus(int id)
{
    if (_map[0] == _map[1] && _map[2] == _map[1])
        return (_map[0] == id ? 'w' : 'l');
    if (_map[3] == _map[4] && _map[5] == _map[4])
        return (_map[3] == id ? 'w' : 'l');
    if (_map[6] == _map[7] && _map[8] == _map[7])
        return (_map[6] == id ? 'w' : 'l');

    if (_map[0] == _map[3] && _map[6] == _map[3])
        return (_map[0] == id ? 'w' : 'l');
    if (_map[1] == _map[4] && _map[7] == _map[4])
        return (_map[1] == id ? 'w' : 'l');
    if (_map[2] == _map[5] && _map[8] == _map[5])
        return (_map[2] == id ? 'w' : 'l');

    if (_map[0] == _map[4] && _map[8] == _map[0])
        return (_map[0] == id ? 'w' : 'l');
    if (_map[2] == _map[4] && _map[6] == _map[2])
        return (_map[2] == id ? 'w' : 'l');

    return 't';
}

bool Rtype::Game_info::isGameAvailable(void)
{
    std::lock_guard<std::mutex> lock(_playersMutex);
	return !(_players->max_size() == 2);
}

int Rtype::Game_info::getRoomId(void)
{
	return _id;
}

void Rtype::Game_info::connectPlayer(std::shared_ptr<Rtype::client_info> player)
{
	if (!isGameAvailable())
		return;
    std::lock_guard<std::mutex> lock(_playersMutex);
	if (!_players)
		_players = std::make_shared<std::map<int, std::shared_ptr<Rtype::client_info>>>();
	_players->insert({player->getId(), player});
	player->setRoom(_id);
}

std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> Rtype::Game_info::getPlayers(void) {
    return _players;
}

void Rtype::Game_info::disconnectPlayer(int id)
{
    std::lock_guard<std::mutex> lock(_playersMutex);
    if (_players->find(id) != _players->end()) {
        auto player = _players->find(id)->second;
      	player->setRoom(-1);
		_players->erase(id);  
    }
}

int Rtype::Game_info::getNbMaxPlayers()
{
    return 2;
}
