#ifndef INCLUDE_CCSDS_PUS_FORMAT_H_
#define INCLUDE_CCSDS_PUS_FORMAT_H_

#include "basic_types.h"

/**
 * \brief Get APID from a telecommand's Packet ID.
 *
 * \param tc_packet_id the telecommand's Packet ID
 *
 * \return the telecommand's APID
 */
#define ccsds_pus_tc_get_APID(tc_packet_id) ((tc_packet_id) & 0x07FF)

/**
 * \brief Get Sequence Count from a telecommand's Packet Sequence Control.
 *
 * \param tc_packet_seq_ctrl the telecommand's Packet Sequence Control
 *
 * \return the telecommand's Sequence Flags
 */
// TODO: Define macro ccsds_pus_tc_get_seq_flags
#define ccsds_pus_tc_get_seq_flags(tc_packet_seq_ctrl) ((tc_packet_seq_ctrl & 0xC000) >> 14)

/**
 * \brief Get Sequence Count from a telecommand's Packet Sequence Control.
 *
 * \param tc_packet_seq_ctrl the telecommand's Packet Sequence Control
 *
 * \return the telecommand's Sequence Count
 */
// TODO: Define macro ccsds_pus_tc_get_seq_count
#define ccsds_pus_tc_get_seq_count(tc_packet_seq_ctrl) (tc_packet_seq_ctrl & 0x3FFF)

/**
 * \brief Get Ack from a telecommand's Data Field Header.
 *
 * \param tc_df_header the telecommand's Data Field Header
 *
 * \return the telecommand's Ack
 */
// TODO: Define macro ccsds_pus_tc_get_ack
#define ccsds_pus_tc_get_ack(tc_df_header) ((tc_df_header & 0x0F000000) >> 24)

/**
 * \brief Get Service Type from a telecommand's Data Field Header.
 *
 * \param tc_df_header the telecommand's Data Field Header
 *
 * \return the telecommand's Service Type
 */
// TODO: Define macro ccsds_pus_tc_get_type
#define ccsds_pus_tc_get_type(tc_df_header) ((tc_df_header & 0x00FF0000) >> 16)

/**
 * \brief Get Service Subtype from a telecommand's Data Field Header.
 *
 * \param tc_df_header the telecommand's Data Field Header
 *
 * \return the telecommand's Service Subtype
 */
// TODO: Define macro ccsds_pus_tc_get_subtype
#define ccsds_pus_tc_get_subtype(tc_df_header) ((tc_df_header & 0x0000FF00) >> 8)

/**
 * \brief Get Source ID from a telecommand's Data Field Header.
 *
 * \param df_header the telecommand's Data Field Header
 *
 * \return the telecommand's Source ID
 */
// TODO: Define macro ccsds_pus_tc_get_sourceID
#define ccsds_pus_tc_get_sourceID(tc_df_header) (tc_df_header & 0x000000FF)

/**
 * \brief Deserializes the fields of a telecommand stored in a vector
 *
 * \param tc_bytes vector that stores the bytes of the telecommand
 * \param p_tc_packet_id pointer to the variable that shall store the Packet ID
 * \param p_tc_packet_seq_ctrl pointer to the variable that shall store the
 *                          Packet Sequence Control field
 * \param p_tc_packet_len pointer to the variable that shall store the Packet
 *                     Length field
 * \param p_tc_df_header pointer to the variable that shall store the Data Field
 *                    Header
 * \param p_tc_packet_err_ctrl pointer to the variable that shall store the
 *                          Packet Error Control
 */
// TODO: declare function ccsds_pus_tc_get_fields
void ccsds_pus_tc_get_fields(uint8_t tc_bytes[],
                             uint16_t * p_tc_packet_id,
                             uint16_t * p_packet_seq_ctrl,
                             uint16_t * p_tc_packet_len,
                             uint32_t * p_tc_df_header,
                             uint16_t * p_tc_packet_err_ctrl);

/**
 * \brief Builds the Packet ID of a telmetry.
 *
 * \param apid the value of the APID subfield
 *
 * \return the Packet ID field
 */
#define ccsds_pus_tm_build_packet_id(apid) ((1 << 11) | ((apid) & 0x07FF))

/**
 * \brief Builds the Packet Sequence Control of a telmetry.
 *
 * \param flags the value of the Sequence Flags subfield
 * \param count the value of the Sequence Count subfield
 *
 * \return the Packet Sequence Control field
 */
// TODO: Define macro ccsds_pus_tm_build_packet_seq_ctrl
#define ccsds_pus_tm_build_packet_seq_ctrl(sequence_flags, sequence_count) ((sequence_flags << 14) | (sequence_count & 0x3FFF))

/**
 * \brief Builds the Data Field Header of a telmetry.
 *
 * \param type the value of the Type subfield
 * \param subtype the value of the Subtype subfield
 * \param dest the value of the Destination ID subfield
 *
 * \return the Data Field Header
 */
// TODO: Define macro ccsds_pus_tm_build_df_header
#define ccsds_pus_tm_build_df_header(service_type, service_subtype, destination_ID) ((1 << 28) | (service_type << 16) | (service_subtype << 8) | destination_ID)

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
                             uint32_t tm_df_header);

#endif /* INCLUDE_CCSDS_PUS_FORMAT_H_ */
