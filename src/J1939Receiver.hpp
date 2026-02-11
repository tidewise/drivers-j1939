#ifndef J1939_J1939RECEIVER_HPP
#define J1939_J1939RECEIVER_HPP

#include <j1939/TransportState.hpp>
#include <nmea2000/Receiver.hpp>

namespace j1939 {

    class J1939Receiver : public nmea2000::Receiver {
    public:
        std::pair<nmea2000::Receiver::State, nmea2000::Message> process(
            nmea2000::Message const& msg) override;

        J1939Receiver(nmea2000::PGNLibrary& library)
            : nmea2000::Receiver(library)
        {
        }

    private:
        std::map<uint64_t, TransportState> m_reassembly;
    };
}

#endif