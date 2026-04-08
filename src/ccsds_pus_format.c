#include "basic_types.h"
#include "ccsds_pus_format.h"

uint16_t ccsds_pus_tc_get_APID(uint16_t tc_packet_id) {

    return (tc_packet_id & 0x07FF);

}

uint8_t ccsds_pus_tc_get_seq_flags(uint16_t tc_packet_seq_ctrl) {

	return ((tc_packet_seq_ctrl & 0xC000) >> 14);

}

uint16_t ccsds_pus_tc_get_seq_count(uint16_t tc_packet_seq_ctrl) {

	return(tc_packet_seq_ctrl & 0x3FFF);

}

uint8_t ccsds_pus_tc_get_ack(uint32_t tc_df_header) {

	return((tc_df_header & 0x0F000000) >> 24);

}

uint8_t ccsds_pus_tc_get_type(uint32_t tc_df_header) {

	return((tc_df_header & 0x00FF0000) >> 16);

}

uint8_t ccsds_pus_tc_get_subtype(uint32_t tc_df_header) {

	return((tc_df_header & 0x0000FF00) >> 8);

}

uint8_t ccsds_pus_tc_get_sourceID(uint32_t tc_df_header) {

	return(tc_df_header & 0x000000FF);

}
