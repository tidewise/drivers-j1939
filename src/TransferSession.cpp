#include "TransferSession.hpp"
#include <can_common/Decode.hpp>
#include <cstring>
#include <j1939/Helpers.hpp>

using namespace j1939;
using namespace can_common::decode;
using namespace std;

void TransferSession::fromBAMMessage(can_common::PGNMessage const& bam_message)
{
    if (!isBAM(bam_message)) {
        throw invalid_argument("Expected message to be Broadcast Announce Message (BAM)");
    }
    number_of_packets = decode8(&bam_message.payload[3]);
    message = bam_message;
    message.pgn = decode32(&bam_message.payload[5]) & 0x00ffffff;
    message.size = decode16(&bam_message.payload[1]);
    current_packets_count = 0;
    current_data_size = 0;
    std::memset(message.payload, 0, message.size);
}

MessageState TransferSession::add(can_common::PGNMessage const& incoming_msg)
{
    if (!isDataTransfer(incoming_msg)) {
        throw invalid_argument("Expected message to be a Data Transfer message (DT)");
    }
    uint8_t sequence_counter = decode8(&incoming_msg.payload[0]);
    current_packets_count += 1;
    if (sequence_counter != current_packets_count) {
        return MessageState::INVALID_SEQUENCE_NUMBER;
    }
    bool last_message = (sequence_counter == number_of_packets);
    size_t incoming_size =
        last_message ? message.size - current_data_size : incoming_msg.size - 1;
    memcpy(message.payload + current_data_size, incoming_msg.payload + 1, incoming_size);
    current_data_size += incoming_size;
    message.time = base::Time::now();
    return last_message ? MessageState::COMPLETE : MessageState::PROCESSED;
}
