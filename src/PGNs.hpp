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
         * @brief Engine Torque Mode (SPN 899)
         */
        enum EngineTorqueMode : uint8_t {
            LOW_IDLE_GOVERNOR = 0b0000,
            ACCELERATOR_PEDAL = 0b0001,
            CRUISE_CONTROL = 0b0010,
            PTO_GOVERNOR = 0b0011,
            ROAD_SPEED_GOVERNOR = 0b0100,
            ASR_CONTROL = 0b0101,
            TRANSMISSION_CONTROL = 0b0110,
            ABS_CONTROL = 0b0111,
            TORQUE_LIMITING = 0b1000,
            HIGH_SPEED_GOVERNOR = 0b1001,
            BRAKING_SYSTEM = 0b1010,
            REMOTE_ACCELERATOR = 0b1011,
            SERVICE_TOOL = 0b1100,
            OTHER = 0b1101,
            RESERVED = 0b1110,
            ENGINE_TORQUE_MODE_NOT_AVAILABLE = 0b1111
        };

        /**
         * @brief Engine Starter Mode (SPN 1675)
         */
        enum EngineStarterMode : uint8_t {
            START_NOT_REQUESTED = 0b0000,
            STARTER_ACTIVE_GEAR_NOT_ENGAGED = 0b0001,
            STARTER_ACTIVE_GEAR_ENGAGED = 0b0010,
            START_FINISHED = 0b0011,
            STARTER_INHIBITED_ENGINE_ALREADY_RUNNING = 0b0100,
            STARTER_INHIBITED_ENGINE_NOT_READY = 0b0101,
            STARTER_INHIBITED_DRIVELINE_ENGAGED = 0b0110,
            STARTER_INHIBITED_ACTIVE_IMMOBILIZER = 0b0111,
            STARTER_INHIBITED_STARTER_OVER_TEMP = 0b1000,
            RESERVED_9 = 0b1001,
            RESERVED_10 = 0b1010,
            RESERVED_11 = 0b1011,
            STARTER_INHIBITED_REASON_UNKNOWN = 0b1100,
            ERROR_LEGACY = 0b1101,
            ERROR = 0b1110,
            ENGINE_STARTER_MODE_NOT_AVAILABLE = 0b1111
        };

        /**
         * @brief Electronic Engine Controller 1 (EEC1) - PGN 61444
         */
        struct ElectronicEngineController1 {
            static constexpr int BYTE_LENGTH = 8;
            static constexpr int ID = 61444;

            static ElectronicEngineController1 fromMessage(
                can_common::PGNMessage const& message);

            base::Time time;

            /**
             * @brief State of engine torque control system.
             * @note Unit: Control State (Bit-mapped) | SPN: 899
             */
            EngineTorqueMode engine_torque_mode;

            /**
             * @brief Driver's requested torque.
             * @note Unit: % | Scaling: 1%/bit | Offset: -125% | SPN: 512
             */
            uint8_t drivers_demand_engine;

            /**
             * @brief Actual torque output.
             * @note Unit: % | Scaling: 1%/bit | Offset: -125% | SPN: 513
             */
            uint8_t actual_engine;

            /**
             * @brief Engine crankshaft speed.
             * @note Unit: RPM | Scaling: 0.125 RPM/bit | Offset: 0 | SPN: 190
             */
            uint16_t engine_speed;

            /**
             * @brief Source address of the device controlling the engine.
             * @note Unit: Address (0-255) | SPN: 1483
             */
            uint8_t source_address;

            /**
             * @brief Status of engine starter.
             * @note Unit: State (Bit-mapped) | SPN: 1675
             */
            EngineStarterMode engine_starter_mode;

            /**
             * @brief Engine torque demand.
             * @note Unit: % | Scaling: 1%/bit | Offset: -125% | SPN: 2432
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
             * @brief Selected gear during the current shift or the next pending shift
             * @note Unit: Gear | Offset: -125 (0 = Neutral) | SPN: 524 |
             * Negative values are reverse gears, positive values are forward gears, zero
             * is neutral. 251 (0xFB) is park
             */
            uint8_t selected_gear;

            /**
             * @brief Actual ratio of input shaft speed to output shaft speed.
             * @note Unit: Ratio | Scaling: 0.001/bit | Offset: 0 | SPN: 526
             */
            uint16_t actual_gear_ratio;

            /**
             * @brief Currently engaged gear or last gear engaged.
             * @note Unit: Gear | Offset: -125 | SPN: 523 |
             * Negative values are reverse gears, positive values are forward gears, zero
             * is neutral . 251 (0xFB) is park
             */
            uint8_t current_gear;

            /**
             * @brief Requested transmission range.
             * @note Unit: ASCII/Range Code | SPN: 162
             */
            uint16_t transmission_requested_range;

            /**
             * @brief Current transmission range.
             * @note Unit: ASCII/Range Code | SPN: 163
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
             * @brief Amount of fuel consumed by engine per unit of time.
             * @note Unit: L/h | Scaling: 0.05 L/h per bit | Offset: 0 | SPN: 183
             */
            uint16_t fuel_rate;

            /**
             * @brief Current fuel economy at current speed.
             * @note Unit: km/Kg | Scaling: 1/512 km/Kg per bit | Offset: 0 | SPN: 184
             */
            uint16_t instantaneous_fuel_economy;

            /**
             * @brief Average of instantaneous fuel economy over trip/interval.
             * @note Unit: km/Kg | Scaling: 1/512 km/Kg per bit | Offset: 0 | SPN: 185
             */
            uint16_t average_fuel_economy;

            /**
             * @brief Position of the valve used to regulate the supply of a fluid
             * @note Unit: % | Scaling: 0.4%/bit | Offset: 0 | SPN: 51
             */
            uint8_t throttle_position;
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
             * @brief Gage pressure of fuel as delivered from supply to the injection pump
             * @note Unit: kPa | Scaling: 4 kPa/bit | Offset: 0 | SPN: 94
             */
            uint8_t fuel_delivery_pressure;

            /**
             * @brief Differential crankcase blow-by pressure.
             * @note Unit: kPa | Scaling: 0.05 kPa/bit | Offset: 0 | SPN: 22
             */
            uint8_t extended_crankcase_blow_by_pressure;

            /**
             * @brief Ratio of sump oil volume to maximum required volume
             * @note Unit: % | Scaling: 0.4%/bit | Offset: 0 | SPN: 98
             */
            uint8_t engine_oil_level;

            /**
             * @brief Gage pressure of oil in engine lubrification system
             * @note Unit: kPa | Scaling: 4 kPa/bit | Offset: 0 | SPN: 100
             */
            uint8_t engine_oil_pressure;

            /**
             * @brief Cage pressure inside engine crankcase.
             * @note Unit: kPa | Scaling: 0.0078125 kPa/bit | Offset: -128 kPa | SPN: 101
             */
            uint16_t crankcase_pressure;

            /**
             * @brief Cage pressure of liquid found in engine colling system
             * @note Unit: kPa | Scaling: 2 kPa/bit | Offset: 0 | SPN: 109
             */
            uint8_t coolant_pressure;

            /**
             * @brief Ratio of actual coolant liquid volume to total cooling system volume
             * @note Unit: % | Scaling: 0.4%/bit | Offset: 0 | SPN: 111
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
             * @brief Gage pressure of the engine oil in fuel injection
             * @note Unit: kPa | Scaling: 1/256 MPa/bit | Offset: 0 | SPN: 164
             */
            uint16_t injection_control_pressure;

            /**
             * @brief Gage ressure in fuel metering rail 1.
             * @note Unit: kPa | Scaling: 1/256 MPa/bit | Offset: 0 | SPN: 157
             */
            uint16_t injector_metering_rail_1_pressure;

            /**
             * @brief Pressure in fuel timing rail 1.
             * @note Unit: kPa | Scaling: 1/256 MPa/bit | Offset: 0 | SPN: 156
             */
            uint16_t injector_timing_rail_1_pressure;

            /**
             * @brief Pressure in fuel metering rail 2.
             * @note Unit: kPa | Scaling: 1/256 MPa/bit | Offset: 0 | SPN: 1349
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
             * @brief Exhaust back pressure as a result of particle accumulation on filter
             * media placed in the exhaust stream
             * @note Unit: kPa | Scaling: 0.5 kPa/bit | Offset: 0 | SPN: 81
             */
            uint8_t particulate_trap_inlet_pressure;

            /**
             * @brief Air gage pressure measured downstream in the compressor discharge of
             * the turbocharger
             * @note Unit: kPa | Scaling: 2 kPa/bit | Offset: 0 | SPN: 102
             */
            uint8_t boost_pressure;

            /**
             * @brief Pre-combustion intake manifold air temperature.
             * @note Unit: °C | Scaling: 1 °C/bit | Offset: -40 °C | SPN: 105
             */
            uint8_t intake_manifold_1_temperature;

            /**
             * @brief Absolute air pressure at inlet to intake mainfold or air box
             * @note Unit: kPa | Scaling: 2 kPa/bit | Offset: 0 | SPN: 106
             */
            uint8_t air_inlet_pressure;

            /**
             * @brief Delta pressure across air filter.
             * @note Unit: kPa | Scaling: 0.05 kPa/bit | Offset: 0 | SPN: 107
             */
            uint8_t air_filter_1_differential_pressure;

            /**
             * @brief Temperature of exhaust gas.
             * @note Unit: °C | Scaling: 0.03125 °C/bit | Offset: -273 °C | SPN: 173
             */
            uint16_t exhaust_gas_temperature;

            /**
             * @brief Delta pressure across coolant filter.
             * @note Unit: kPa | Scaling: 0.5 kPa/bit | Offset: 0 | SPN: 112
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
             * @brief Accumulated time of operation of engine.
             * @note Unit: hr | Scaling: 0.05 hr/bit | Offset: 0 | SPN: 247
             */
            uint32_t total_engine_hours;

            /**
             * @brief Cumulative engine crankshaft revolutions during its operation.
             * @note Unit: rev | Scaling: 1000 rev/bit | Offset: 0 | SPN: 249
             */
            uint32_t total_engine_revolutions;
        };

        /**
         * @brief Vehicle Electrical Power (VEP) - PGN 65271
         */
        struct VehicleElectricalPower {
            static constexpr int BYTE_LENGTH = 8;
            static constexpr int ID = 65271;

            static VehicleElectricalPower fromMessage(
                can_common::PGNMessage const& message);

            base::Time time;

            /**
             * @brief Net flow of electrical into/out of the battery
             * @note Unit: A | Scaling: 1 A/bit | Offset: -125 A | SPN: 114
             */
            uint8_t net_battery_current;

            /**
             * @brief Current from alternator.
             * @note Unit: A | Scaling: 1 A/bit | Offset: 0 | SPN: 115
             */
            uint8_t alternator_current;

            /**
             * @brief Electical potential at alternator.
             * @note Unit: V | Scaling: 0.05 V/bit | Offset: 0 | SPN: 167
             */
            uint16_t alternator_potential;

            /**
             * @brief Electrical potential of the battery.
             * @note Unit: V | Scaling: 0.05 V/bit | Offset: 0 | SPN: 168
             */
            uint16_t electrical_potential;

            /**
             * @brief Electrical potential measured at the input of the ECU.
             * @note Unit: V | Scaling: 0.05 V/bit | Offset: 0 | SPN: 158
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
             * @note Unit: °C | Scaling: 1 °C/bit | Offset: -40 °C | SPN: 110
             */
            uint8_t engine_coolant_temperature;

            /**
             * @brief Temperature of fuel entering injectors.
             * @note Unit: °C | Scaling: 1 °C/bit | Offset: -40 °C | SPN: 174
             */
            uint8_t fuel_temperature;

            /**
             * @brief Temperature of the engine lubrificant.
             * @note Unit: °C | Scaling: 0.03125 °C/bit | Offset: -273 °C | SPN: 175
             */
            uint16_t engine_oil_temperature;

            /**
             * @brief Turbocharger lubrificant temperature.
             * @note Unit: °C | Scaling: 0.03125 °C/bit | Offset: -273 °C | SPN: 176
             */
            uint16_t turbo_oil_temperature;

            /**
             * @brief Air temperature after intercooler.
             * @note Unit: °C | Scaling: 1 °C/bit | Offset: -40 °C | SPN: 52
             */
            uint8_t engine_intercooler_temperature;

            /**
             * @brief Thermostat current position used to regulate the engine intercooler
             * temperature.
             * @note Unit: % | Scaling: 0.4%/bit | Offset: 0 | SPN: 1134
             */
            uint8_t engine_intercooler_thermostat_opening;
        };
    }
}

#endif