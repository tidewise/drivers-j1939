#ifndef J1939_DECODE_HPP
#define J1939_DECODE_HPP

#include <algorithm>
#include <cstdint>
#include <string>

namespace j1939 {
    namespace decode {
        inline std::uint64_t decode64(std::uint8_t const* byte)
        {
            return static_cast<std::uint64_t>(byte[7]) << 56 |
                   static_cast<std::uint64_t>(byte[6]) << 48 |
                   static_cast<std::uint64_t>(byte[5]) << 40 |
                   static_cast<std::uint64_t>(byte[4]) << 32 |
                   static_cast<std::uint64_t>(byte[3]) << 24 |
                   static_cast<std::uint64_t>(byte[2]) << 16 |
                   static_cast<std::uint64_t>(byte[1]) << 8 |
                   static_cast<std::uint64_t>(byte[0]) << 0;
        }

        inline std::uint32_t decode32(std::uint8_t const* byte)
        {
            return static_cast<std::uint32_t>(byte[3]) << 24 |
                   static_cast<std::uint32_t>(byte[2]) << 16 |
                   static_cast<std::uint32_t>(byte[1]) << 8 |
                   static_cast<std::uint32_t>(byte[0]) << 0;
        }

        inline std::uint16_t decode16(std::uint8_t const* byte)
        {
            return static_cast<std::uint16_t>(byte[1]) << 8 |
                   static_cast<std::uint16_t>(byte[0]) << 0;
        }

        inline std::uint8_t decode8(std::uint8_t const* byte)
        {
            return byte[0];
        }

        inline std::string decodeString(std::uint8_t const* byte, int length)
        {
            auto end = std::find(byte, byte + length, 0);
            return std::string(byte, end);
        }
    };
}

#endif