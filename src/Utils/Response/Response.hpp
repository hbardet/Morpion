/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Response.hpp
*/

/**
 * @file Response.hpp
 * @brief Declaration of the Utils::Network::Response class for the communication response.
 */

#pragma once
#include <vector>
#include <any>
#include <queue>
#include <cstdint>
#include "../ParametersMap/ParametersMap.hpp"

namespace Utils
{
    namespace Network
    {
        class Response
        {
        private:
            Utils::InfoTypeEnum _infoType;
            uint8_t _infoFunction;
            std::queue<std::any> _params;
            uint32_t _ACK;

        public:
            /**
             * @brief Constructor for the Response class.
             * @param ACK The ACK number.
             * @param infoType The type of information.
             * @param infoFunction The function of the information.
             * @param list_params The list of parameters.
             */
            Response(uint32_t ACK, Utils::InfoTypeEnum infoType, uint8_t infoFunction, std::vector<std::any> list_params);
            Response() {};
            ~Response() = default;

            /**
             * @brief Get the type of information.
             * @return The type of information.
             */
            Utils::InfoTypeEnum GetInfoType() const;
            /**
             * @brief Get the function of the information.
             * @return The function of the information as a uint9_t.
             */
            uint8_t GetInfoFunction() const;
            /**
             * @brief Get the ACK number.
             * @return The ACK number.
             */
            uint32_t getACK() const;

            /**
             * @brief Pops a parameter from the queue.
             * @return The parameter as a std::any.
             */
            std::any RawPopParam();

            /**
             * @brief Pops a parameter from the queue and casts it to the given type.
             * @tparam T The type to cast the parameter to.
             * @return The parameter as the given type.
             */
            template<typename T>

            T PopParam()
            {
                return std::any_cast<T>(RawPopParam());
            }
        };       
    }
}