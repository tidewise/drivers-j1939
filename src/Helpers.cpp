#include <j1939/Helpers.hpp>

using namespace nmea2000;

namespace j1939 {
    bool isBAM(Message const& message)
    {
        return message.pgn == PGN_TP_CM && message.payload[0] == TP_CM_BAM;
    }

    bool isConnectionManagement(Message const& message)
    {
        return message.pgn == PGN_TP_CM;
    }

    bool isDataTransfer(Message const& message)
    {
        return message.pgn == PGN_TP_DT;
    }
}
