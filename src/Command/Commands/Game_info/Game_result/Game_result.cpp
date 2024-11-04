/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Game_result
*/

#include "Game_result.hh"

void Rtype::Command::GameInfo::Game_result::set_client()
{
}

void Rtype::Command::GameInfo::Game_result::set_server(std::shared_ptr<Rtype::Game_info> game_info)
{
    _gameInfo = game_info;
}

Rtype::Command::GameInfo::Game_result::~Game_result()
{
}

void Rtype::Command::GameInfo::Game_result::execute_client_side()
{
    std::cerr << "This command have no client side" << std::endl;
}

void Rtype::Command::GameInfo::Game_result::execute_server_side()
{
    CONSOLE_INFO("Game status: ", (_gameInfo->gameStatus(0) == 'w' ? "Won" : "Lost")) //! to adapt
	sendToEndpoint(*_clientInfo, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::GameWonLost, _gameInfo->gameStatus(0) == 'w'); //! to adapt
}
