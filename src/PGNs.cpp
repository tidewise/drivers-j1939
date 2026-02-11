#include <j1939/J1939Receiver.hpp>
#include <j1939/PGNs.hpp>
#include <nmea2000/Decode.hpp>

using namespace j1939;
using namespace pgns;
using namespace nmea2000::decode;
using namespace nmea2000;

template <typename PGNType> void validate_message(nmea2000::Message const& message)
{
    if (message.pgn != PGNType::ID) {
        throw std::invalid_argument("unexpected PGN ID");
    }
    if (message.size < PGNType::BYTE_LENGTH) {
        throw std::invalid_argument("unexpected payload size");
    }
}

EletronicEngineController1 EletronicEngineController1::fromMessage(Message const& message)
{
    validate_message<EletronicEngineController1>(message);

    EletronicEngineController1 result;
    result.time = message.time;

    result.engine_torque_mode = (decode8(&message.payload[0]) & 0xf);
    result.drivers_demand_engine = decode8(&message.payload[1]);
    result.actual_engine = decode8(&message.payload[2]);
    result.engine_speed = decode16(&message.payload[3]);
    result.source_address = decode8(&message.payload[5]);
    result.engine_starter_mode = decode8(&message.payload[6]) & 0x0F;
    result.engine_demand = decode8(&message.payload[7]);

    return result;
}

EletronicEngineController2 EletronicEngineController2::fromMessage(Message const& message)
{

    validate_message<EletronicEngineController2>(message);

    EletronicEngineController2 result;
    result.time = message.time;

    result.selected_gear = decode8(&message.payload[0]);
    result.actual_gear_ratio = decode16(&message.payload[1]);
    result.current_gear = decode8(&message.payload[3]);
    result.transmission_requested_range = decode16(&message.payload[4]);
    result.transmission_current_range = decode16(&message.payload[6]);

    return result;
}

FuelEconomy FuelEconomy::fromMessage(Message const& message)
{
    validate_message<FuelEconomy>(message);

    FuelEconomy result;
    result.time = message.time;

    result.fuel_rate = decode16(&message.payload[0]);
    result.instantaneous_fuel_economy = decode16(&message.payload[2]);
    result.average_fuel_economy = decode16(&message.payload[4]);
    result.throttle_position_1 = decode8(&message.payload[6]);
    result.throttle_position_2 = decode8(&message.payload[7]);

    return result;
}

EngineFluidLevelAndPressure1 EngineFluidLevelAndPressure1::fromMessage(
    Message const& message)
{
    validate_message<EngineFluidLevelAndPressure1>(message);

    EngineFluidLevelAndPressure1 result;
    result.time = message.time;

    result.fuel_delivery_pressure = decode8(&message.payload[0]);
    result.extended_crankcase_blow_by_pressure = decode8(&message.payload[1]);
    result.engine_oil_level = decode8(&message.payload[2]);
    result.engine_oil_pressure = decode8(&message.payload[3]);
    result.crankcase_pressure = decode16(&message.payload[4]);
    result.coolant_pressure = decode8(&message.payload[6]);
    result.coolant_level = decode8(&message.payload[7]);

    return result;
}

EngineFluidLevelAndPressure2 EngineFluidLevelAndPressure2::fromMessage(
    Message const& message)
{
    validate_message<EngineFluidLevelAndPressure2>(message);


    EngineFluidLevelAndPressure2 result;
    result.time = message.time;

    result.injection_control_pressure = decode16(&message.payload[0]);
    result.injector_metering_rail_1_pressure = decode16(&message.payload[2]);
    result.injector_timing_rail_1_pressure = decode16(&message.payload[4]);
    result.injector_metering_rail_2_pressure = decode16(&message.payload[6]);

    return result;
}

InletConditions InletConditions::fromMessage(Message const& message)
{
    validate_message<InletConditions>(message);

    InletConditions result;
    result.time = message.time;

    result.particulate_trap_inlet_pressure = decode8(&message.payload[0]);
    result.boost_pressure = decode8(&message.payload[1]);
    result.intake_manifold_1_temperature = decode8(&message.payload[2]);
    result.air_inlet_pressure = decode8(&message.payload[3]);
    result.air_filter_1_differential_pressure = decode8(&message.payload[4]);
    result.exhaust_gas_temperature = decode16(&message.payload[5]);
    result.coolant_filter_differential_pressure = decode8(&message.payload[7]);

    return result;
}

EngineHoursAndRevolutions EngineHoursAndRevolutions::fromMessage(Message const& message)
{
    validate_message<EngineHoursAndRevolutions>(message);

    EngineHoursAndRevolutions result;
    result.time = message.time;

    result.total_engine_hours = decode32(&message.payload[0]);
    result.total_engine_revolutions = decode32(&message.payload[4]);

    return result;
}

VehicleElectricalPower1 VehicleElectricalPower1::fromMessage(Message const& message)
{
    validate_message<VehicleElectricalPower1>(message);

    VehicleElectricalPower1 result;
    result.time = message.time;

    result.net_battery_current = decode8(&message.payload[0]);
    result.alternator_current = decode8(&message.payload[1]);
    result.alternator_potential = decode16(&message.payload[2]);
    result.electrical_potential = decode16(&message.payload[4]);
    result.battery_potential = decode16(&message.payload[6]);

    return result;
}
EngineTemperature1 EngineTemperature1::fromMessage(Message const& message)
{
    validate_message<EngineTemperature1>(message);

    EngineTemperature1 result;
    result.time = message.time;

    result.engine_coolant_temperature = decode8(&message.payload[0]);
    result.fuel_temperature = decode8(&message.payload[1]);
    result.engine_oil_temperature = decode16(&message.payload[2]);
    result.turbo_oil_temperature = decode16(&message.payload[4]);
    result.engine_intercooler_temperature = decode8(&message.payload[6]);
    result.engine_intercooler_thermostat_opening = decode8(&message.payload[7]);

    return result;
}

TransportProtocolConnectionManagement TransportProtocolConnectionManagement::fromMessage(
    Message const& message)
{
    validate_message<TransportProtocolConnectionManagement>(message);

    TransportProtocolConnectionManagement result;
    result.time = message.time;

    result.control_byte = decode8(&message.payload[0]);
    result.message_size = decode16(&message.payload[1]);
    result.number_of_packets = decode8(&message.payload[3]);
    result.reserved = decode8(&message.payload[4]);
    result.pgn = (decode32(&message.payload[5])) & 0x00FFFFFF;

    return result;
}

nmea2000::PGNLibrary const& j1939::pgns::getLibrary()
{
    static nmea2000::PGNLibrary library;

    if (library.empty()) {
        std::vector<nmea2000::PGNInfo> known_pgns;
        known_pgns.reserve(10);
        known_pgns.push_back({61444, 8});
        known_pgns.push_back({61445, 8});
        known_pgns.push_back({65266, 8});
        known_pgns.push_back({65263, 8});
        known_pgns.push_back({65243, 8});
        known_pgns.push_back({65270, 8});
        known_pgns.push_back({60416, 8});
        known_pgns.push_back({65253, 8});
        known_pgns.push_back({65271, 8});
        known_pgns.push_back({65262, 8});

        library = nmea2000::PGNLibrary(known_pgns);
    }

    return library;
}