#include <j1939/Helpers.hpp>
#include <j1939/Receiver.hpp>
#include <utility>

using namespace j1939;
using namespace std;
using namespace can_common;

bool keyFound(std::map<uint64_t, j1939::TransferSession>::iterator const& map_iterator,
    map<uint64_t, j1939::TransferSession> const& reassembly_map)
{
    return map_iterator != reassembly_map.end();
}

void deleteOldIncompleteMessages(
    std::map<uint64_t, j1939::TransferSession>::iterator const& map_iterator,
    map<uint64_t, j1939::TransferSession>& reassembly_map)
{
    if (keyFound(map_iterator, reassembly_map)) {
        reassembly_map.erase(map_iterator);
        // TODO: Increment lost data statistics
    }
}

std::pair<MessageState, can_common::PGNMessage> processBAM(
    map<uint64_t, j1939::TransferSession>& reassembly_map,
    can_common::PGNMessage const& message,
    uint64_t key)
{
    TransferSession transfer;
    transfer.fromBAMMessage(message);
    reassembly_map[key] = transfer;
    return make_pair(MessageState::PROCESSED, transfer.message);
}

std::pair<MessageState, can_common::PGNMessage> processDTMessage(
    map<uint64_t, j1939::TransferSession>& reassembly_map,
    can_common::PGNMessage const& message,
    uint64_t key,
    std::map<uint64_t, j1939::TransferSession>::iterator const& map_iterator)
{
    if (!keyFound(map_iterator, reassembly_map)) {
        return make_pair(MessageState::INVALID_SEQUENCE_NUMBER, message);
    }
    auto state = map_iterator->second.add(message);
    can_common::PGNMessage return_message;
    if (state == COMPLETE) {
        return_message = map_iterator->second.message;
    }
    else if (state == PROCESSED) {
        return_message = message;
    }
    if (state != PROCESSED) {
        reassembly_map.erase(map_iterator);
    }
    return make_pair(state, return_message);
}

std::pair<MessageState, can_common::PGNMessage> Receiver::process(PGNMessage const& msg)
{
    uint64_t key = getKey(msg);
    auto it = m_reassembly.find(key);

    if (isConnectionManagement(msg)) {
        deleteOldIncompleteMessages(it, m_reassembly);
        if (isBAM(msg)) {
            return processBAM(m_reassembly, msg, key);
        }
        // TODO: RTS
        // TODO: send CTS/EoMA
        // provisory return
        return make_pair(MessageState::UNKNOWN_PGN, msg);
    }
    else if (isDataTransfer(msg)) {
        processDTMessage(m_reassembly, msg, key, it);
    }
    return make_pair(MessageState::COMPLETE, msg);
}