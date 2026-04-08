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

void ccsds_pus_tc_get_fields(uint8_t tc_bytes[],
                             uint16_t * p_tc_packet_id,
                             uint16_t * p_packet_seq_ctrl,
                             uint16_t * p_tc_packet_len,
                             uint32_t * p_tc_df_header,
                             uint16_t * p_tc_packet_err_ctrl) {

    // Deserialize Packet ID and store it at p_tc_packet_id
    *p_tc_packet_id = deserialize_uint16(&tc_bytes[0]);

    // TODO: Deserialize Packet Seq. Control and store it at p_tc_packet_seq_ctrl
    *p_packet_seq_ctrl = deserialize_uint16(&tc_bytes[2]);

    // TODO: Deserialize Packet Length and store it at p_tc_packet_len
    *p_tc_packet_len = deserialize_uint16(&tc_bytes[4]);

    // TODO: Deserialize Data Field Header and store it at p_tc_df_header
    *p_tc_df_header = deserialize_uint32(&tc_bytes[6]);

    // Hay que saber cuántos bytes (pista: depende de packet length

    // TODO: Deserialize Packet Error Control and store it at p_tc_packet_err_ctrl
	*p_tc_packet_err_ctrl = deserialize_uint16(&tc_bytes[*p_tc_packet_len + 5]);

}

