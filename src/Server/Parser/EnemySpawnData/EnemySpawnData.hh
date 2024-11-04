/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** EnemySpawnData.hh
*/

#pragma once
#include <iostream>
#include <numeric>
#include <utility>
#include "../../../Utils/enemiesTypeEnum.hpp"

#include "../../../Utils/enemiesTypeEnum.hpp"

namespace Rtype {

    class EnemySpawnData {
    public:
        EnemySpawnData();
        ~EnemySpawnData() = default;

        void setType(enemiesTypeEnum_t type);
        void setDifficulty(int difficulty);
        void setPositionX(float position_x);
        void setPositionY(float position_y);
        void setHealth(int health);
        void setModel(std::string model);
        void setSpawnTime(std::pair <int, int> spawnTime);
        int getSpawnTimeInSeconds() const;

        enemiesTypeEnum_t getType() const;
        int getDifficulty() const;
        float getPositionX() const;
        float getPositionY() const;
        int getHealth() const;
        std::string getModel() const;
        std::pair <int, int> getSpawnTime() const;

    private:

        enemiesTypeEnum_t _type;
        int _difficulty;
        float _position_x;
        float _position_y;
        int _health;
        std::string _model;
        int _spawnTimeInSeconds;
        std::pair<int, int> _spawnTime;
    };
}
