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
    };

    // Enums for various game-related functions.
    enum class GameInfoEnum: uint8_t {
        NewClientConnected = 0,
        GamesAvailable,
        CreateGame,
        JoinGame,
        GameWonLost,
        ClientDisconnect,
        MissingPackages
    };

    // Enums for player-related functions.
    enum class PlayerEnum: uint8_t {
        SetPawn = 0
    };

    /**
     * @brief A concept that constrains a type T to be one of the specified enumeration types.
     *
     * This concept ensures that the template parameter T can only be one of the following types:
     * - GameInfoEnum
     * - PlayerEnum
     *
     * Any type that does not match one of these enumerations will not satisfy this concept.
     */
    template <typename T>
    concept FunctionIndex = std::is_same_v<T, GameInfoEnum> || std::is_same_v<T, PlayerEnum>;


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
                    {{InfoTypeEnum::GameInfo, static_cast<uint8_t>(GameInfoEnum::GamesAvailable)}, {"", "i"}},
                    {{InfoTypeEnum::GameInfo, static_cast<uint8_t>(GameInfoEnum::CreateGame)}, {"", "i"}},
                    {{InfoTypeEnum::GameInfo, static_cast<uint8_t>(GameInfoEnum::JoinGame)}, {"i", "bii"}},
                    {{InfoTypeEnum::GameInfo, static_cast<uint8_t>(GameInfoEnum::GameWonLost)}, {"", "b"}},
                    {{InfoTypeEnum::GameInfo, static_cast<uint8_t>(GameInfoEnum::ClientDisconnect)}, {"", "i"}},
                    {{InfoTypeEnum::GameInfo, static_cast<uint8_t>(GameInfoEnum::MissingPackages)}, {"llll", ""}},

                    {{InfoTypeEnum::Player, static_cast<uint8_t>(PlayerEnum::SetPawn)}, {"i", "ii"}},
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
