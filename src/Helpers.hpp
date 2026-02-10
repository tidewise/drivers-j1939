#ifndef J1939_HELPERS_HPP
#define J1939_HELPERS_HPP

#include <nmea2000/Message.hpp>

namespace j1939 {
    static constexpr uint32_t PGN_TP_CM = 60416; // 0xEC00
    static constexpr uint32_t PGN_TP_DT = 60160; // 0xEB00
    static constexpr uint8_t TP_CM_BAM = 32;     // Broadcast Announce Message

    bool isBAM(nmea2000::Message const& message);
    bool isConnectionManagement(nmea2000::Message const& message);
    bool isDataTransfer(nmea2000::Message const& message);
}

#endif