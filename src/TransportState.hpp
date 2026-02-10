#ifndef J1939_TRANSPORTSTATE_HPP
#define J1939_TRANSPORTSTATE_HPP

#include <nmea2000/Message.hpp>
#include <nmea2000/Receiver.hpp>

namespace j1939 {
    /**
     * @brief Used to reassembly Transport Protocol (TP) messages
     *
     */
    struct TransportState {
        /**
         * @brief Maximum transport protocol message size
         *
         */
        static const int MAX_TP_SIZE = 1785;

        /**
         * @brief The PGN of the reassembled messsage
         *
         */
        uint32_t pgn = 0;
        /**
         * @brief The message size in bytes
         *
         */
        uint16_t total_data_size = 0;
        /**
         * @brief The number of expected packets
         *
         */
        uint8_t number_of_packets = 0;
        int current_packets_count = 0;
        /**
         * @brief The current data size in bytes
         *
         */
        size_t current_data_size = 0;
        /**
         * @brief The data buffer
         *
         */
        uint8_t data[MAX_TP_SIZE];

        /**
         * @brief Initiates a TransportState from a Broadcast Announcement Message (BAM)
         *
         * @param message
         */
        void fromBAMMessage(nmea2000::Message const& message);
        /**
         * @brief Adds the data of a Data Transfer (DT) message to the data buffer and
         * returns the message state
         *
         * @param message The incoming message
         * @return nmea2000::Receiver::State The message state
         */
        nmea2000::Receiver::State add(nmea2000::Message const& message);
    };
}

#endif