#include <gtest/gtest.h>
#include <j1939/PGNs.hpp>

using namespace j1939;
using namespace pgns;
using namespace std;
using namespace nmea2000;

struct PGNsTest : public ::testing::Test {};

template <typename M>
M parse_message(vector<uint8_t> const& payload,
    int size = 0,
    base::Time const& time = base::Time::now());

TEST_F(PGNsTest, ir_parses_pgn_61444)
{
    auto parsed = parse_message<EletronicEngineController1>(
        {0x01, 0x50, 0x5A, 0x40, 0x1F, 0x0A, 0x01, 0x51});
    ASSERT_EQ(1, parsed.engine_torque_mode);
    ASSERT_EQ(80, parsed.drivers_demand_engine);
    ASSERT_EQ(90, parsed.actual_engine);
    ASSERT_EQ(8000, parsed.engine_speed);
    ASSERT_EQ(10, parsed.source_address);
    ASSERT_EQ(1, parsed.engine_starter_mode);
    ASSERT_EQ(81, parsed.engine_demand);
}

TEST_F(PGNsTest, ir_parses_pgn_61445)
{
    auto parsed = parse_message<EletronicEngineController2>(
        {0x07, 0x06, 0x15, 0x03, 0x28, 0x01, 0x64, 0x02});
    ASSERT_EQ(7, parsed.selected_gear);
    ASSERT_EQ(5382, parsed.actual_gear_ratio);
    ASSERT_EQ(3, parsed.current_gear);
    ASSERT_EQ(296, parsed.transmission_requested_range);
    ASSERT_EQ(612, parsed.transmission_current_range);
}

TEST_F(PGNsTest, ir_parses_pgn_65266)
{
    auto parsed =
        parse_message<FuelEconomy>({0xE8, 0x03, 0x00, 0x10, 0x00, 0x20, 0x64, 0xC8});
    ASSERT_EQ(1000, parsed.fuel_rate);
    ASSERT_EQ(4096, parsed.instantaneous_fuel_economy);
    ASSERT_EQ(8192, parsed.average_fuel_economy);
    ASSERT_EQ(100, parsed.throttle_position_1);
    ASSERT_EQ(200, parsed.throttle_position_2);
}

TEST_F(PGNsTest, ir_parses_pgn_65263)
{
    auto parsed = parse_message<EngineFluidLevelAndPressure1>(
        {0x96, 0x14, 0x80, 0xC8, 0x50, 0x00, 0x64, 0xB4});
    ASSERT_EQ(150, parsed.fuel_delivery_pressure);
    ASSERT_EQ(20, parsed.extended_crankcase_blow_by_pressure);
    ASSERT_EQ(128, parsed.engine_oil_level);
    ASSERT_EQ(200, parsed.engine_oil_pressure);
    ASSERT_EQ(80, parsed.crankcase_pressure);
    ASSERT_EQ(100, parsed.coolant_pressure);
    ASSERT_EQ(180, parsed.coolant_level);
}

TEST_F(PGNsTest, ir_parses_pgn_60416)
{
    auto parsed = parse_message<TransportProtocolConnectionManagement>(
        {0x20, 0x12, 0x00, 0x03, 0xFF, 0xEC, 0xFE, 0x00});
    ASSERT_EQ(32, parsed.control_byte);
    ASSERT_EQ(18, parsed.message_size);
    ASSERT_EQ(3, parsed.number_of_packets);
    ASSERT_EQ(255, parsed.reserved);
    ASSERT_EQ(65260, parsed.pgn);
}

template <typename M>
M parse_message(vector<uint8_t> const& payload, int size, base::Time const& time)
{
    Message message;
    message.time = time;
    message.pgn = M::ID;
    message.size = size == 0 ? payload.size() : size;
    std::copy(payload.begin(), payload.end(), message.payload);
    return M::fromMessage(message);
}