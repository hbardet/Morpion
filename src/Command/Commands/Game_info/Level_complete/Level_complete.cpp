/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Level_complete
*/

#include "Level_complete.hh"

void Rtype::Command::GameInfo::Level_complete::set_client()
{
}

void Rtype::Command::GameInfo::Level_complete::set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::client_info>>> players, int level)
{
    _level = level;
    _players = players;
}

Rtype::Command::GameInfo::Level_complete::~Level_complete()
{
}

void Rtype::Command::GameInfo::Level_complete::execute_client_side()
{
    std::cerr << "This command have no client side" << std::endl;
}

void Rtype::Command::GameInfo::Level_complete::execute_server_side()
{
    for (auto player: *_players) {
        _endpoint = udp::endpoint(address::from_string(player.second->getAddr()), player.second->getPort());
        sendToEndpoint(*player.second, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::LevelComplete, _level);
    }
    // CONSOLE_INFO(_gameInfo->getRoomId(), " went to the next Level !")
    // sendToEndpoint(*_clientInfo, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::LevelComplete, _gameInfo.get());
}
