/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** ParametersMap
*/

#pragma once

#include <iostream>
#include <map>
#include <cstdint>
#include <concepts>
#include <type_traits>
#include <variant>

namespace Utils
{
    // Enums representing different categories of functions.
    enum class InfoTypeEnum: uint8_t {
        GameInfo = 0,
        Player,
        Enemy,
        Boss,
        PowerUp,
        Projectile,
    };

    // Enums for various game-related functions.
    enum class GameInfoEnum: uint8_t {
        NewClientConnected = 0,
        GamesAvailable,
        CreateGame,
        JoinGame,
        GameWonLost,
        SafetyCheck,
        LevelComplete,
        ClientDisconnect,
        MissingPackages
    };

    // Enums for player-related functions.
    enum class PlayerEnum: uint8_t {
        PlayerSpawnOnGame = 0,
        PlayerDie,
        PlayerMove,
        Position,
        PlayerAttack,
        PlayerGotPowerUp,
        PlayerHitAWall,
        PlayerScore
    };

    // Enums for enemy-related functions.
    enum class EnemyEnum: uint8_t {
        EnemySpawn = 0,
        EnemyDie,
        EnemyMove,
        EnemyAttack,
        EnemyDestroy,
        EnemyDamage
    };

    // Enums for boss-related functions.
    enum class BossEnum: uint8_t {
        BossSpawn = 0,
        BossDie,
        BossAttack
    };

    // Enums for power-up-related functions.
    enum class PowerUpEnum: uint8_t {
        PowerUpSpawn = 0,
        PowerUpDisappear,
        PowerUpAttack
    };

    // Enums for projectile-related functions.
    enum class ProjectileEnum: uint8_t {
        ProjectileFired = 0,
        ProjectileHit
    };

    /**
     * @brief A concept that constrains a type T to be one of the specified enumeration types.
     *
     * This concept ensures that the template parameter T can only be one of the following types:
     * - GameInfoEnum
     * - PlayerEnum
     * - EnemyEnum
     * - BossEnum
     * - PowerUpEnum
     * - ProjectileEnum
     *
     * Any type that does not match one of these enumerations will not satisfy this concept.
     */
    template <typename T>
    concept FunctionIndex = std::is_same_v<T, GameInfoEnum> || std::is_same_v<T, PlayerEnum> ||
                        std::is_same_v<T, EnemyEnum> || std::is_same_v<T, BossEnum> ||
                        std::is_same_v<T, PowerUpEnum> || std::is_same_v<T, ProjectileEnum>;


    using PrimitiveType = std::variant<uint32_t, bool, char, int, double>;
    
    // Class managing a mapping of parameters for all functions of the protocol.
    class ParametersMap {
        public:
            /**
             * @brief Initialize the parameters map with all functions and their parameters.
             *
             * Sets up the mapping of function types and indexes to their corresponding
             * parameter types expected by the server and client.
             */
            static void init_map()
            {
                if (!_parametersMap.empty())
                    return;
                _parametersMap = {
                    {{InfoTypeEnum::GameInfo, static_cast<uint8_t>(GameInfoEnum::NewClientConnected)}, {"", "i"}},
                    {{InfoTypeEnum::GameInfo, static_cast<uint8_t>(GameInfoEnum::GamesAvailable)}, {"", "iii"}},
                    {{InfoTypeEnum::GameInfo, static_cast<uint8_t>(GameInfoEnum::CreateGame)}, {"ii", "i"}},
                    {{InfoTypeEnum::GameInfo, static_cast<uint8_t>(GameInfoEnum::JoinGame)}, {"i", "bii"}},
                    {{InfoTypeEnum::GameInfo, static_cast<uint8_t>(GameInfoEnum::GameWonLost)}, {"", "b"}},
                    {{InfoTypeEnum::GameInfo, static_cast<uint8_t>(GameInfoEnum::SafetyCheck)}, {"", ""}},
                    {{InfoTypeEnum::GameInfo, static_cast<uint8_t>(GameInfoEnum::LevelComplete)}, {"", "i"}},
                    {{InfoTypeEnum::GameInfo, static_cast<uint8_t>(GameInfoEnum::ClientDisconnect)}, {"", "i"}},
                    {{InfoTypeEnum::GameInfo, static_cast<uint8_t>(GameInfoEnum::MissingPackages)}, {"llll", ""}},

                    {{InfoTypeEnum::Player, static_cast<uint8_t>(PlayerEnum::PlayerSpawnOnGame)}, {"", "iff"}},
                    {{InfoTypeEnum::Player, static_cast<uint8_t>(PlayerEnum::PlayerDie)}, {"", "i"}},
                    {{InfoTypeEnum::Player, static_cast<uint8_t>(PlayerEnum::PlayerMove)}, {"ff", "iff"}},
                    {{InfoTypeEnum::Player, static_cast<uint8_t>(PlayerEnum::Position)}, {"", "iff"}},
                    {{InfoTypeEnum::Player, static_cast<uint8_t>(PlayerEnum::PlayerAttack)}, {"i", "ii"}},
                    {{InfoTypeEnum::Player, static_cast<uint8_t>(PlayerEnum::PlayerGotPowerUp)}, {"i", "ii"}},
                    {{InfoTypeEnum::Player, static_cast<uint8_t>(PlayerEnum::PlayerHitAWall)}, {"", "i"}},
                    {{InfoTypeEnum::Enemy, static_cast<uint8_t>(EnemyEnum::EnemyDie)}, {"", "i"}},
                    {{InfoTypeEnum::Enemy, static_cast<uint8_t>(EnemyEnum::EnemyAttack)}, {"", "i"}},
                    {{InfoTypeEnum::Enemy, static_cast<uint8_t>(EnemyEnum::EnemyDestroy)}, {"", "i"}},
                    {{InfoTypeEnum::Enemy, static_cast<uint8_t>(EnemyEnum::EnemyDamage)}, {"i", "i"}},

                    {{InfoTypeEnum::Boss, static_cast<uint8_t>(BossEnum::BossSpawn)}, {"", "iiffi"}},
                    {{InfoTypeEnum::Boss, static_cast<uint8_t>(BossEnum::BossDie)}, {"", "i"}},
                    {{InfoTypeEnum::Boss, static_cast<uint8_t>(BossEnum::BossAttack)}, {"", "ii"}},

                    {{InfoTypeEnum::PowerUp, static_cast<uint8_t>(PowerUpEnum::PowerUpSpawn)}, {"ff", "iff"}},
                    {{InfoTypeEnum::PowerUp, static_cast<uint8_t>(PowerUpEnum::PowerUpDisappear)}, {"", ""}},
                    {{InfoTypeEnum::PowerUp, static_cast<uint8_t>(PowerUpEnum::PowerUpAttack)}, {"", ""}},

                    {{InfoTypeEnum::Projectile, static_cast<uint8_t>(ProjectileEnum::ProjectileFired)}, {"", "ii"}},
                    {{InfoTypeEnum::Projectile, static_cast<uint8_t>(ProjectileEnum::ProjectileHit)}, {"", "i"}},
                };
            }

            /**
             * @brief Get the number of parameters expected on the server side.
             * @param function_type The category of the function.
             * @param function_index The index of the function.
             * @return The number of parameters expected by the server.
             */
            static int getNbParameterPerFunctionServer(InfoTypeEnum function_type, uint8_t function_index)
            {
                return _parametersMap[{function_type, function_index}].first.length();
            }

            /**
             * @brief Get the number of parameters expected on the client side.
             * @param function_type The category of the function.
             * @param function_index The index of the function.
             * @return The number of parameters expected by the client.
             */
            static int getNbParameterPerFunctionClient(InfoTypeEnum function_type, uint8_t function_index)
            {
                return _parametersMap[{function_type, function_index}].second.length();
            }

                        /**
             * @brief Get the number of parameters on the server side.
             * @param function_type The category of the function.
             * @param function_index The index of the function.
             * @return The number of parameters expected by the server.
             */
            template <FunctionIndex T>
            static int getNbParameterPerFunctionServer(InfoTypeEnum function_type, T function_index)
            {
                return _parametersMap[{function_type, static_cast<uint8_t>(function_index)}].first.length();
            }

            /**
             * @brief Get the number of parameters on the client side.
             * @param function_type The category of the function.
             * @param function_index The index of the function.
             * @return The number of parameters expected by the client.
             */
            template <FunctionIndex T>
            static int getNbParameterPerFunctionClient(InfoTypeEnum function_type, T function_index)
            {
                return _parametersMap[{function_type, static_cast<uint8_t>(function_index)}].second.length();
            }

            /**
             * @brief Get the parameter types for a server function.
             * @param function_type The category of the function.
             * @param function_index The index of the function.
             * @return The parameter types expected by the server as a string.
             */
            static std::string getParameterTypePerFunctionServer(InfoTypeEnum function_type, uint8_t function_index)
            {
                return _parametersMap[{function_type, function_index}].first;
            }

            /**
             * @brief Get the parameter types for a client function.
             * @param function_type The category of the function.
             * @param function_index The index of the function.
             * @return The parameter types expected by the client as a string.
             */
            static std::string getParameterTypePerFunctionClient(InfoTypeEnum function_type, uint8_t function_index)
            {
                return _parametersMap[{function_type, function_index}].second;
            }

                        /**
             * @brief Get the parameter types for a server function.
             * @param function_type The category of the function.
             * @param function_index The index of the function.
             * @return The parameter types expected by the server as a string.
             */
            template <FunctionIndex T>
            static std::string getParameterTypePerFunctionServer(InfoTypeEnum function_type, T function_index)
            {
                return _parametersMap[{function_type, static_cast<uint8_t>(function_index)}].first;
            }

            /**
             * @brief Get the parameter types for a client function.
             * @param function_type The category of the function.
             * @param function_index The index of the function.
             * @return The parameter types expected by the client as a string.
             */
            template <FunctionIndex T>
            static std::string getParameterTypePerFunctionClient(InfoTypeEnum function_type, T function_index)
            {
                return _parametersMap[{function_type, static_cast<uint8_t>(function_index)}].second;
            }

        private:
            /**
             * @brief Map of function caategories and indexes to parameter types.
             *
             * The map key is a pair consisting of the function category & index,
             * while the value is a pair of strings representing the parameter types
             * expected by the server & client, respectively.
             * Parameter types are denoted by characters (e.g., b: Bool, c: Char, i: Int, f: Float).
             * The first string represents the server's expected parameters, while the second string represents the client's.
             */
            static std::map<std::pair<InfoTypeEnum, uint8_t>, std::pair<std::string, std::string>> _parametersMap;
    };
}
