/*
 * midi.c
 *
 *  Created on: Feb 7, 2014
 *      Author: renan
 */

#include "midi.h"

#include <stdio.h>

#include "utils.h"

// for midi
#define BUFFER_SIZE = 1024;

int check_file(char *buffer) {
	return buffer[0] == 'M' && buffer[1] == 'T' && buffer[2] == 'h'
			&& buffer[3] == 'd';
}

int check_length(char *buffer) {
	return (int) buffer[4] == 6;
}

void read_format(char *buffer, midi_format *format) {
	// print_hex_chars(buffer, 6);
	format->format = chars_to_int(buffer);
	format->number_of_tracks = chars_to_int(buffer + 2);
	format->deltatime_ticks = chars_to_int(buffer + 4);
}

int read_track_length(char *buffer) {
	unsigned long len;
	print_hex_chars(buffer, 8);
	if (buffer[0] != 'M' && buffer[1] != 'T' && buffer[2] != 'r'
			&& buffer[3] != 'k') {
		return 0;
	}

	len = chars_to_long(buffer + 4);
	return len;
}

int read_midi_events(char *buffer, int num_tracks, midi_track *track) {
	char *current;
	char vql[4];
	int vql_len;
	int i;
	long delta_time;
	midi_event *event;
	current = buffer;

	i = 0;
	do {
		printf(">>>> ");
		print_hex_chars(current, 5);
		vql_len = read_vql(&current, vql);
		printf("vql len = %i\n", vql_len);
		delta_time = vql_to_long(vql, vql_len);
		event = &(track->midi_events[i]);
		printf("delta time = %i\n", delta_time);
		if (*current == MIDI_META_EVENT) {
			printf("read meta event\n");
			event->delta_time = delta_time;
			event->is_meta = 1;
			read_midi_meta_event(&current, event);
		} else if (*current & (char)0x80) {
			printf("it is a message\n");
			print_hex_chars(current, 12);
			break;
		} else {

			printf("entro else \n");
			print_hex_chars(current, 1);
			break;
		}

		// print_hex_chars(event->data, event->data_len);
		printf("oops event: %x\n", event->event);
		//track->midi_events[i] = *event;
		i++;
	} while (event->event != MIDI_END_OF_TRACK_EVENT);
	track->track_event_count = i;
	return i;
}

void read_midi_meta_event(char **current, midi_event *event) {
	int i;
	(*current)++;
	event->event = **current;
	(*current)++;
	event->data_len = **current;

	for (i = 0; i < event->data_len; i++) {
		(*current)++;
		event->data[i] = **current;
	}
	(*current)++;
}

void read_midi_event(char **buffer, midi_event *event) {

}

void print_midi_event_desc(char evt) {
	if (evt == MIDI_META_EVENT) {
		printf("MIDI_META_EVENT\n");
	} else if (evt == MIDI_META_TIME_SIGNATURE_EVENT) {
		printf("MIDI_META_TIME_SIGNATURE_COMMAND\n");
	} else {
		printf("UNKOWN\n");
	}
}

int main(int argc, char *argv[]) {
	midi_format format;
	FILE *fd;
	char buffer[1024];
	int trk_len;
	int read_count;
	int i;
	midi_track tracks[5];

	fd = fopen("beethoven_fur_elise.mid", "r");

	if (fd == 0) {
		printf("unable to open midi file.\n");
		return 1;
	}

	fread(buffer, 1, 4, fd);
	if (!check_file(buffer)) {
		printf("not a midi file.\n");
		fclose(fd);
		return 1;
	}

	fread(buffer, 1, 4, fd);
	if (check_length(buffer)) {
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
	for(i=0;i< format.number_of_tracks; i++) {

		printf("=================== reading track %i\n", i);
		fread(buffer, 1, 8, fd);
		// print_hex_chars(buffer, 8);
		trk_len = read_track_length(buffer);
		printf("track length = %i\n", trk_len);

		read_count = fread(buffer, 1, trk_len, fd);
		if (read_count != trk_len) {
			printf("unable to read track.\n");
			fclose(fd);
			return 1;
		}

		// printf("starting to read first track.\n");
		read_midi_events(buffer, trk_len, &tracks[i]);
		printf("event counts = %i\n", tracks[i].track_event_count);

//		fread(buffer, 1, 8, fd);
//		buffer[8] = '\0';
//		printf(buffer);
//		print_hex_chars(buffer, 8);

	}

//read_count = fread(buffer, 1, 4, fd);
//buffer[4] = '\0';
//printf(buffer);

	fclose(fd);
	return 0;
}
