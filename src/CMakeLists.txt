rock_library(j1939
    SOURCES Receiver.cpp TransferSession.cpp Helpers.cpp PGNs.cpp Adapters.cpp
    HEADERS Receiver.hpp TransferSession.hpp Helpers.hpp PGNs.hpp Adapters.hpp
            MessageState.hpp
    DEPS_PKGCONFIG canbus base-types can_common)

rock_executable(j1939_ctl Main.cpp
    DEPS j1939)