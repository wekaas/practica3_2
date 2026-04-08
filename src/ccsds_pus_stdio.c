#include <stdio.h>

#include "basic_types.h"
#include "ccsds_pus_stdio.h"
#include "ccsds_pus_format.h"

void ccsds_pus_tmtc_print_packet_header_fields(uint16_t tc_packet_id) {

	printf("APID: 0x%X\n", ccsds_pus_tc_get_APID(tc_packet_id));

}

void ccsds_pus_tmtc_print_packet_seq_ctrl_fields(uint16_t tc_packet_seq_ctrl) {

	printf("Sequence Flags: 0x%X\n",
			ccsds_pus_tc_get_seq_flags(tc_packet_seq_ctrl));
	printf("Sequence Count: %d\n",
			ccsds_pus_tc_get_seq_count(tc_packet_seq_ctrl));

}

void ccsds_pus_tc_print_df_header_fields(uint32_t tc_df_header) {

	printf("Ack: 0x%X\n", ccsds_pus_tc_get_ack(tc_df_header));
	printf("Service Type: %d\n", ccsds_pus_tc_get_type(tc_df_header));
	printf("Service Subtype: %d\n", ccsds_pus_tc_get_subtype(tc_df_header));
	printf("Source ID: 0x%X\n", ccsds_pus_tc_get_sourceID(tc_df_header));

}

uint16_t ccsds_pus_tc_read(int fd, uint8_t tc_bytes[]) {

	uint16_t nbytes = 0;
	uint16_t tc_packet_len = 0;

	// Read the first initial six bytes of the TC (Packet Header)
	read(fd, &tc_bytes[0], 6);

	// Obtain Packet Length:

	// The Packet Length field is stored in bytes 4 and 5. To obtain the
	// actual value of the 16-bit field and store correctly into memory,
	// we have to deserialize it using function deserialize_uint16():
	tc_packet_len = deserialize_uint16(&tc_bytes[4]);

	uint16_t remaning_bytes = tc_packet_len + 1;

	// TODO: Read the remaining bytes and return the proper number of
	// bytes read. THE FUNCTION SHALL ALSO READ THE PACKET ERROR CONTROL
	// and store it into the vector.
	read(fd, &tc_bytes[6], remaning_bytes);

	nbytes = 6 + remaning_bytes;

	return nbytes;
}
