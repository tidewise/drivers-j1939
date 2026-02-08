rock_library(j1939
    SOURCES Dummy.cpp
    HEADERS Dummy.hpp)

rock_executable(j1939_bin Main.cpp
    DEPS j1939)

