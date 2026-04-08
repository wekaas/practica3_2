#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

// Includes the declaration of the basic type aliases
#include "basic_types.h"
// Includes the field extraction function declarations
#include "ccsds_pus_format.h"

int main() {

	int tc_fd;
	int tm_fd;
	uint8_t read_byte;

	tc_fd = open("multiple-tcs.bin", O_RDONLY);
	tm_fd = open("multiple-tms.bin", O_WRONLY | O_CREAT | O_TRUNC, 0664);

	uint8_t ntcs;

	read(tc_fd, &read_byte, 1);
	ntcs = read_byte;

	uint16_t tm_count = 0;
	for (uint8_t tc = 0; tc < ntcs; tc = tc + 1) {

		uint16_t tc_packet_id;
		uint16_t tc_packet_seq_ctrl;
		uint16_t tc_packet_len;
		uint32_t tc_df_header;
		uint16_t tc_packet_err_ctrl;

		uint16_t crc_value;
		uint8_t nbytes = 0;

		uint8_t tc_bytes[256];

		uint8_t byte_to_write;
		uint16_t tm_packet_id = 0;
		uint16_t tm_packet_seq_ctrl;
		uint16_t tm_packet_len;
		uint32_t tm_df_header = 0;

		// Read telecommand from file
		nbytes = ccsds_pus_tc_read(tc_fd, tc_bytes);

		// Deserialize primary fields
		ccsds_pus_tc_get_fields(tc_bytes, &tc_packet_id, &tc_packet_seq_ctrl,
				&tc_packet_len, &tc_df_header, &tc_packet_err_ctrl);

		// Print the contents of all the fields
		ccsds_pus_tmtc_print_packet_header_fields(tc_packet_id);
		ccsds_pus_tmtc_print_packet_seq_ctrl_fields(tc_packet_seq_ctrl);
		ccsds_pus_tc_print_df_header_fields(tc_df_header);

		// Calculate CRC
		// We need to calculate the CRC with nbytes - 2, since the vector
		// ALSO STORES the Packet Error Control field
		crc_value = cal_crc_16(tc_bytes, nbytes - 2);

		// KEEP THE REST OF THE CODE AS IS
		//
		//
		if (tc_packet_err_ctrl == crc_value) {

		printf(
				"Expected CRC value 0x%X, Calculated CRC value 0x%X: OK\n",
				tc_packet_err_ctrl, crc_value);

		//Packet ID

		tm_packet_id = tm_packet_id | (1 << 11);
		tm_packet_id = tm_packet_id | (0x32C);

		byte_to_write = (tm_packet_id & 0xFF00) >> 8;
		write(tm_fd, &byte_to_write, 1);

		byte_to_write = (tm_packet_id & 0x00FF);
		write(tm_fd, &byte_to_write, 1);

		//Packet Sequence Control

		tm_packet_seq_ctrl = (3 << 14) | tm_count;

		byte_to_write = (tm_packet_seq_ctrl & 0xFF00) >> 8;
		write(tm_fd, &byte_to_write, 1);

		byte_to_write = (tm_packet_seq_ctrl & 0x00FF);
		write(tm_fd, &byte_to_write, 1);

		//Packet Length

		tm_packet_len = 0x000D;

		byte_to_write = (tm_packet_len & 0xFF00) >> 8;
		write(tm_fd, &byte_to_write, 1);

		byte_to_write = (tm_packet_len & 0x00FF);
		write(tm_fd, &byte_to_write, 1);

		//Data Field

		tm_df_header = tm_df_header | (1 << 28) | (1 << 16) | (1 << 8)
				| 0x78;

		byte_to_write = (tm_df_header & 0xFF000000) >> 24;
		write(tm_fd, &byte_to_write, 1);

		byte_to_write = (tm_df_header & 0x00FF0000) >> 16;
		write(tm_fd, &byte_to_write, 1);

		byte_to_write = (tm_df_header & 0x0000FF00) >> 8;
		write(tm_fd, &byte_to_write, 1);

		byte_to_write = (tm_df_header & 0x000000FF);
		write(tm_fd, &byte_to_write, 1);

		//Source Data

		byte_to_write = (tc_packet_id & 0xFF00) >> 8;
		write(tm_fd, &byte_to_write, 1);

		byte_to_write = (tc_packet_id & 0x00FF);
		write(tm_fd, &byte_to_write, 1);

		byte_to_write = (tc_packet_seq_ctrl & 0xFF00) >> 8;
		write(tm_fd, &byte_to_write, 1);

		byte_to_write = (tc_packet_seq_ctrl & 0x00FF);
		write(tm_fd, &byte_to_write, 1);

	} else {

		printf(
				"Expected CRC value 0x%X, Calculated CRC value 0x%X: FAIL\n",
				tc_packet_err_ctrl, crc_value);

		//Packet ID (igual)

		tm_packet_id = tm_packet_id | (1 << 11);
		tm_packet_id = tm_packet_id | (0x32C);

		byte_to_write = (tm_packet_id & 0xFF00) >> 8;
		write(tm_fd, &byte_to_write, 1);

		byte_to_write = (tm_packet_id & 0x00FF);
		write(tm_fd, &byte_to_write, 1);

		//Packet Sequence Control

		tm_packet_seq_ctrl = (3 << 14) | tm_count;

		byte_to_write = (tm_packet_seq_ctrl & 0xFF00) >> 8;
		write(tm_fd, &byte_to_write, 1);

		byte_to_write = (tm_packet_seq_ctrl & 0x00FF);
		write(tm_fd, &byte_to_write, 1);

		//Packet Length (igual)

		tm_packet_len = 0x000D;

		byte_to_write = (tm_packet_len & 0xFF00) >> 8;
		write(tm_fd, &byte_to_write, 1);

		byte_to_write = (tm_packet_len & 0x00FF);
		write(tm_fd, &byte_to_write, 1);

		//Data Field

		tm_df_header = tm_df_header | (1 << 28) | (1 << 16) | (2 << 8)
				| 0x78;

		byte_to_write = (tm_df_header & 0xFF000000) >> 24;
		write(tm_fd, &byte_to_write, 1);

		byte_to_write = (tm_df_header & 0x00FF0000) >> 16;
		write(tm_fd, &byte_to_write, 1);

		byte_to_write = (tm_df_header & 0x0000FF00) >> 8;
		write(tm_fd, &byte_to_write, 1);

		byte_to_write = (tm_df_header & 0x000000FF);
		write(tm_fd, &byte_to_write, 1);

		//Source Data

		byte_to_write = (tc_packet_id & 0xFF00) >> 8;
		write(tm_fd, &byte_to_write, 1);

		byte_to_write = (tc_packet_id & 0x00FF);
		write(tm_fd, &byte_to_write, 1);

		byte_to_write = (tc_packet_seq_ctrl & 0xFF00) >> 8;
		write(tm_fd, &byte_to_write, 1);

		byte_to_write = (tc_packet_seq_ctrl & 0x00FF);
		write(tm_fd, &byte_to_write, 1);

		uint16_t error = 2;

		byte_to_write = (error & 0xFF00) >> 8;
		write(tm_fd, &byte_to_write, 1);

		byte_to_write = (error & 0x00FF);
		write(tm_fd, &byte_to_write, 1);

		byte_to_write = (tc_packet_err_ctrl & 0xFF00) >> 8;
		write(tm_fd, &byte_to_write, 1);

		byte_to_write = (tc_packet_err_ctrl & 0x00FF);
		write(tm_fd, &byte_to_write, 1);

		byte_to_write = (crc_value & 0xFF00) >> 8;
		write(tm_fd, &byte_to_write, 1);

		byte_to_write = (crc_value & 0x00FF);
		write(tm_fd, &byte_to_write, 1);

		tm_count++;
		}
	}

		close(tc_fd);
		close(tm_fd);

		return 0;

	}
