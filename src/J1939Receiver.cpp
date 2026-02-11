#include <j1939/Helpers.hpp>
#include <j1939/J1939Receiver.hpp>
#include <utility>

using namespace j1939;
using namespace nmea2000;
using namespace std;

std::pair<Receiver::State, Message> J1939Receiver::process(Message const& msg)
{
    uint64_t key = getKey(msg);
    auto it = m_reassembly.find(key);

    if (isConnectionManagement(msg)) {
        if (isBAM(msg)) {
            TransportState state;
            state.fromBAMMessage(msg);
            m_reassembly[key] = state;
            return make_pair(Receiver::State::PROCESSED, state.message);
        }
        else {
            // TODO: RTS
            // TODO: send CTS/EoMA
            // provisory return
            return make_pair(Receiver::State::INVALID_SEQUENCE_NUMBER, msg);
        }
    }
    else if (isDataTransfer(msg)) {
        if (it == m_reassembly.end()) {
            return make_pair(Receiver::State::INVALID_SEQUENCE_NUMBER, msg);
        }
        auto state = it->second.add(msg);
        Message return_message;
        if (state == COMPLETE) {
            return_message = it->second.message;
        }
        else if (state == PROCESSED) {
            return_message = msg;
        }
        if (state != PROCESSED) {
            m_reassembly.erase(it);
        }
        return make_pair(state, return_message);
    }
    else {
        return Receiver::process(msg);
    }
}