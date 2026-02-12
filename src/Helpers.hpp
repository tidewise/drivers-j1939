#ifndef J1939_HELPERS_HPP
#define J1939_HELPERS_HPP

#include <can_common/PGNMessage.hpp>

namespace j1939 {
    static constexpr uint32_t PGN_TP_CM = 60416; // 0xEC00
    static constexpr uint32_t PGN_TP_DT = 60160; // 0xEB00
    static constexpr uint8_t TP_CM_BAM = 32;     // Broadcast Announce Message

    bool isBAM(can_common::PGNMessage const& message);
    bool isConnectionManagement(can_common::PGNMessage const& message);
    bool isDataTransfer(can_common::PGNMessage const& message);
    uint64_t getKey(can_common::PGNMessage const& messsage);
}

#endif