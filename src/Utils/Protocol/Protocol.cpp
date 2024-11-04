/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Protocol.cpp
*/

#include "./Protocol.hpp"
#include "../Response/Response.hpp"
#include "../Utils/Protocol/Protocol.hpp"


namespace Utils
{
    namespace Network
    {
        
        /**
         * @brief Read a fixed-size type from a bytes vector.
         * @param offset The offset to start reading from.
         * @param msg The bytes vector to read from.
         * @param type The type to read.
         * @param size The size of the type to read.
         * @return The value read as a std::any.
         */
        std::any Protocol::newParam(std::size_t &offset, bytes msg, char type_, std::size_t size)
        {
            char char_placeholder = '\0';
            int16_t int_placeholder = 0;
            int32_t long_placeholder = 0;
            double float_placeholder = 0.0;
            bool bool_placeholder = false;
            std::any value;

            // std::cout << "Type: [" << type_ << "] of size: [" << size << "]"<< std::endl;
            switch (type_)
            {
            case 'c':
                std::memcpy(&char_placeholder, msg.data() + offset, size);
                value =  std::any(char_placeholder);
                break;
            case 'i':
                std::memcpy(&int_placeholder, msg.data() + offset, size);
                value =  std::any(static_cast<int32_t>(int_placeholder));
                break;
            case 'f':
                std::memcpy(&int_placeholder, msg.data() + offset, size);
                float_placeholder = static_cast<double>(int_placeholder) / 1000.0;
                value =  std::any(float_placeholder);
                break;
            case 'b':
                std::memcpy(&bool_placeholder, msg.data() + offset, size);
                value =  std::any(bool_placeholder);
                break;
            case 'l':
                std::memcpy(&long_placeholder, msg.data() + offset, size);
                value = std::any(long_placeholder);
                break;
            default:
                throw std::runtime_error("Unknown type");
            }

            offset += size;
            return value;
        }

        std::vector<std::size_t> Protocol::decryptDescriptor(uint16_t descriptor, size_t args_number)
        {
            std::vector<std::size_t> sizes;
            size_t bit_position = 0;
            size_t size = 0;

            for (size_t i = 0; i < args_number; i++) {
                size = 0;

                while ((!((descriptor & (1 << bit_position)) > 0 ) ^ ((~i) & 1))) {
                    size++;
                    bit_position++;
                }
                sizes.push_back(size);
            }

            return sizes;
        }

        /**
         * @brief Parse the message received.
         * @param isClient A boolean to know if the message is read by the client or the server.
         * @param msg The message to parse.
         * @return The response object.
         */
        Response Protocol::ParseMsg(bool isClient, bytes &msg)
        {
            uint32_t ack = 0;
            Utils::InfoTypeEnum info = Utils::InfoTypeEnum::GameInfo;
            uint8_t functionDefiner = 0;
            std::vector<std::any> params;
            std::size_t offset = 0;
            std::string params_types;
            uint16_t args_bytes = 0;
            std::vector<std::size_t> args_sizes;
            

            Utils::ParametersMap::init_map();

            std::memcpy(&ack, msg.data() + offset, ACK_SIZE);
            offset += ACK_SIZE;
            std::memcpy(&info, msg.data() + offset, INFO_TYPE_SIZE);
            offset += INFO_TYPE_SIZE;
            std::memcpy(&functionDefiner, msg.data() + offset, FUNCTION_TYPE_SIZE);
            offset += FUNCTION_TYPE_SIZE;
            std::memcpy(&args_bytes, msg.data() + offset, DESCRIPTOR_SIZE);
            offset += DESCRIPTOR_SIZE;

            if (isClient)
                params_types = Utils::ParametersMap::getParameterTypePerFunctionClient(info, functionDefiner);
            else
                params_types = Utils::ParametersMap::getParameterTypePerFunctionServer(info, functionDefiner);
            args_sizes = decryptDescriptor(args_bytes, params_types.size());

            for (size_t i = 0; i < params_types.size(); i++)
                params.push_back(newParam(offset, msg, params_types[i], args_sizes[i]));

            return Response(ack, info, functionDefiner, params);
        }
    } // namespace Network
    
} // namespace Utils
