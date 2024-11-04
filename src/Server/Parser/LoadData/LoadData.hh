/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Loaddata
*/

#pragma once
#include <iostream>
#include <fstream>
#include <json/json.h>
#include <stack>
#include <algorithm>

#include "../EnemySpawnData/EnemySpawnData.hh"
#include "../../../Utils/enemiesTypeEnum.hpp"

namespace Rtype {

    class LoadData {
        public:
            LoadData();
            ~LoadData() = default;

            void LoadDataFromFile(const std::string &path);
            std::stack<Rtype::EnemySpawnData> GetEnemySpawnData() const;
            void clearEnemySpawnData();

        private:
            enemiesTypeEnum_t convertStringToEnumType(const std::string &text);
            std::stack<Rtype::EnemySpawnData> _enemySpawnData;

    };
}
