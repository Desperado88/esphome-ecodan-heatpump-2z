#ifndef ECODAN_HEATPUMP_INCLUDE_COMMANDS_H
#define ECODAN_HEATPUMP_INCLUDE_COMMANDS_H

#define PACKET_BUFFER_SIZE 23

#include <cstdint>

namespace ecodan {

using std::uint8_t;

enum commandVarTypeEnum {
  CommandVarType_TEMPERATURE,
  CommandVarType_AC_MODE_SETTING,
  CommandVarType_ON_OFF,
  CommandVarType_HOT_WATER_MODE,
};

namespace commands {

#define SINGLE_ARG(...) __VA_ARGS__
#define DEFINE_COMMAND(d_name, d_varIndex, d_varType, d_packetMask) \
  struct command_##d_name { \
    static constexpr uint8_t varIndex = d_varIndex; \
    static constexpr commandVarTypeEnum varType = d_varType; \
    static constexpr uint8_t packetMask[PACKET_BUFFER_SIZE] = d_packetMask; \
  }

DEFINE_COMMAND(power_state, 8, CommandVarType_ON_OFF, SINGLE_ARG({0xfc, 0x41, 0x02, 0x7a, 0x10, 0x32, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}));
// Didn't work when testing
DEFINE_COMMAND(holiday_mode, 10, CommandVarType_ON_OFF, SINGLE_ARG({0xfc, 0x41, 0x02, 0x7a, 0x10, 0x34, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}));
DEFINE_COMMAND(force_dhw, 8, CommandVarType_ON_OFF, SINGLE_ARG({0xfc, 0x41, 0x02, 0x7a, 0x10, 0x34, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}));
DEFINE_COMMAND(mode_select, 11, CommandVarType_AC_MODE_SETTING, SINGLE_ARG({0xfc, 0x41, 0x02, 0x7a, 0x10, 0x32, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}));
DEFINE_COMMAND(hot_water_mode, 10, CommandVarType_HOT_WATER_MODE, SINGLE_ARG({0xfc, 0x41, 0x02, 0x7a, 0x10, 0x32, 0x04, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}));
DEFINE_COMMAND(hot_water_setpoint, 13, CommandVarType_TEMPERATURE, SINGLE_ARG({0xfc, 0x41, 0x02, 0x7a, 0x10, 0x32, 0x20, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}));
DEFINE_COMMAND(zone1_room_temp_setpoint, 15, CommandVarType_TEMPERATURE, SINGLE_ARG({0xfc, 0x41, 0x02, 0x7a, 0x10, 0x32, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}));
DEFINE_COMMAND(zone1_flow_temp_setpoint, 15, CommandVarType_TEMPERATURE, SINGLE_ARG({0xfc, 0x41, 0x02, 0x7a, 0x10, 0x32, 0x80, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}));
DEFINE_COMMAND(zone1_room_temp, 7, CommandVarType_TEMPERATURE, SINGLE_ARG({0xfc, 0x41, 0x02, 0x7a, 0x10, 0x07, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00}));

} // namespace commands
} // namespace ecodan

#endif // ECODAN_HEATPUMP_INCLUDE_COMMANDS_H
