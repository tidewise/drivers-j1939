#ifndef J1939_HELPERS_HPP
#define J1939_HELPERS_HPP

#include <can_common/PGNMessage.hpp>

namespace j1939 {
    /**
     * @brief Transport Protocol Connection Management (TP.CM) PGN - 0xEC00
     *
     */
    static constexpr uint32_t PGN_TP_CM = 60416;
    /**
     * @brief Transport Protocol Data Transfer (TP.DT) PGN - 0xEB00
     *
     */
    static constexpr uint32_t PGN_TP_DT = 60160;
    /**
     * @brief Broadcast Announce Message control byte
     *
     * The control byte of the Transport Protocol Connection Management (TP.CM) when
     * Broadcast Announce Message (BAM) - 0x20
     *
     */
    static constexpr uint8_t TP_CM_BAM = 32; // Broadcast Announce Message

    /**
     * @brief Checks if a PGN message is a Broadcast Announce Message (BAM)
     *
     * In the J1939 Transport Protocol (TP), a BAM is used to initiate multi-packet
     * data transfers to a global destination
     *
     * @param message The PGN message to be evaluated
     * @return true If the message is a BAM connection management frame
     * @return false Otherwise
     */
    bool isBAM(can_common::PGNMessage const& message);

    /**
     * @brief Checks if a PGN message is a TP Connection Management (TP.CM) frame
     *
     * Connection Management is the "handshaking" protocol used to coordinate
     * multi-packet transfers. It handles the setup (RTS/BAM), flow control (CTS),
     * and teardown (ACK/Abort) of a data session.
     *
     * @param message The PGN message to be evaluated
     * @return true If the PGN matches PGN_TP_CM (0xEC00)
     * @return false Otherwise
     */
    bool isConnectionManagement(can_common::PGNMessage const& message);

    /**
     * @brief Checks if a PGN message is a TP Data Transfer (TP.DT) frame.
     *
     * TP.DT frames are used to carry the actual data segments of a multi-packet
     * message after a connection has been established via a TP.CM frame.
     *
     * @param message The PGN message (can_common::PGNMessage) to be evaluated.
     * @return true If the PGN matches PGN_TP_DT (0xEB00).
     * @return false Otherwise.
     */
    bool isDataTransfer(can_common::PGNMessage const& message);

    /**
     * @brief Generates a unique 64-bit identifier for a specific J1939 communication
     * session
     *
     * This key is constructed by combining the PGN, Source Address, and Destination
     * Address. It is primarily used as a lookup key in maps or trackers to manage
     * concurrent Transport Protocol sessions between different nodes
     *
     * @param message The PGN message used to generate the session key
     * @return uint64_t A composite key representing the PGN/Source/Destination
     * triplet
     */
    uint64_t getKey(can_common::PGNMessage const& messsage);
}

#endif