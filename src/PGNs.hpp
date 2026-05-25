#ifndef J1939_PGNS_HPP
#define J1939_PGNS_HPP

#include <can_common/PGNLibrary.hpp>
#include <can_common/PGNMessage.hpp>

/**
 * @namespace j1939::pgns
 * @brief Logic for handling SAE J1939 Parameter Group Numbers.
 */
namespace j1939 {
    namespace pgns {
        can_common::PGNLibrary const& getLibrary();

        /**
         * @brief Electronic Engine Controller 1 (EEC1) - PGN 61444
         */
        struct ElectronicEngineController1 {
            static constexpr int BYTE_LENGTH = 8;
            static constexpr int ID = 61444;

            static ElectronicEngineController1 fromMessage(
                can_common::PGNMessage const& message);

            /** @brief Reception timestamp. */
            base::Time time;

            /**
             * @brief State of engine torque control system.
             * @note Unit: Control State (Bit-mapped)
             */
            uint8_t engine_torque_mode;

            /**
             * @brief Driver's requested torque.
             * @note Unit: % | Scaling: 1%/bit | Offset: -125%
             */
            uint8_t drivers_demand_engine;

            /**
             * @brief Actual torque output.
             * @note Unit: % | Scaling: 1%/bit | Offset: -125%
             */
            uint8_t actual_engine;

            /**
             * @brief Engine crankshaft speed.
             * @note Unit: RPM | Scaling: 0.125 RPM/bit | Offset: 0
             */
            uint16_t engine_speed;

            /**
             * @brief Source address of controlling device.
             * @note Unit: Address (0-255)
             */
            uint8_t source_address;

            /**
             * @brief Status of engine starter.
             * @note Unit: State (Bit-mapped)
             */
            uint8_t engine_starter_mode;

            /**
             * @brief Engine torque demand.
             * @note Unit: % | Scaling: 1%/bit | Offset: -125%
             */
            uint8_t engine_demand;
        };

        /**
         * @brief Electronic Engine Controller 2 (EEC2) - PGN 61445
         */
        struct ElectronicEngineController2 {
            static constexpr int BYTE_LENGTH = 8;
            static constexpr int ID = 61445;

            static ElectronicEngineController2 fromMessage(
                can_common::PGNMessage const& message);

            base::Time time;

            /**
             * @brief Operator selected gear.
             * @note Unit: Gear | Offset: -125 (0 = Neutral)
             */
            uint8_t selected_gear;

            /**
             * @brief Transmission gear ratio.
             * @note Unit: Ratio | Scaling: 0.001/bit | Offset: 0
             */
            uint16_t actual_gear_ratio;

            /**
             * @brief Currently engaged gear.
             * @note Unit: Gear | Offset: -125
             */
            uint8_t current_gear;

            /**
             * @brief Requested transmission range.
             * @note Unit: ASCII/Range Code
             */
            uint16_t transmission_requested_range;

            /**
             * @brief Current transmission range.
             * @note Unit: ASCII/Range Code
             */
            uint16_t transmission_current_range;
        };

        /**
         * @brief Fuel Economy (LFE) - PGN 65266
         */
        struct FuelEconomy {
            static constexpr int BYTE_LENGTH = 8;
            static constexpr int ID = 65266;

            static FuelEconomy fromMessage(can_common::PGNMessage const& message);

            base::Time time;

            /**
             * @brief Engine fuel consumption rate.
             * @note Unit: L/h | Scaling: 0.05 L/h per bit | Offset: 0
             */
            uint16_t fuel_rate;

            /**
             * @brief Instantaneous economy at current speed.
             * @note Unit: km/L | Scaling: 1/512 km/L per bit | Offset: 0
             */
            uint16_t instantaneous_fuel_economy;

            /**
             * @brief Average economy over trip/interval.
             * @note Unit: km/L | Scaling: 1/512 km/L per bit | Offset: 0
             */
            uint16_t average_fuel_economy;

            /**
             * @brief Primary throttle position.
             * @note Unit: % | Scaling: 0.4%/bit | Offset: 0
             */
            uint8_t throttle_position_1;

            /**
             * @brief Secondary throttle position.
             * @note Unit: % | Scaling: 0.4%/bit | Offset: 0
             */
            uint8_t throttle_position_2;
        };

        /**
         * @brief Engine Fluid Level and Pressure 1 (EFL/P1) - PGN 65263
         */
        struct EngineFluidLevelAndPressure1 {
            static constexpr int BYTE_LENGTH = 8;
            static constexpr int ID = 65263;

            static EngineFluidLevelAndPressure1 fromMessage(
                can_common::PGNMessage const& message);

            base::Time time;

            /**
             * @brief Pressure at fuel delivery pump.
             * @note Unit: kPa | Scaling: 4 kPa/bit | Offset: 0
             */
            uint8_t fuel_delivery_pressure;

            /**
             * @brief Crankcase blow-by pressure.
             * @note Unit: kPa | Scaling: 0.05 kPa/bit | Offset: 0
             */
            uint8_t extended_crankcase_blow_by_pressure;

            /**
             * @brief Engine oil volume.
             * @note Unit: % | Scaling: 0.4%/bit | Offset: 0
             */
            uint8_t engine_oil_level;

            /**
             * @brief Engine oil pressure gauge.
             * @note Unit: kPa | Scaling: 4 kPa/bit | Offset: 0
             */
            uint8_t engine_oil_pressure;

            /**
             * @brief Absolute crankcase pressure.
             * @note Unit: kPa | Scaling: 0.0078125 kPa/bit | Offset: -128 kPa
             */
            uint16_t crankcase_pressure;

            /**
             * @brief Engine coolant system pressure.
             * @note Unit: kPa | Scaling: 2 kPa/bit | Offset: 0
             */
            uint8_t coolant_pressure;

            /**
             * @brief Engine coolant volume.
             * @note Unit: % | Scaling: 0.4%/bit | Offset: 0
             */
            uint8_t coolant_level;
        };

        /**
         * @brief Engine Fluid Level and Pressure 2 (EFL/P2) - PGN 65243
         */
        struct EngineFluidLevelAndPressure2 {
            static constexpr int BYTE_LENGTH = 8;
            static constexpr int ID = 65243;

            static EngineFluidLevelAndPressure2 fromMessage(
                can_common::PGNMessage const& message);

            base::Time time;

            /**
             * @brief Control pressure for fuel injection.
             * @note Unit: kPa | Scaling: 16 kPa/bit | Offset: 0
             */
            uint16_t injection_control_pressure;

            /**
             * @brief Pressure in fuel metering rail 1.
             * @note Unit: kPa | Scaling: 16 kPa/bit | Offset: 0
             */
            uint16_t injector_metering_rail_1_pressure;

            /**
             * @brief Pressure in fuel timing rail 1.
             * @note Unit: kPa | Scaling: 16 kPa/bit | Offset: 0
             */
            uint16_t injector_timing_rail_1_pressure;

            /**
             * @brief Pressure in fuel metering rail 2.
             * @note Unit: kPa | Scaling: 16 kPa/bit | Offset: 0
             */
            uint16_t injector_metering_rail_2_pressure;
        };

        /**
         * @brief Inlet Conditions (IC1) - PGN 65270
         */
        struct InletConditions {
            static constexpr int BYTE_LENGTH = 8;
            static constexpr int ID = 65270;

            static InletConditions fromMessage(can_common::PGNMessage const& message);

            base::Time time;

            /**
             * @brief Inlet pressure to particulate trap.
             * @note Unit: kPa | Scaling: 0.5 kPa/bit | Offset: 0
             */
            uint8_t particulate_trap_inlet_pressure;

            /**
             * @brief Intake manifold boost pressure.
             * @note Unit: kPa | Scaling: 2 kPa/bit | Offset: 0
             */
            uint8_t boost_pressure;

            /**
             * @brief Intake manifold air temperature.
             * @note Unit: °C | Scaling: 1 °C/bit | Offset: -40 °C
             */
            uint8_t intake_manifold_1_temperature;

            /**
             * @brief Engine inlet air pressure (barometric).
             * @note Unit: kPa | Scaling: 2 kPa/bit | Offset: 0
             */
            uint8_t air_inlet_pressure;

            /**
             * @brief Delta pressure across air filter.
             * @note Unit: kPa | Scaling: 0.05 kPa/bit | Offset: 0
             */
            uint8_t air_filter_1_differential_pressure;

            /**
             * @brief Temperature of exhaust gas.
             * @note Unit: °C | Scaling: 0.03125 °C/bit | Offset: -273 °C
             */
            uint16_t exhaust_gas_temperature;

            /**
             * @brief Delta pressure across coolant filter.
             * @note Unit: kPa | Scaling: 0.5 kPa/bit | Offset: 0
             */
            uint8_t coolant_filter_differential_pressure;
        };

        /**
         * @brief Engine Hours and Revolutions (HOURS) - PGN 65253
         */
        struct EngineHoursAndRevolutions {
            static constexpr int BYTE_LENGTH = 8;
            static constexpr int ID = 65253;

            static EngineHoursAndRevolutions fromMessage(
                can_common::PGNMessage const& message);

            base::Time time;

            /**
             * @brief Cumulative engine operation time.
             * @note Unit: hr | Scaling: 0.05 hr/bit | Offset: 0
             */
            uint32_t total_engine_hours;

            /**
             * @brief Cumulative engine crankshaft rotations.
             * @note Unit: rev | Scaling: 1000 rev/bit | Offset: 0
             */
            uint32_t total_engine_revolutions;
        };

        /**
         * @brief Vehicle Electrical Power 1 (VEP1) - PGN 65271
         */
        struct VehicleElectricalPower1 {
            static constexpr int BYTE_LENGTH = 8;
            static constexpr int ID = 65271;

            static VehicleElectricalPower1 fromMessage(
                can_common::PGNMessage const& message);

            base::Time time;

            /**
             * @brief Current flow at battery.
             * @note Unit: A | Scaling: 1 A/bit | Offset: -125 A
             */
            uint8_t net_battery_current;

            /**
             * @brief Current from alternator.
             * @note Unit: A | Scaling: 1 A/bit | Offset: 0
             */
            uint8_t alternator_current;

            /**
             * @brief Potential at alternator.
             * @note Unit: V | Scaling: 0.05 V/bit | Offset: 0
             */
            uint16_t alternator_potential;

            /**
             * @brief General electrical potential.
             * @note Unit: V | Scaling: 0.05 V/bit | Offset: 0
             */
            uint16_t electrical_potential;

            /**
             * @brief Potential measured at battery.
             * @note Unit: V | Scaling: 0.05 V/bit | Offset: 0
             */
            uint16_t battery_potential;
        };

        /**
         * @brief Engine Temperature 1 (ET1) - PGN 65262
         */
        struct EngineTemperature1 {
            static constexpr int BYTE_LENGTH = 8;
            static constexpr int ID = 65262;

            static EngineTemperature1 fromMessage(can_common::PGNMessage const& message);

            base::Time time;

            /**
             * @brief Engine coolant liquid temperature.
             * @note Unit: °C | Scaling: 1 °C/bit | Offset: -40 °C
             */
            uint8_t engine_coolant_temperature;

            /**
             * @brief Fuel temperature at inlet.
             * @note Unit: °C | Scaling: 1 °C/bit | Offset: -40 °C
             */
            uint8_t fuel_temperature;

            /**
             * @brief Engine oil temperature.
             * @note Unit: °C | Scaling: 0.03125 °C/bit | Offset: -273 °C
             */
            uint16_t engine_oil_temperature;

            /**
             * @brief Turbocharger oil temperature.
             * @note Unit: °C | Scaling: 0.03125 °C/bit | Offset: -273 °C
             */
            uint16_t turbo_oil_temperature;

            /**
             * @brief Air temperature after intercooler.
             * @note Unit: °C | Scaling: 1 °C/bit | Offset: -40 °C
             */
            uint8_t engine_intercooler_temperature;

            /**
             * @brief Intercooler thermostat opening.
             * @note Unit: % | Scaling: 0.4%/bit | Offset: 0
             */
            uint8_t engine_intercooler_thermostat_opening;
        };
    }
}

#endif