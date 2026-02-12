#ifndef J1939_TRANSFERSESSION_HPP
#define J1939_TRANSFERSESSION_HPP

#include <can_common/PGNMessage.hpp>
#include "MessageState.hpp"

namespace j1939 {
    /**
     * @brief Used to reassembly Transport Protocol Data Transfer (TP.DT) messages
     *
     */
    struct TransferSession {
        /**
         * @brief The message to be reassembled
         *
         */
        can_common::PGNMessage message;
        /**
         * @brief The number of expected packets
         *
         */
        uint8_t number_of_packets = 0;
        uint8_t current_packets_count = 0;
        /**
         * @brief The current data size in bytes
         *
         */
        size_t current_data_size = 0;
        /**
         * @brief Initiates a TransportState from a Broadcast Announcement Message (BAM)
         *
         * @param message
         */
        void fromBAMMessage(can_common::PGNMessage const& message);
        /**
         * @brief Adds the data of a Data Transfer (DT) message to the data buffer and
         * returns the message state
         *
         * @param message The incoming message
         * @return MessageState The message state
         */
        MessageState add(can_common::PGNMessage const& message);
    };
}

#endif