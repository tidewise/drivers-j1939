rock_library(j1939
    SOURCES PGNs.cpp J1939Receiver.cpp TransportState.cpp Helpers.cpp
    HEADERS PGNs.hpp J1939Receiver.hpp TransportState.hpp Helpers.hpp Adapters.hpp
    DEPS_PKGCONFIG canbus base-types nmea2000)

rock_executable(j1939_bin Main.cpp
    DEPS j1939)