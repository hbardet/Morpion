/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Factory
*/

#include "Factory.hh"

Rtype::Command::Factory::Factory()
{
    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(Utils::GameInfoEnum::NewClientConnected)}] = []() {return std::make_unique<GameInfo::Client_connection>();};
    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(Utils::GameInfoEnum::CreateGame)}] = []() {return std::make_unique<GameInfo::Create_game>();};
    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(Utils::GameInfoEnum::GameWonLost)}] = []() {return std::make_unique<GameInfo::Game_result>();};
    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(Utils::GameInfoEnum::GamesAvailable)}] = []() {return std::make_unique<GameInfo::Games_available>();};
    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(Utils::GameInfoEnum::JoinGame)}] = []() {return std::make_unique<GameInfo::Join_game>();};
    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(Utils::GameInfoEnum::ClientDisconnect)}] = []() {return std::make_unique<GameInfo::Client_disconnect>();};
    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(Utils::GameInfoEnum::MissingPackages)}] = []() {return std::make_unique<GameInfo::Missing_packages>();};

    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::PlayerAttack)}] = []() {return std::make_unique<Player::Attack>();};
}

std::unique_ptr<Rtype::Command::ACommand> Rtype::Command::Factory::createCommand(uint8_t cmd_category, uint8_t cmd_index)
{
    auto it = _commandMap.find({cmd_category, cmd_index});

    if (it != _commandMap.end())
        return it->second();
    return nullptr;
}
