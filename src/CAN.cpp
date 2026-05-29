#include <canbus/Driver.hpp>
#include <iodrivers_base/Driver.hpp>
#include <j1939/CAN.hpp>

using namespace base;
using namespace j1939;

void CAN::setReadTimeout(base::Time const& timeout)
{
    m_read_timeout = timeout;
}

CAN::CAN(std::string const& name, std::string const& type)
    : m_driver(canbus::openCanDevice(name, type))
    , m_library(pgns::getLibrary())
    , m_receiver(m_library)
{
}

CAN::~CAN()
{
    m_driver->close();
    delete m_driver;
}

struct CANReadTimeoutGuard {
    canbus::Driver& m_driver;
    base::Time m_original_timeout;

    CANReadTimeoutGuard(canbus::Driver& driver)
        : m_driver(driver)
        , m_original_timeout(base::Time::fromMilliseconds(driver.getReadTimeout()))
    {
    }

    ~CANReadTimeoutGuard()
    {
        m_driver.setReadTimeout(m_original_timeout.toMilliseconds());
    }
};

can_common::PGNMessage CAN::readMessage()
{
    auto deadline = Time::now() + m_read_timeout;
    Time remaining = m_read_timeout;
    CANReadTimeoutGuard guard(*m_driver);
    while (true) {
        m_driver->setReadTimeout(remaining.toMilliseconds());

        canbus::Message msg = m_driver->read();
        auto state = m_receiver.process(can_common::PGNMessage::fromCAN(msg));
        if (state.first >= MessageState::COMPLETE) {
            return state.second;
        }

        remaining = deadline - Time::now();
        if (remaining < Time()) {
            throw iodrivers_base::TimeoutError(iodrivers_base::TimeoutError::PACKET,
                "timed out reading CAN");
        }
    }
}
