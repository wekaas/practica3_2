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

uint16_t ccsds_pus_tm_build_packet_id(uint16_t apid) {

	uint16_t tm_packet_id;
	tm_packet_id = (1 << 11) | (apid & 0x07FF);
	return tm_packet_id;

}

// TODO: Define function ccsds_pus_tm_build_packet_seq_ctrl
uint16_t ccsds_pus_tm_build_packet_seq_ctrl(uint16_t  sequence_count, uint8_t sequence_flags){

	uint16_t tm_packet_seq_ctrl;
	tm_packet_seq_ctrl = (sequence_flags << 14) | (sequence_count & 0x3FFF);
	return(tm_packet_seq_ctrl);

}
// TODO: Define function ccsds_pus_tm_build_df_header
uint32_t ccsds_pus_tm_build_df_header(uint8_t service_type, uint8_t service_subtype, uint8_t destination_ID){

	uint32_t tm_df_header;
	tm_df_header = (1 << 28) | (service_type << 16) | (service_subtype << 8) | destination_ID;
	return(tm_df_header);
}

/**
 * \brief Serializes and stores into a vector the main fields of a TM packet.
 *
 * \param tm_bytes vector that will store the generated serialized telemetry
 * \param tm_packet_id the Packet ID field of the generated telemetry
 * \param tm_packet_seq_ctrl the Packet Sequence Control field of the
 *                           generated telemetry
 * \param tm_packet_length the Packet Length of the generated telemetry
 * \param tm_df_header the Data Field Header of the generated telemetry
 */
void ccsds_pus_tm_set_fields(uint8_t tm_bytes[],
                             uint16_t tm_packet_id,
                             uint16_t tm_packet_seq_ctrl,
                             uint16_t tm_packet_length,
                             uint32_t tm_df_header) {

    serialize_uint16(tm_packet_id, &tm_bytes[0]);

    // TODO: Finish the implementation of the function

    serialize_uint16(tm_packet_seq_ctrl, &tm_bytes[2]);

    serialize_uint16(tm_packet_length, &tm_bytes[4]);

    serialize_uint32(tm_df_header, &tm_bytes[6]);
}





