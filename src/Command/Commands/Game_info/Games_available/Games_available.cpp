/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Games_available
*/

#include "Games_available.hh"

void Rtype::Command::GameInfo::Games_available::set_client()
{
}

void Rtype::Command::GameInfo::Games_available::set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::Game_info>>> games)
{
    _games = games;
}

Rtype::Command::GameInfo::Games_available::~Games_available()
{
}

void Rtype::Command::GameInfo::Games_available::execute_client_side()
{
	sendToEndpoint(Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::GamesAvailable);
}

void Rtype::Command::GameInfo::Games_available::execute_server_side()
{
    bool sended = false;

    for (auto game: *_games) {
        if (game.second->isGameAvailable()) {
    	    sendToEndpoint(*_clientInfo, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::GamesAvailable, game.second->getRoomId());
            sended |= true;
        }
    }
    if (!sended)
    	sendToEndpoint(*_clientInfo, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::GamesAvailable, -1);
}
