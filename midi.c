/*
 * midi.c
 *
 *  Created on: Feb 7, 2014
 *      Author: renan
 */

#include <stdio.h>
#include "utils.h"
#include "midi.h"

// for midi
#define BUFFER_SIZE = 1024;

bool check_file(char *buffer) {
	return buffer[0] == 'M' && buffer[1] == 'T' && buffer[2] == 'h' && buffer[3] == 'd';
}

bool check_length(char *buffer) {
	return (int)buffer[4] == 6;
}

void read_format(char *buffer, midi_format *format)
{
	// print_hex_chars(buffer, 6);
	format->format = chars_to_int(buffer);
	format->number_of_tracks = chars_to_int(buffer+2);
	format->deltatime_ticks = chars_to_int(buffer+4);
}

int read_track_length(char *buffer) {
	unsigned long len;
	if(buffer[0] != 'M' && buffer[1] != 'T' && buffer[2] != 'r' && buffer[3] != 'k') {
		return 0;
	}

	len = chars_to_long(buffer+4);
	return len;
}

int main(int count, char **args)
{
	midi_format format;
	FILE *fd;
	char buffer[1024];
	int trk_len;
	fd = fopen("Beethoven_Symphony_No._5_4th.mid","r");

	if(fd == 0) {
		printf("unable to open midi file.\n");
		return 1;
	}

	fread(buffer, 1, 4, fd);
	if(!check_file(buffer)) {
		printf("not a midi file.\n");
		fclose(fd);
		return 1;
	}

	fread(buffer, 1, 4, fd);
	if(check_length(buffer)) {
		printf("not a valid header length.\n");
		fclose(fd);
		return 1;
	}

	fread(buffer, 1, 6, fd);
	// print_hex_chars(buffer, 6);
	read_format(buffer, &format);
	printf("format %i\n", format.format);
	printf("tracks %i\n", format.number_of_tracks);
	printf("deltatime_ticks %i\n", format.deltatime_ticks);



	// read tracks
	fread(buffer, 1, 8, fd);
	// print_hex_chars(buffer, 8);
	trk_len = read_track_length(buffer);
	printf("track length = %i\n", trk_len);


	fclose(fd);
	return 0;
}
