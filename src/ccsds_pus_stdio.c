#include <stdio.h>

#include "basic_types.h"
#include "ccsds_pus_stdio.h"
#include "ccsds_pus_format.h"

void ccsds_pus_tmtc_print_packet_header_fields(uint16_t tc_packet_id) {

	printf("APID: 0x%X\n", ccsds_pus_tc_get_APID(tc_packet_id));

}

void ccsds_pus_tmtc_print_packet_seq_ctrl_fields(uint16_t tc_packet_seq_ctrl) {

	printf("Sequence Flags: 0x%X\n", ccsds_pus_tc_get_seq_flags(tc_packet_seq_ctrl));
	printf("Sequence Count: %d\n", ccsds_pus_tc_get_seq_count(tc_packet_seq_ctrl));

}

void ccsds_pus_tc_print_df_header_fields(uint32_t tc_df_header) {

	printf("Ack: 0x%X\n", ccsds_pus_tc_get_ack(tc_df_header));
	printf("Service Type: %d\n", ccsds_pus_tc_get_type(tc_df_header));
	printf("Service Subtype: %d\n", ccsds_pus_tc_get_subtype(tc_df_header));
	printf("Source ID: 0x%X\n", ccsds_pus_tc_get_sourceID(tc_df_header));

}
