#ifndef INCLUDE_CCSDS_PUS_STDIO_H_
#define INCLUDE_CCSDS_PUS_STDIO_H_

#include "basic_types.h"

/**
 * \brief Print packet header fields
 *
 * \param tc_packet_id telecommand packet_id
 */
void ccsds_pus_tmtc_print_packet_header_fields(uint16_t tc_packet_id);

/**
 * \brief Print packet sequence control fields
 *
 * \param tc_packet_seq_ctrl telecommand packet sequence control
 */
// TODO: Declare function ccsds_pus_tmtc_print_packet_seq_ctrl_fields
void ccsds_pus_tmtc_print_packet_seq_ctrl_fields(uint16_t tc_packet_seq_ctrl);

/**
 * \brief Print data field header
 *
 * \param tc_df_header telecommand data field header
 */
// TODO: Declare function ccsds_pus_tc_print_df_header_fields
void ccsds_pus_tc_print_df_header_fields(uint32_t tc_df_header);

/**
 * \brief Reads a telecommand from a file
 *
 * \param fd descriptor of the file from which the TC shall be read
 * \param tc_bytes vector that shall store the bytes of the read TC
 *
 * \return the number of bytes that are part of the telecommand
 */
// TODO: Declare function ccsds_pus_tc_read
uint16_t ccsds_pus_tc_read(int fd, uint8_t tc_bytes[]);

#endif /* INCLUDE_CCSDS_PUS_STDIO_H_ */
