/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Response.cpp
*/

#include "../Protocol/Protocol.hpp"
#include "./Response.hpp"

namespace Utils
{
    namespace Network
    {
        Response::Response(uint32_t ACK, Utils::InfoTypeEnum infoType, uint8_t infoFunction, std::vector<std::any> list_params) :_ACK(ACK) , _infoType(infoType), _infoFunction(infoFunction)
        {
            for (std::any &param : list_params)
                _params.push(param);
        }

        Utils::InfoTypeEnum Response::GetInfoType() const
        {
            return _infoType;
        }

        uint8_t Response::GetInfoFunction() const
        {
            return _infoFunction;
        }

        uint32_t Response::getACK() const
        {
            return _ACK;
        }

        std::any Response::RawPopParam()
        {
            std::any param = _params.front();

            _params.pop();
            return param;
        }
    }    
}