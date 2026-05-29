#ifndef J1939_RECEIVER_HPP
#define J1939_RECEIVER_HPP

#include <can_common/PGNLibrary.hpp>
#include <j1939/MessageState.hpp>
#include <j1939/TransferSession.hpp>

namespace j1939 {

    class Receiver {
    public:
        Receiver(can_common::PGNLibrary& library);
        std::pair<j1939::MessageState, can_common::PGNMessage> process(
            can_common::PGNMessage const& msg);

    private:
        std::map<uint64_t, TransferSession> m_reassembly;
        can_common::PGNLibrary& m_library;
    };
}

#endif