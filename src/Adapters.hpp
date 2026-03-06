#ifndef J1939_ADAPTERS_HPP
#define J1939_ADAPTERS_HPP

#include <can_common/PGNLibrary.hpp>
#include <can_common/PGNMessage.hpp>
#include <canbus/Driver.hpp>
#include <j1939/PGNs.hpp>
#include <j1939/Receiver.hpp>

namespace canbus {
    class Driver;
}

namespace j1939 {
    namespace adapters {
        class Interface {
        protected:
            base::Time m_read_timeout = base::Time::fromSeconds(5);

        public:
            Interface();
            virtual ~Interface();
            void setReadTimeout(base::Time const& timeout);
            virtual can_common::PGNMessage readMessage() = 0;
        };

        class CAN : public Interface {
            canbus::Driver* m_driver = nullptr;
            can_common::PGNLibrary m_library;
            Receiver m_receiver;

        public:
            /** Open a CAN interface
             *
             * @param type the interface type. One of socket, hico, hico_pci,
             * net_gateway easy_sync. See drivers/canbus
             * (https://github.com/rock-drivers/drivers-canbus) for more information
             */
            CAN(std::string const& name, std::string const& type = "socket");
            ~CAN();

            can_common::PGNMessage readMessage();
        };
    }
}

#endif
