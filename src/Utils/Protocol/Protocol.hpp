/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** Protocole.hh
*/

/**
 * @file Protocole.hpp
 * @brief Declaration of the Utils::Network::Protocole class for the communication protocol.
 */

#pragma once
#include <cstdint>
#include <iostream>
#include <vector>
#include <cstring>
#include <any>
#include <cstdarg>
#include <variant>
#include "../Response/Response.hpp"

namespace Utils
{
    namespace Network
    {
        /**
         * @typedef bytes
         * @brief Alias for a vector of uint8_t.
         */
        using bytes = std::vector<uint8_t>;

        class Protocol
        {
        private:
            static const std::size_t ACK_SIZE = sizeof(uint32_t);
            static const std::size_t PARAMS_SIZE_SIZE = sizeof(uint8_t);
            static const std::size_t INFO_TYPE_SIZE = sizeof(uint8_t);
            static const std::size_t FUNCTION_TYPE_SIZE = sizeof(uint8_t);
            static const std::size_t DESCRIPTOR_SIZE = sizeof(uint16_t);

            template <typename T>
            static void updateDescriptor(uint16_t &descriptor, std::size_t &bit_position, T value)
            {
                std::size_t num_bits = 1;

                if constexpr (std::is_same<T, uint32_t>::value) {
                    if (value & 0xFF000000)
                        num_bits = 4;
                    else if (value & 0x00FF0000)
                        num_bits = 3;
                    else if (value & 0x0000FF00)
                        num_bits = 2;
                    else
                        num_bits = 1;
                }
                else if constexpr (std::is_same<T, int>::value) {
                    if ((value & 0xFF00) != 0)
                        num_bits = 2;
                }
                else if constexpr (std::is_same<T, double>::value)
                    num_bits = 2;

                for (size_t i = 0; i < num_bits; i++)
                    if (bit_position == 0 || ((1 << (bit_position - 1)) & descriptor) == 0)
                        descriptor |= (1 << (bit_position + i));
                    else
                        descriptor &= ~(1 << (bit_position + i));

                bit_position += num_bits;
                for (size_t i = bit_position; i < sizeof(uint16_t) * 8; i++)
                {
                    if (((1 << (bit_position - 1)) & descriptor) == 0)
                        descriptor |= (1 << (i));
                    else
                        descriptor &= ~(1 << (i));
                }


            }

            /**
             * @brief Appends a fixed-size type into a bytes vector.
             *
             * @tparam T have to be Primitive type.
             * @param msg The bytes vector to append the value to.
             * @param value The value to append.
             */
            template <typename T>
            static void appendFixedSizeTypeIntoBytes(bytes &msg, T value, bool isAck)
            {
                bytes converted_value;
                int16_t scaled_value;

                if constexpr (std::is_same<T, uint32_t>::value) {
                    if (isAck) {
                    std::cout << "ACK: " << value << std::endl;
                        converted_value.resize(ACK_SIZE);
                        std::memcpy(converted_value.data(), &value, ACK_SIZE);
                    } else {
                        if (value & 0xFF000000) {
                            converted_value.resize(4);
                        } else if (value & 0x00FF0000) {
                            converted_value.resize(3);
                        } else if (value & 0x0000FF00) {
                            converted_value.resize(2);
                        } else {
                            converted_value.resize(1);
                        }
                    }
                    std::memcpy(converted_value.data(), &value, converted_value.size());
                } else if constexpr (std::is_same<T, int>::value) {
                    if ((value & 0xFF00) == 0) {
                        converted_value.resize(1);
                        converted_value[0] = static_cast<uint8_t>(value);
                    } else {
                        converted_value.resize(2);
                        std::memcpy(converted_value.data(), &value, 2);
                    }
                }
                else if constexpr (std::is_same<T, double>::value) {
                        scaled_value = static_cast<int16_t>(value * 1000.0);
                        converted_value.resize(sizeof(scaled_value));
                        std::memcpy(converted_value.data(), &scaled_value, sizeof(scaled_value));
                }
                else {
                    converted_value.resize(sizeof(T));
                    std::memcpy(converted_value.data(), &value, sizeof(T));
                }

                msg.insert(msg.end(), converted_value.begin(), converted_value.end());
            }

            /**
             * @brief Extracts a fixed-size type from a bytes vector.
             *
             * @param offset The offset to start extracting from.
             * @param msg The bytes vector to extract the value from.
             * @param type_ The type of the value to extract.
             * @return The extracted value in a std::any.
             */
            static std::any newParam(std::size_t &offset, bytes msg, char type_, std::size_t size);

            /**
             * @brief Decrypts the descriptor to get the sizes of each argument.
             *
             * @param descriptor The descriptor to decrypt.
             * @param args_number The number of arguments.
             * @return A vector containing the sizes of the arguments.
             */
            static std::vector<std::size_t> decryptDescriptor(uint16_t descriptor, size_t args_number);

        public:
            Protocol() = delete;


            /**
             * @brief Convert a va_list to a vector of PrimitiveType.
             * @param params The va_list to convert.
             * @param params_type The types of the parameters.
             * @return The vector of PrimitiveType.
             */
            static std::vector<Utils::PrimitiveType>  va_listToVector(va_list params, std::string params_type) {
                std::vector<Utils::PrimitiveType> args;
                int int_arg;
                double double_arg;

                for (const char c: params_type) {
                    switch (c) {
                        case 'b':
                            args.push_back(va_arg(params, int));
                            break;
                        case 'c':
                            args.push_back(va_arg(params, int));
                            break;
                        case 'i':
                            int_arg = va_arg(params, int);
                            if (int_arg < -32768 || int_arg > 32767)
                                throw std::runtime_error("int argument is too big");
                            args.push_back(int_arg);
                            break;
                        case 'f':
                            double_arg = va_arg(params, double);
                            if (double_arg > 32.0 || double_arg < -32.0)
                                throw std::runtime_error("double argument is too big or too small");
                            args.push_back(double_arg);
                            break;
                        case 'l':
                            int_arg = va_arg(params, int);
                            args.push_back(int_arg);
                            break;
                        default:
                            throw std::runtime_error(std::string("Unknown type from map: ") + c);
                            break;
                    }
                }
                va_end(params);
                return args;
            }

            /**
             * @brief Encode the msg in bytes.
             * @tparam T The type of the function to send.
             * @param ack The ACK number.
             * @param info The type of the message.
             * @param functionDefiner The function to send.
             * @param args The list of arguments to send.
             * @return The message to send in bytes.
             */
            template<Utils::FunctionIndex T>
            static bytes CreateMsg(uint32_t ack, Utils::InfoTypeEnum info, T functionDefiner, std::vector<Utils::PrimitiveType> args)
            {
                bytes msg;
                std::size_t args_byte_bit_offset = 0x0;
                std::size_t args_byte_position = 0x0;

                std::cout << "ACK writing msg" << std::endl;
                std::cout << "InfoType: " << static_cast<uint32_t>(static_cast<uint8_t>(info)) << std::endl;
                std::cout << "InfoFunction: " << static_cast<uint32_t>(static_cast<uint8_t>(functionDefiner)) << std::endl;

                appendFixedSizeTypeIntoBytes(msg, ack, true);
                appendFixedSizeTypeIntoBytes(msg, info, false);
                appendFixedSizeTypeIntoBytes(msg, static_cast<uint8_t>(functionDefiner), false);
                args_byte_position = msg.size();
                appendFixedSizeTypeIntoBytes(msg, static_cast<uint16_t>(0x00), false);

                for (const auto &arg: args) {
                    std::visit([&msg, &args_byte_bit_offset, args_byte_position](auto &&value) {
                        using P = std::decay_t<decltype(value)>;
                        updateDescriptor<P>(*reinterpret_cast<uint16_t*>(&msg[args_byte_position]), args_byte_bit_offset, value);
                        appendFixedSizeTypeIntoBytes<P>(msg, value, value);
                    }, arg);
                }
                return msg;
            }

            /**
             * @brief Parse the message received.
             * @param isClient True if the message is read by a Client, False if it's read by a Server.
             * @param msg The message to parse.
             * @return The response to the message.
             */
            static Response ParseMsg(bool isClient, bytes &msg);
        };
    } // namespace Network

} // namespace Utils
