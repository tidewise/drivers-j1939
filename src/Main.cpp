#include <iodrivers_base/Driver.hpp>
#include <iostream>
#include <j1939/CAN.hpp>
#include <j1939/PGNs.hpp>
#include <j1939/Receiver.hpp>

using namespace std;
using namespace j1939;

void usage(ostream& stream)
{
    cerr << "usage: j1939_ctl URI\n";
    cerr << "\n";
    cerr << "Set up a CAN interface and print received J1939 PGN information.\n";
    cerr << "Arguments:\n";
    cerr << "URI is the can interface, eg.: can0\n";
    cerr << flush;
}

int main(int argc, char const* argv[])
{
    if (argc < 2) {
        usage(cout);
        return 0;
    }

    string uri = argv[1];

    j1939::CAN can_interface(uri, "socket");
    while (true) {
        try {
            auto msg = can_interface.readMessage();
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
