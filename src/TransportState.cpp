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

void TransportState::fromBAMMessage(nmea2000::Message const& message)
{
    if (!isBAM(message)) {
        throw invalid_argument("Expected message to be Broadcast Announce Messag (BAM)");
    }
    total_data_size = decode16(&message.payload[1]);
    number_of_packets = decode8(&message.payload[3]);
    pgn = decode32(&message.payload[5]) & 0x00ffffff;
    current_packets_count = 0;
    current_data_size = 0;
    std::memset(data, 0, total_data_size);
}

nmea2000::Receiver::State TransportState::add(nmea2000::Message const& message)
{
    if (!isDataTransfer(message)) {
        throw invalid_argument("Expected message to be a Data Transfer message (DT)");
    }
    uint8_t sequence_counter = decode8(&message.payload[0]);
    if (sequence_counter != current_packets_count) {
        return Receiver::State::INVALID_SEQUENCE_NUMBER;
    }
    current_packets_count += 1;
    bool last_message = (sequence_counter == number_of_packets);
    size_t incoming_size =
        last_message ? total_data_size - current_data_size : message.size - 1;
    current_data_size += incoming_size;
    memcpy(data + current_data_size, message.payload + 1, incoming_size);
    return last_message ? Receiver::State::COMPLETE : Receiver::State::PROCESSED;
}
