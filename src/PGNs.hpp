#ifndef J1939_PGNS_HPP
#define J1939_PGNS_HPP

#include <nmea2000/Message.hpp>
#include <nmea2000/PGNLibrary.hpp>

namespace j1939 {
    namespace pgns {

        nmea2000::PGNLibrary const& getLibrary();

        struct ElectronicEngineController1 {
            static constexpr int BYTE_LENGTH = 8;
            static constexpr int ID = 61444;

            static ElectronicEngineController1 fromMessage(
                nmea2000::Message const& message);

            base::Time time;

            uint8_t engine_torque_mode;
            // Driver's demand engine (percent torque)
            uint8_t drivers_demand_engine;
            // Actual engine (percent torque)
            uint8_t actual_engine;
            uint16_t engine_speed;
            // Source address of controlling device for engine control
            uint8_t source_address;
            uint8_t engine_starter_mode;
            // The engine demand (percent torque)
            uint8_t engine_demand;
        };
        struct ElectronicEngineController2 {
            static constexpr int BYTE_LENGTH = 8;
            static constexpr int ID = 61445;

            static ElectronicEngineController2 fromMessage(
                nmea2000::Message const& message);

            base::Time time;

            uint8_t selected_gear;
            uint16_t actual_gear_ratio;
            uint8_t current_gear;
            uint16_t transmission_requested_range;
            uint16_t transmission_current_range;
        };
        struct FuelEconomy {
            static constexpr int BYTE_LENGTH = 8;
            static constexpr int ID = 65266;

            static FuelEconomy fromMessage(nmea2000::Message const& message);

            base::Time time;

            uint16_t fuel_rate;
            uint16_t instantaneous_fuel_economy;
            uint16_t average_fuel_economy;
            uint8_t throttle_position_1;
            // todo fix name
            uint8_t throttle_position_2;
        };
        struct EngineFluidLevelAndPressure1 {
            static constexpr int BYTE_LENGTH = 8;
            static constexpr int ID = 65263;

            static EngineFluidLevelAndPressure1 fromMessage(
                nmea2000::Message const& message);

            base::Time time;

            uint8_t fuel_delivery_pressure;
            uint8_t extended_crankcase_blow_by_pressure;
            uint8_t engine_oil_level;
            uint8_t engine_oil_pressure;
            uint16_t crankcase_pressure;
            uint8_t coolant_pressure;
            uint8_t coolant_level;
        };
        struct EngineFluidLevelAndPressure2 {
            static constexpr int BYTE_LENGTH = 8;
            static constexpr int ID = 65243;

            static EngineFluidLevelAndPressure2 fromMessage(
                nmea2000::Message const& message);

            base::Time time;

            uint16_t injection_control_pressure;
            uint16_t injector_metering_rail_1_pressure;
            uint16_t injector_timing_rail_1_pressure;
            uint16_t injector_metering_rail_2_pressure;
        };
        struct InletConditions {
            static constexpr int BYTE_LENGTH = 8;
            static constexpr int ID = 65270;

            static InletConditions fromMessage(nmea2000::Message const& message);

            base::Time time;

            uint8_t particulate_trap_inlet_pressure;
            uint8_t boost_pressure;
            uint8_t intake_manifold_1_temperature;
            uint8_t air_inlet_pressure;
            uint8_t air_filter_1_differential_pressure;
            uint16_t exhaust_gas_temperature;
            uint8_t coolant_filter_differential_pressure;
        };
        struct TransportProtocolConnectionManagement {
            static constexpr int BYTE_LENGTH = 8;
            static constexpr int ID = 60416;

            static TransportProtocolConnectionManagement fromMessage(
                nmea2000::Message const& message);

            base::Time time;

            // TODO bam or control_byte?
            uint8_t control_byte;
            // nmea2000::Message size (bytes)
            uint16_t message_size;
            uint8_t number_of_packets;
            uint8_t reserved;
            uint32_t pgn;
        };
        struct EngineHoursAndRevolutions {
            static constexpr int BYTE_LENGTH = 8;
            static constexpr int ID = 65253;

            static EngineHoursAndRevolutions fromMessage(
                nmea2000::Message const& message);

            base::Time time;

            uint32_t total_engine_hours;
            uint32_t total_engine_revolutions;
        };
        struct VehicleElectricalPower1 {
            static constexpr int BYTE_LENGTH = 8;
            static constexpr int ID = 65271;

            static VehicleElectricalPower1 fromMessage(nmea2000::Message const& message);

            base::Time time;

            uint8_t net_battery_current;
            uint8_t alternator_current;
            uint16_t alternator_potential;
            uint16_t electrical_potential;
            uint16_t battery_potential;
        };
        struct EngineTemperature1 {
            static constexpr int BYTE_LENGTH = 8;
            static constexpr int ID = 65262;

            static EngineTemperature1 fromMessage(nmea2000::Message const& message);

            base::Time time;

            uint8_t engine_coolant_temperature;
            uint8_t fuel_temperature;
            uint16_t engine_oil_temperature;
            uint16_t turbo_oil_temperature;
            uint8_t engine_intercooler_temperature;
            uint8_t engine_intercooler_thermostat_opening;
        };
    }
}

#endif