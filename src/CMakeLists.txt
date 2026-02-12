rock_library(j1939
    SOURCES Receiver.cpp TransferSession.hpp Helpers.cpp PGNs.cpp
    HEADERS Receiver.hpp TransferSession.hpp Helpers.hpp PGNs.hpp MessageState.hpp
    DEPS_PKGCONFIG canbus base-types can_common)