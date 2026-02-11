#include "TransportState.hpp"
#include <cstring>
#include <nmea2000/Decode.hpp>
#include <j1939/Helpers.hpp>
#include <j1939/TransportState.hpp>

using namespace j1939;
using namespace nmea2000;
using namespace nmea2000::decode;
using namespace decode;
using namespace std;

void TransportState::fromBAMMessage(nmea2000::Message const& bam_message)
{
    if (!isBAM(bam_message)) {
        throw invalid_argument("Expected message to be Broadcast Announce Messag (BAM)");
    }
    number_of_packets = decode8(&bam_message.payload[3]);
    message = bam_message;
    message.pgn = decode32(&bam_message.payload[5]) & 0x00ffffff;
    message.size = decode16(&bam_message.payload[1]);
    current_packets_count = 0;
    current_data_size = 0;
    std::memset(message.payload, 0, message.size);
}

nmea2000::Receiver::State TransportState::add(nmea2000::Message const& incoming_msg)
{
    if (!isDataTransfer(incoming_msg)) {
        throw invalid_argument("Expected message to be a Data Transfer message (DT)");
    }
    uint8_t sequence_counter = decode8(&incoming_msg.payload[0]);
    if (sequence_counter != current_packets_count) {
        return Receiver::State::INVALID_SEQUENCE_NUMBER;
    }
    current_packets_count += 1;
    bool last_message = (sequence_counter == number_of_packets);
    size_t incoming_size =
        last_message ? message.size - current_data_size : message.size - 1;
    current_data_size += incoming_size;
    memcpy(message.payload + current_data_size, message.payload + 1, incoming_size);
    message.time = base::Time::now();
    return last_message ? Receiver::State::COMPLETE : Receiver::State::PROCESSED;
}
