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
    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(Utils::GameInfoEnum::LevelComplete)}] = []() {return std::make_unique<GameInfo::Level_complete>();};
    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(Utils::GameInfoEnum::ClientDisconnect)}] = []() {return std::make_unique<GameInfo::Client_disconnect>();};
    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::GameInfo), static_cast<uint8_t>(Utils::GameInfoEnum::MissingPackages)}] = []() {return std::make_unique<GameInfo::Missing_packages>();};

    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::PlayerAttack)}] = []() {return std::make_unique<Player::Attack>();};
    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::PlayerDie)}] = []() {return std::make_unique<Player::Die>();};
    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::PlayerHitAWall)}] = []() {return std::make_unique<Player::Hit_wall>();};
    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::PlayerMove)}] = []() {return std::make_unique<Player::Move>();};
    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::Position)}] = []() {return std::make_unique<Player::Position>();};
    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::PlayerGotPowerUp)}] = []() {return std::make_unique<Player::Power_up>();};
    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::PlayerScore)}] = []() {return std::make_unique<Player::Score>();};
    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::Player), static_cast<uint8_t>(Utils::PlayerEnum::PlayerSpawnOnGame)}] = []() {return std::make_unique<Player::Spawn>();};

    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::Enemy), static_cast<uint8_t>(Utils::EnemyEnum::EnemyAttack)}] = []() {return std::make_unique<Enemy::Attack>();};
    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::Enemy), static_cast<uint8_t>(Utils::EnemyEnum::EnemyDie)}] = []() {return std::make_unique<Enemy::Die>();};
    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::Enemy), static_cast<uint8_t>(Utils::EnemyEnum::EnemySpawn)}] = []() {return std::make_unique<Enemy::Spawn>();};
    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::Enemy), static_cast<uint8_t>(Utils::EnemyEnum::EnemyDestroy)}] = []() {return std::make_unique<Enemy::Destroy>();};
    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::Enemy), static_cast<uint8_t>(Utils::EnemyEnum::EnemyDamage)}] = []() {return std::make_unique<Enemy::Damage>();};

    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::Boss), static_cast<uint8_t>(Utils::BossEnum::BossAttack)}] = []() {return std::make_unique<Boss::Attack>();};
    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::Boss), static_cast<uint8_t>(Utils::BossEnum::BossDie)}] = []() {return std::make_unique<Boss::Die>();};
    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::Boss), static_cast<uint8_t>(Utils::BossEnum::BossSpawn)}] = []() {return std::make_unique<Boss::Spawn>();};

    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::PowerUp), static_cast<uint8_t>(Utils::PowerUpEnum::PowerUpSpawn)}] = []() {return std::make_unique<PowerUp::Spawn>();};

    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::Projectile), static_cast<uint8_t>(Utils::ProjectileEnum::ProjectileFired)}] = []() {return std::make_unique<Projectile::Fired>();};
    _commandMap[{static_cast<uint8_t>(Utils::InfoTypeEnum::Projectile), static_cast<uint8_t>(Utils::ProjectileEnum::ProjectileHit)}] = []() {return std::make_unique<Projectile::Hit>();};
}

std::unique_ptr<Rtype::Command::ACommand> Rtype::Command::Factory::createCommand(uint8_t cmd_category, uint8_t cmd_index)
{
    auto it = _commandMap.find({cmd_category, cmd_index});

    if (it != _commandMap.end())
        return it->second();
    return nullptr;
}
