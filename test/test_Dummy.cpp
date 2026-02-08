#include <boost/test/unit_test.hpp>
#include <j1939/Dummy.hpp>

using namespace j1939;

BOOST_AUTO_TEST_CASE(it_should_not_crash_when_welcome_is_called)
{
    j1939::DummyClass dummy;
    dummy.welcome();
}
