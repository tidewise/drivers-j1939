#ifndef J1939_RECEIVER_HPP
#define J1939_RECEIVER_HPP

#include <j1939/TransferSession.hpp>
#include <j1939/MessageState.hpp>
#include <can_common/PGNLibrary.hpp>

namespace j1939 {

    class Receiver {
    public:
        std::pair<j1939::MessageState, can_common::PGNMessage> process(
            can_common::PGNMessage const& msg);

    private:
        std::map<uint64_t, TransferSession> m_reassembly;
    };
}

#endif