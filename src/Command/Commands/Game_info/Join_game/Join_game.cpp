/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Join_game
*/

#include "Join_game.hh"

void Rtype::Command::GameInfo::Join_game::set_client(int gameRoom)
{
    _gameRoom = gameRoom;
}

void Rtype::Command::GameInfo::Join_game::set_server()
{
    _exist = false;
}

void Rtype::Command::GameInfo::Join_game::set_server(std::shared_ptr<Rtype::Game_info> game, std::shared_ptr<Rtype::client_info> client_info)
{
    _gameInfo = game;
    _clientInfo = client_info;
    _exist = true;
}

Rtype::Command::GameInfo::Join_game::~Join_game()
{
}

void Rtype::Command::GameInfo::Join_game::execute_client_side()
{
	sendToEndpoint(Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::JoinGame, _gameRoom);
}

void Rtype::Command::GameInfo::Join_game::execute_server_side()
{
    if (!_exist) {
        CONSOLE_INFO("", "No room matching this ID")
	    sendToEndpoint(*_clientInfo, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::JoinGame, false);
    } else if (!_gameInfo->isGameAvailable()) {
        CONSOLE_INFO(_gameInfo->getRoomId(), " is not available : max player number reach")
	    sendToEndpoint(*_clientInfo, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::JoinGame, false);
    } else {
        _gameInfo->connectPlayer(_clientInfo);
	    sendToEndpoint(*_clientInfo, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::JoinGame, true);
    }
}
