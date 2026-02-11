#include <iostream>
#include <j1939/J1939Receiver.hpp>
// #include <nmea2000/PGNs.hpp>
#include <iodrivers_base/Driver.hpp>
#include <j1939/PGNs.hpp>
#include <j1939/Adapters.hpp>
#include <nmea2000/Adapters.hpp>

using namespace std;
using namespace nmea2000;

int main(int argc, char const* argv[])
{
    string type = argv[1];
    string uri = argv[2];

    adapters::Interface* interface = nullptr;
    if (type == "can") {
        interface = new j1939::adapters::J1939CAN(uri, "socket");
    }
    else if (type == "actisense") {
        throw invalid_argument("Not implemented");
    }
    else {
        cerr << "unknown connection type '" << type << "'\n\n";
        return 1;
    }
    while (true) {
        try {
            auto msg = interface->readMessage();
            cout << "msg.time: " << msg.time << " " << "msg.pgn: " << msg.pgn << " "
                 << "msg.priority: " << msg.priority << " " << "msg.size: " << msg.size
                 << endl;
        }
        catch (iodrivers_base::TimeoutError&) {
            cout << "TIMEOUT" << endl;
        }
    }
    return 0;
}
