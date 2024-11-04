/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Create_game
*/

#include "Create_game.hh"

void Rtype::Command::GameInfo::Create_game::set_client()
{
}

void Rtype::Command::GameInfo::Create_game::set_server(std::shared_ptr<std::map<int, std::shared_ptr<Rtype::Game_info>>> games)
{
    _games = games;
}

Rtype::Command::GameInfo::Create_game::~Create_game()
{
}

int Rtype::Command::GameInfo::Create_game::getRoomIdAvailable(bool set_seed) const
{
    int room_id = 0;

    if (_games->size() == 9000)
        return -1;
    if (set_seed)
        srand(std::time(nullptr));
    room_id = (rand() % 9000) + 1000;
    for (auto game: *_games)
        if (game.second->getRoomId() == room_id)
            return getRoomIdAvailable(false);
    return room_id;
}

void Rtype::Command::GameInfo::Create_game::execute_client_side()
{
	sendToEndpoint(Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::CreateGame);
}

void Rtype::Command::GameInfo::Create_game::execute_server_side()
{
    int room_id = getRoomIdAvailable(true);

    if (room_id == -1) {
        CONSOLE_INFO("Impossible to create a game, no more room available.", "")
        return;
    }
    _games->insert({room_id, std::make_shared<Game_info>(room_id)});
    CONSOLE_INFO("Create a new game: ", room_id)
	sendToEndpoint(*_clientInfo, Utils::InfoTypeEnum::GameInfo, Utils::GameInfoEnum::CreateGame, room_id);
}
