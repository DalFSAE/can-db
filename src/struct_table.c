#include "can0_powertrain.h"
#include <stdint.h>

//ordered based on can0_powertrain.h declaration order, rx_table[] will be ordered smallest to largest
struct can0_powertrain_m173_modulation_and_flux_info_t m173_msg;
struct can0_powertrain_m172_torque_and_timer_info_t m172_msg;
struct can0_powertrain_m194_read_write_param_response_t m194_msg;
struct can0_powertrain_m171_fault_codes_t m171_msg;
struct can0_powertrain_m170_internal_states_t m170_msg;
struct can0_powertrain_m169_internal_voltages_t m169_msg;
struct can0_powertrain_m168_flux_id_iq_info_t m168_msg;
struct can0_powertrain_m167_voltage_info_t m167_msg;
struct can0_powertrain_m166_current_info_t m166_msg;
struct can0_powertrain_m165_motor_position_info_t m165_msg;
struct can0_powertrain_m164_digital_input_status_t m164_msg;
struct can0_powertrain_m163_analog_input_voltages_t m163_msg;
struct can0_powertrain_m162_temperature_set_3_t m162_msg;
struct can0_powertrain_m161_temperature_set_2_t m161_msg;
struct can0_powertrain_m160_temperature_set_1_t m160_msg;
struct can0_powertrain_m174_firmware_info_t m174_msg;
struct can0_powertrain_m187_u2_c_command_txd_t m187_msg;
struct can0_powertrain_m176_fast_info_t m176_msg;
struct can0_powertrain_m175_diag_data_message_t m175_msg;


typedef void (*CAN_Handler_t)(void* store_data, const uint8_t* data, size_t size);

typedef struct {
    uint32_t id;          // CAN ID
    void* storage;
    CAN_Handler_t handler;
    const char* name;     // optional

} CAN_Rx_Entry_t;

static const CAN_Rx_Entry_t rx_table[] = {
    //Using the already defined CAN id's from can0_powertrain.h
    //ordered properly by message ID, all are defined by the 'Mxxx' in their name, apart from M187, which has a value of 0x1d7u = 471
    //MUST STAY ORDERED FOR BINARY SEARCH BELOW
    {CAN0_POWERTRAIN_M160_TEMPERATURE_SET_1_FRAME_ID, &m160_msg, can0_powertrain_m160_temperature_set_1_unpack, "TEMP_SET_1"},
    {CAN0_POWERTRAIN_M161_TEMPERATURE_SET_2_FRAME_ID, &m161_msg, can0_powertrain_m161_temperature_set_2_unpack, "TEMP_SET_2"},
    {CAN0_POWERTRAIN_M162_TEMPERATURE_SET_3_FRAME_ID, &m162_msg, can0_powertrain_m162_temperature_set_3_unpack, "TEMP_SET_3"},
    {CAN0_POWERTRAIN_M163_ANALOG_INPUT_VOLTAGES_FRAME_ID, &m163_msg, can0_powertrain_m163_analog_input_voltages_unpack, "ANALOG_IN_VOLTAGE"},
    {CAN0_POWERTRAIN_M164_DIGITAL_INPUT_STATUS_FRAME_ID, &m164_msg, can0_powertrain_m164_digital_input_status_unpack, "DIGITAL_IN_STATUS"},
    {CAN0_POWERTRAIN_M165_MOTOR_POSITION_INFO_FRAME_ID, &m165_msg, can0_powertrain_m165_motor_position_info_unpack, "MOTOR_POSITION_INFO"},
    {CAN0_POWERTRAIN_M166_CURRENT_INFO_FRAME_ID, &m166_msg, can0_powertrain_m166_current_info_unpack, "CURRENT_INFO"},
    {CAN0_POWERTRAIN_M167_VOLTAGE_INFO_FRAME_ID, &m167_msg, can0_powertrain_m167_voltage_info_unpack, "VOLTAGE_INFO"},
    {CAN0_POWERTRAIN_M168_FLUX_ID_IQ_INFO_FRAME_ID, &m168_msg, can0_powertrain_m168_flux_id_iq_info_unpack, "FLUX_ID_IQ_INFO"},
    {CAN0_POWERTRAIN_M169_INTERNAL_VOLTAGES_FRAME_ID, &m169_msg, can0_powertrain_m169_internal_voltages_unpack, "INTERNAL_VOLTAGES"},
    {CAN0_POWERTRAIN_M170_INTERNAL_STATES_FRAME_ID, &m170_msg, can0_powertrain_m170_internal_states_unpack, "INTERNAL_STATES"},
    {CAN0_POWERTRAIN_M171_FAULT_CODES_FRAME_ID, &m171_msg, can0_powertrain_m171_fault_codes_unpack, "FAULT_CODES"},
    {CAN0_POWERTRAIN_M172_TORQUE_AND_TIMER_INFO_FRAME_ID, &m172_msg, can0_powertrain_m172_torque_and_timer_info_unpack, "TORQUE_TIMER_INFO" },
    {CAN0_POWERTRAIN_M173_MODULATION_AND_FLUX_INFO_FRAME_ID, &m173_msg, can0_powertrain_m173_modulation_and_flux_info_unpack, "MOD_FLUX_INFO"},
    {CAN0_POWERTRAIN_M174_FIRMWARE_INFO_FRAME_ID, &m174_msg,can0_powertrain_m174_firmware_info_unpack, "FIRMWARE_INFO"},
    {CAN0_POWERTRAIN_M175_DIAG_DATA_MESSAGE_FRAME_ID, &m175_msg, can0_powertrain_m175_diag_data_message_unpack, "DIAG_DATA_MESSAGE"},
    {CAN0_POWERTRAIN_M176_FAST_INFO_FRAME_ID,&m176_msg,can0_powertrain_m176_fast_info_unpack, "FAST_INFO"},
    {CAN0_POWERTRAIN_M194_READ_WRITE_PARAM_RESPONSE_FRAME_ID, &m194_msg, can0_powertrain_m194_read_write_param_response_unpack,   "INV_TEMP" },
    {CAN0_POWERTRAIN_M187_U2_C_COMMAND_TXD_FRAME_ID, &m187_msg, can0_powertrain_m187_u2_c_command_txd_unpack, "U@_C_COMMAND_TXD"}
};

void RX_Callback(uint16_t received_id, const uint8_t* data, size_t size) {
    size_t left = 0;
    size_t right = sizeof(rx_table) / sizeof(rx_table[0]);
    while (left < right)
    {
        size_t mid = left + (right - left) / 2;

        if (rx_table[mid].id == received_id) {
            rx_table[mid].handler(rx_table[mid].storage, data, size);
            return;
        }
        else if (received_id < rx_table[mid].id) {
            right = mid;
        }
        else {
            left = mid + 1;
        }
    }
    //Does this require some form of error handler incase an ID is not found?
}