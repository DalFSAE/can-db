#include "can0_powertrain.h"

switch (rx_header.StdId)
{
case CAN0_POWERTRAIN_M173_MODULATION_AND_FLUX_INFO_FRAME_ID:
    can0_powertrain_m173_modulation_and_flux_info_unpack(&m173_msg, rx_data, rx_header.DLC);
    break;
case CAN0_POWERTRAIN_M172_TORQUE_AND_TIMER_INFO_FRAME_ID:
    can0_powertrain_m172_torque_and_timer_info_unpack(&m172_msg, rx_data, rx_header.DLC);
    break;
case CAN0_POWERTRAIN_M194_READ_WRITE_PARAM_RESPONSE_FRAME_ID:
    can0_powertrain_m194_read_write_param_response_unpack(&m194_msg, rx_data, rx_header.DLC);
    break;
case CAN0_POWERTRAIN_M171_FAULT_CODES_FRAME_ID:
    can0_powertrain_m171_fault_codes_unpack(&m171_msg, rx_data, rx_header.DLC);
    break;
case CAN0_POWERTRAIN_M170_INTERNAL_STATES_FRAME_ID:
    can0_powertrain_m170_internal_states_unpack(&m170_msg, rx_data, rx_header.DLC);
    break;
case CAN0_POWERTRAIN_M169_INTERNAL_VOLTAGES_FRAME_ID:
    can0_powertrain_m169_internal_voltages_unpack(&m169_msg, rx_data, rx_header.DLC);
    break;
case CAN0_POWERTRAIN_M168_FLUX_ID_IQ_INFO_FRAME_ID:
    can0_powertrain_m168_flux_id_iq_info_unpack(&m168_msg, rx_data, rx_header.DLC);
    break;
case CAN0_POWERTRAIN_M167_VOLTAGE_INFO_FRAME_ID:
    can0_powertrain_m167_voltage_info_unpack(&m167_msg, rx_data, rx_header.DLC);
    break;
case CAN0_POWERTRAIN_M166_CURRENT_INFO_FRAME_ID:
    can0_powertrain_m166_current_info_unpack(&m166_msg, rx_data, rx_header.DLC);
    break;
case CAN0_POWERTRAIN_M165_MOTOR_POSITION_INFO_FRAME_ID:
    can0_powertrain_m165_motor_position_info_unpack(&m165_msg, rx_data, rx_header.DLC);
    break;
case CAN0_POWERTRAIN_M164_DIGITAL_INPUT_STATUS_FRAME_ID:
    can0_powertrain_m164_digital_input_status_unpack(&m164_msg, rx_data, rx_header.DLC);
    break;
case CAN0_POWERTRAIN_M163_ANALOG_INPUT_VOLTAGES_FRAME_ID:
    can0_powertrain_m163_analog_input_voltages_unpack(&m163_msg, rx_data, rx_header.DLC);
    break;
case CAN0_POWERTRAIN_M162_TEMPERATURE_SET_3_FRAME_ID:
    can0_powertrain_m162_temperature_set_3_unpack(&m162_msg, rx_data, rx_header.DLC);
    break;
case CAN0_POWERTRAIN_M161_TEMPERATURE_SET_2_FRAME_ID:
    can0_powertrain_m161_temperature_set_2_unpack(&m161_msg, rx_data, rx_header.DLC);
    break;
case CAN0_POWERTRAIN_M160_TEMPERATURE_SET_1_FRAME_ID:
    can0_powertrain_m160_temperature_set_1_unpack(&m160_msg, rx_data, rx_header.DLC);
    break;
case CAN0_POWERTRAIN_M174_FIRMWARE_INFO_FRAME_ID:
    can0_powertrain_m174_firmware_info_unpack(&m174_msg, rx_data, rx_header.DLC);
    break;
case CAN0_POWERTRAIN_M187_U2_C_COMMAND_TXD_FRAME_ID:
    can0_powertrain_m187_u2_c_command_txd_unpack(&m187_msg, rx_data, rx_header.DLC);
    break;
case CAN0_POWERTRAIN_M176_FAST_INFO_FRAME_ID:
    can0_powertrain_m176_fast_info_unpack(&m176_msg, rx_data, rx_header.DLC);
    break;
case CAN0_POWERTRAIN_M175_DIAG_DATA_MESSAGE_FRAME_ID:
    can0_powertrain_m175_diag_data_message_unpack(&m175_msg, rx_data, rx_header.DLC);
    break;
default:
    break;
}
