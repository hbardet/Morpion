/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** EnemySpawnData.cpp
*/

#include "EnemySpawnData.hh"

Rtype::EnemySpawnData::EnemySpawnData()
{}

void Rtype::EnemySpawnData::setType(enemiesTypeEnum_t enemyType)
{
    _type = enemyType;
}

void Rtype::EnemySpawnData::setDifficulty(int difficulty)
{
    _difficulty = difficulty;
}


void Rtype::EnemySpawnData::setPositionX(float x)
{
    _position_x = x;
}

void Rtype::EnemySpawnData::setPositionY(float y)
{
    _position_y = y;
}

void Rtype::EnemySpawnData::setHealth(int health)
{
    _health = health;
}

void Rtype::EnemySpawnData::setModel(std::string model)
{
    _model = model;
}

void Rtype::EnemySpawnData::setSpawnTime(std::pair <int, int> spawnTime)
{
    _spawnTime = spawnTime;
    _spawnTimeInSeconds = spawnTime.first * 60 + spawnTime.second;
}

enemiesTypeEnum_t Rtype::EnemySpawnData::getType() const
{
    return _type;
}

int Rtype::EnemySpawnData::getSpawnTimeInSeconds() const
{
    return _spawnTimeInSeconds;
}

int Rtype::EnemySpawnData::getHealth() const
{
    return _health;
}

float Rtype::EnemySpawnData::getPositionX() const
{
    return _position_x;
}

float Rtype::EnemySpawnData::getPositionY() const
{
    return _position_y;
}

int Rtype::EnemySpawnData::getDifficulty() const
{
    return _difficulty;
}

std::string Rtype::EnemySpawnData::getModel() const
{
    return _model;
}

std::pair <int, int> Rtype::EnemySpawnData::getSpawnTime() const
{
    return _spawnTime;
}
