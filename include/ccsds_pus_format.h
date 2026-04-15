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
uint16_t ccsds_pus_tc_get_APID(uint16_t tc_packet_id);

/**
 * \brief Get Sequence Count from a telecommand's Packet Sequence Control.
 *
 * \param tc_packet_seq_ctrl the telecommand's Packet Sequence Control
 *
 * \return the telecommand's Sequence Flags
 */
// TODO: Declare function ccsds_pus_tc_get_seq_flags
uint8_t ccsds_pus_tc_get_seq_flags(uint16_t tc_packet_seq_ctrl);

/**
 * \brief Get Sequence Count from a telecommand's Packet Sequence Control.
 *
 * \param tc_packet_seq_ctrl the telecommand's Packet Sequence Control
 *
 * \return the telecommand's Sequence Count
 */
// TODO: Declare function ccsds_pus_tc_get_seq_count
uint16_t ccsds_pus_tc_get_seq_count(uint16_t tc_packet_seq_ctrl);

/**
 * \brief Get Ack from a telecommand's Data Field Header.
 *
 * \param tc_df_header the telecommand's Data Field Header
 *
 * \return the telecommand's Ack
 */
// TODO: Declare function ccsds_pus_tc_get_ack
uint8_t ccsds_pus_tc_get_ack(uint32_t tc_df_header);

/**
 * \brief Get Service Type from a telecommand's Data Field Header.
 *
 * \param tc_df_header the telecommand's Data Field Header
 *
 * \return the telecommand's Service Type
 */
// TODO: Declare function ccsds_pus_tc_get_type
uint8_t ccsds_pus_tc_get_type(uint32_t tc_df_header);

/**
 * \brief Get Service Subtype from a telecommand's Data Field Header.
 *
 * \param tc_df_header the telecommand's Data Field Header
 *
 * \return the telecommand's Service Subtype
 */
// TODO: Declare function ccsds_pus_tc_get_subtype
uint8_t ccsds_pus_tc_get_subtype(uint32_t tc_df_header);

/**
 * \brief Get Source ID from a telecommand's Data Field Header.
 *
 * \param tc_df_header the telecommand's Data Field Header
 *
 * \return the telecommand's Source ID
 */
// TODO: Declare function ccsds_pus_tc_get_sourceID
uint8_t ccsds_pus_tc_get_sourceID(uint32_t tc_df_header);

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
uint16_t ccsds_pus_tm_build_packet_id(uint16_t apid);

/**
 * \brief Builds the Packet Sequence Control of a telmetry.
 *
 * \param flags the value of the Sequence Flags subfield
 * \param count the value of the Sequence Count subfield
 *
 * \return the Packet Sequence Control field
 */
// TODO: Declare function ccsds_pus_tm_build_packet_seq_ctrl
uint16_t ccsds_pus_tm_build_packet_seq_ctrl(uint16_t sequence_flags, uint8_t sequence_count);

/**
 * \brief Builds the Data Field Header of a telmetry.
 *
 * \param type the value of the Type subfield
 * \param subtype the value of the Subtype subfield
 * \param dest the value of the Destination ID subfield
 *
 * \return the Data Field Header
 */
// TODO: Declare function ccsds_pus_tm_build_df_header
uint32_t ccsds_pus_tm_build_df_header(uint8_t service_type, uint8_t service_subtype, uint8_t destination_ID);

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
