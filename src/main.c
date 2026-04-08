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

	uint8_t tc = 0;
	uint16_t tm_count = 0;

	while (tc < ntcs) {

		uint8_t tc_bytes[256];
		uint16_t tc_packet_id;
		uint16_t tc_packet_seq_ctrl;
		uint16_t tc_packet_len;
		uint32_t tc_df_header;
		uint16_t tc_packet_err_ctrl;

		uint8_t byte_to_write;

		uint16_t tm_packet_id = 0;
		uint16_t tm_packet_seq_ctrl;
		uint16_t tm_packet_len;
		uint32_t tm_df_header = 0;

		read(tc_fd, &read_byte, 1);
		tc_bytes[0] = read_byte;

		tc_packet_id = read_byte;
		tc_packet_id = tc_packet_id << 8;

		read(tc_fd, &read_byte, 1);
		tc_bytes[1] = read_byte;

		tc_packet_id = tc_packet_id | read_byte;

		printf("Packet ID: 0x%X\n", tc_packet_id);

		// Packet seq ctrl

		read(tc_fd, &read_byte, 1);
		tc_bytes[2] = read_byte;

		tc_packet_seq_ctrl = read_byte;
		tc_packet_seq_ctrl = tc_packet_seq_ctrl << 8;

		read(tc_fd, &read_byte, 1);
		tc_bytes[3] = read_byte;

		tc_packet_seq_ctrl = tc_packet_seq_ctrl | read_byte;

		printf("Packet Sequence Control: 0x%X\n", tc_packet_seq_ctrl);

		//Packet lengt

		read(tc_fd, &read_byte, 1);
		tc_bytes[4] = read_byte;

		tc_packet_len = read_byte;
		tc_packet_len = tc_packet_len << 8;

		read(tc_fd, &read_byte, 1);
		tc_bytes[5] = read_byte;

		tc_packet_len = tc_packet_len | read_byte;

		printf("Packet Length: 0x%X\n", tc_packet_len);

		//Data Field Header

		read(tc_fd, &read_byte, 1);
		tc_bytes[6] = read_byte;

		tc_df_header = read_byte;
		tc_df_header = tc_df_header << 24;

		read(tc_fd, &read_byte, 1);
		tc_bytes[7] = read_byte;

		tc_df_header = tc_df_header | (read_byte << 16);

		read(tc_fd, &read_byte, 1);
		tc_bytes[8] = read_byte;

		tc_df_header = tc_df_header | (read_byte << 8);

		read(tc_fd, &read_byte, 1);
		tc_bytes[9] = read_byte;

		tc_df_header = tc_df_header | read_byte;

		printf("Data Field Header: 0x%X\n", tc_df_header);

		//Calculo el telecomando:

		uint16_t i = 0;

		while (i < tc_packet_len - 5) {

			read(tc_fd, &read_byte, 1);

			tc_bytes[10 + i] = read_byte;

			i = i + 1;

		}

		//Packet error control

		read(tc_fd, &read_byte, 1);
		tc_packet_err_ctrl = read_byte;
		tc_packet_err_ctrl = tc_packet_err_ctrl << 8;

		read(tc_fd, &read_byte, 1);
		tc_packet_err_ctrl = tc_packet_err_ctrl | read_byte;

		printf("Packet Error Control: 0x%X\n", tc_packet_err_ctrl);

		uint16_t crc_value = 0xFFFF;

		uint16_t nbytes = tc_packet_len + 5;

		for (uint16_t i = 0; i < nbytes; i++) {

			crc_value = crc_value ^ (tc_bytes[i] << 8);

			for (uint8_t j = 0; j < 8; j++) {

				if ((crc_value & 0x8000) != 0) {
					crc_value = (crc_value << 1) ^ 0x1021;
				} else {
					crc_value = crc_value << 1;
				}
			}
		}

		//Imprimo

		ccsds_pus_tmtc_print_packet_header_fields(tc_packet_id);

		ccsds_pus_tmtc_print_packet_seq_ctrl_fields(tc_packet_seq_ctrl);

		ccsds_pus_tc_print_df_header_fields(tc_df_header);


		// Comparo

		if (tc_packet_err_ctrl == crc_value) {

			printf("Expected CRC value 0x%X, Calculated CRC value 0x%X: OK\n",
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

			tm_df_header = tm_df_header | (1 << 28) | (1 << 16) | (1 << 8) | 0x78;

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

			printf("Expected CRC value 0x%X, Calculated CRC value 0x%X: FAIL\n", tc_packet_err_ctrl, crc_value);

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

		    tm_df_header = tm_df_header | (1 << 28) | (1 << 16) | (2 << 8) | 0x78;

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

		}

		tc++;
		tm_count++;
	}

	close(tc_fd);
	close(tm_fd);

	return 0;

}
