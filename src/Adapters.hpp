#ifndef J1939_ADAPTERS_HPP
#define J1939_ADAPTERS_HPP

#include <j1939/J1939Receiver.hpp>
#include <j1939/PGNs.hpp>
#include <nmea2000/Adapters.hpp>

namespace j1939 {
    namespace adapters {
        class J1939CAN : public nmea2000::adapters::CAN {
        public:
            J1939CAN(std::string const& name, std::string const& type = "socket")
                : nmea2000::adapters::CAN(name, type)
            {
                m_library = j1939::pgns::getLibrary();
                m_receiver = std::make_unique<j1939::J1939Receiver>(m_library);
            }
        };
    }
}

#endif