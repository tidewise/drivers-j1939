#include "Helpers.hpp"
#include <can_common/PGNMessage.hpp>

namespace j1939 {
    bool isBAM(can_common::PGNMessage const& message)
    {
        return message.pgn == PGN_TP_CM && message.payload[0] == TP_CM_BAM;
    }

    bool isConnectionManagement(can_common::PGNMessage const& message)
    {
        return message.pgn == PGN_TP_CM;
    }

    bool isDataTransfer(can_common::PGNMessage const& message)
    {
        return message.pgn == PGN_TP_DT;
    }

    uint64_t getKey(can_common::PGNMessage const& message)
    {
        return static_cast<uint64_t>(message.pgn) |
               static_cast<uint64_t>(message.source) << 24 |
               static_cast<uint64_t>(message.destination) << 32;
    }
}
