#ifndef J1939_MESSAGE_HPP
#define J1939_MESSAGE_HPP

#include <base/Time.hpp>

namespace j1939 {
    /**
     *
     */
    struct Message {
        /**
         * @brief Transport Protocol (TP) maximum payload length
         *
         */
        static const int TP_MAX_PAYLOAD_LENGTH = 1785;

        base::Time time;

        uint8_t priority = 0;
        uint8_t source = 0;
        uint8_t destination = 0;
        uint32_t pgn = 0;
        uint8_t size = 0;
        uint8_t payload[TP_MAX_PAYLOAD_LENGTH];
    };
}

#endif