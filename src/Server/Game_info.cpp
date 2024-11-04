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
	_id(-1), _level(0), _difficulty(1), _nbMaxPlayer(6), _nbProjectiles(100), _tick(0), _timeLastLevelEnded(0), _players(), _nextEnemyIndex(0), _toSetNetwork(true)
{
}

Rtype::Game_info::Game_info(int id, int difficulty, int nbMaxPlayer):
	_id(id), _level(0), _difficulty(difficulty), _nbMaxPlayer(nbMaxPlayer), _nbProjectiles(100), _tick(0), _timeLastLevelEnded(0), _players(), _nextEnemyIndex(0), _toSetNetwork(true)
{
    _loadData.LoadDataFromFile("stage1.json");
    _enemySpawnData = _loadData.GetEnemySpawnData();
	_tickThread = std::thread([this]() { computeTick(); });
}

Rtype::Game_info::~Game_info()
{
	if (_tickThread.joinable()) {
        _tickThread.join();
    }
	if (_gameThread.joinable()) {
        _gameThread.join();
    }
}

Rtype::Game_info::Game_info(Game_info &&other) noexcept:
	_id(other._id), _level(other._level), _difficulty(other._difficulty), _nbMaxPlayer(other._nbMaxPlayer), _tick(other._tick),
    _timeLastLevelEnded(other._timeLastLevelEnded), _tickThread(std::move(other._tickThread)), _players(std::move(other._players)), _toSetNetwork(other._toSetNetwork)
{
    other._id = -1;
    other._level = 0;
    other._nbMaxPlayer = 6;
    other._nbProjectiles = 100;
    other._tick = 0;
    other._timeLastLevelEnded = 0;
    other._nextEnemyIndex = 0;
    other._difficulty = 0;
}

Rtype::Game_info &Rtype::Game_info::operator=(Game_info &&other) noexcept
{
    if (this != &other) {
        if (_tickThread.joinable()) {
            _tickThread.join();
        }

        _id = other._id;
        _level = other._level;
        _nbMaxPlayer = other._nbMaxPlayer;
        _tick = other._tick;
        _tickThread = std::move(other._tickThread);
        _players = std::move(other._players);
		_toSetNetwork = other._toSetNetwork;
        _nbProjectiles = other._nbProjectiles;
        _nextEnemyIndex = other._nextEnemyIndex;
        _difficulty = other._difficulty;
        _timeLastLevelEnded = other._timeLastLevelEnded;

        other._id = -1;
        other._level = 0;
        other._nbMaxPlayer = 6;
        other._tick = 0;
    }
    return *this;
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

void Rtype::Game_info::computeGame(int currentGameTimeInSeconds)
{
}

void Rtype::Game_info::computePlayer()
{
}

void Rtype::Game_info::computeTick(void)
{
    int currentGameTimeInSeconds = 0;

    while (true) {
        {
            std::lock_guard<std::mutex> lock(_playersMutex);
            if (!_players || _players->empty()) 
                continue;
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
        _tick += 1;
        currentGameTimeInSeconds = _tick / 20;
        computeGame(currentGameTimeInSeconds);
        if (_tick % 20 == 0)
            computePlayer();
        if (_tick == MAX_UINT32 - 1) {
            _tick = 0;
            _timeLastLevelEnded = 0;
        }
    }
}

bool Rtype::Game_info::isGameAvailable(void)
{
    std::lock_guard<std::mutex> lock(_playersMutex);
	return !(_players->max_size() == _nbMaxPlayer);
}

bool Rtype::Game_info::gameStatus(void)
{
	return true;
}

void Rtype::Game_info::goNextLevel(void)
{
    const std::string nextLevel = "stage" + std::to_string(_level + 1) + ".json";

    _loadData.clearEnemySpawnData();
    _level += 1;
    _loadData.LoadDataFromFile(nextLevel);
    _enemySpawnData = _loadData.GetEnemySpawnData();
    if (_enemySpawnData.empty()) {
        _loadData.clearEnemySpawnData();
        _level = 1;
        _loadData.LoadDataFromFile("stage1.json");
        _enemySpawnData = _loadData.GetEnemySpawnData();
    }
}

int Rtype::Game_info::getLevel(void)
{
	return _level;
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
	player->setX(-10.);
	player->setY(0.);
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
		player->setX(42.);
		player->setY(42.);
		_players->erase(id);  
    }
}

int Rtype::Game_info::getNbMaxPlayers()
{
    return _nbMaxPlayer;
}

int Rtype::Game_info::getNbProjectiles()
{
    return _nbProjectiles;
}

void Rtype::Game_info::accNbProjectiles()
{
    _nbProjectiles += 1;
}

