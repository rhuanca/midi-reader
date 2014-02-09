#include "utils.h"

#include <stdio.h>

// 2^0 = 1
// 2^1 = 2
// 2^2 = 4
// 2^3 = 8
// 2^4 = 16
// 2^5 = 32
// 2^6 = 64
// 2^7 = 128
void print_byte_string(char byte) {
	int i;
	int c;
	c = 128;
	for (i = 0; i < 8; i++) {
		if (byte & c) {
			printf("1");
		} else {
			printf("0");
		}
		c = c / 2;
	}
	printf("\n");
}

char low_nibble(char byte) {
	return byte & 0x0F;
}

char high_nibble(char byte) {
	return byte & 0xF0;
}

short chars_to_int(char *buffer) {
	int n;
	int i;
	int temp;
	char byte;
	// print_hex_chars(buffer, 2);

	n = 0;
	temp = 16384;

	if (buffer[0] & 0x80) {
		printf("no support for negative numbers.\n");
		return 0;
	}

	for (i = 0; i < 15; i++) {
		byte = buffer[i / 8];
		if (byte & temp) {
			n = n + temp;
		}
		temp = temp / 2;
	}
	return n;
}

long chars_to_long(char *buffer) {
	long num;
	long temp;
	int i;
	char byte;
	int temp2;

	num = 0;
	temp = 1073741824;
	temp2 = 0x40;
	print_hex_chars(buffer, 4);

	if (buffer[0] & 0x80) {
		printf("no support for negative numbers.\n");
		return 0;
	}

	for (i = 1; i < 32; i++) {
		byte = buffer[i / 8];

		if (byte & temp2) {
			num = num + temp;
		}

		if ((i+1) % 8 == 0) {
			temp2 = 0x80;
		} else {
			temp2 = temp2 / 2;
		}
		temp = temp / 2;
	}
	return num;
}

void print_hex_chars(char *buffer, int n) {
	int i;
	int low_byte;
	int high_byte;
	for (i = 0; i < n; i++) {
		high_byte = (buffer[i] & 0xF0) >> 4;
		low_byte = buffer[i] & 0x0F;
		printf("%c%c", int_to_hex(high_byte), int_to_hex(low_byte));
		if (i < n - 1) {
			printf(" ");
		}
	}
	printf("\n");
}

char int_to_hex(int i) {
	if (i < 10) {
		return '0' + i;
	} else if (i < 16) {
		return 'A' + i - 10;
	}
	return ' ';
}
