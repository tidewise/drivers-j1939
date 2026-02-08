#include <j1939/Decode.hpp>
#include <j1939/PGNs.hpp>

using namespace j1939;
using namespace decode;

EletronicEngineController1 EletronicEngineController1::fromMessage(Message const& message)
{
    if (message.pgn != ID) {
        throw std::invalid_argument("unexpected PGN ID");
    }
    else if (message.size < BYTE_LENGTH) {
        throw std::invalid_argument("unexpected payload size");
    }

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

    if (message.pgn != ID) {
        throw std::invalid_argument("unexpected PGN ID");
    }
    else if (message.size < BYTE_LENGTH) {
        throw std::invalid_argument("unexpected payload size");
    }

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
    if (message.pgn != ID) {
        throw std::invalid_argument("unexpected PGN ID");
    }
    else if (message.size < BYTE_LENGTH) {
        throw std::invalid_argument("unexpected payload size");
    }

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
    if (message.pgn != ID) {
        throw std::invalid_argument("unexpected PGN ID");
    }
    else if (message.size < BYTE_LENGTH) {
        throw std::invalid_argument("unexpected payload size");
    }

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
    if (message.pgn != ID) {
        throw std::invalid_argument("unexpected PGN ID");
    }
    else if (message.size < BYTE_LENGTH) {
        throw std::invalid_argument("unexpected payload size");
    }

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
    if (message.pgn != ID) {
        throw std::invalid_argument("unexpected PGN ID");
    }
    else if (message.size < BYTE_LENGTH) {
        throw std::invalid_argument("unexpected payload size");
    }

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
    if (message.pgn != ID) {
        throw std::invalid_argument("unexpected PGN ID");
    }
    else if (message.size < BYTE_LENGTH) {
        throw std::invalid_argument("unexpected payload size");
    }

    EngineHoursAndRevolutions result;
    result.time = message.time;

    result.total_engine_hours = decode32(&message.payload[0]);
    result.total_engine_revolutions = decode32(&message.payload[4]);

    return result;
}

VehicleElectricalPower1 VehicleElectricalPower1::fromMessage(Message const& message)
{
    if (message.pgn != ID) {
        throw std::invalid_argument("unexpected PGN ID");
    }
    else if (message.size < BYTE_LENGTH) {
        throw std::invalid_argument("unexpected payload size");
    }

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
    if (message.pgn != ID) {
        throw std::invalid_argument("unexpected PGN ID");
    }
    else if (message.size < BYTE_LENGTH) {
        throw std::invalid_argument("unexpected payload size");
    }

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
    if (message.pgn != ID) {
        throw std::invalid_argument("unexpected PGN ID");
    }
    else if (message.size < BYTE_LENGTH) {
        throw std::invalid_argument("unexpected payload size");
    }

    TransportProtocolConnectionManagement result;
    result.time = message.time;

    result.control_byte = decode8(&message.payload[0]);
    result.message_size = decode16(&message.payload[1]);
    result.number_of_packets = decode8(&message.payload[3]);
    result.reserved = decode8(&message.payload[4]);
    result.pgn = (decode32(&message.payload[5])) & 0x00FFFFFF;

    return result;
}