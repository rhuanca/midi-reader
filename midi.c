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
	printf(">>>> ");
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
		printf("\n");
		printf("RAW:");
		print_hex_chars(current, 10);
		vql_len = read_vql(&current, vql);
		delta_time = vql_to_long(vql, vql_len);
		event = &(track->midi_events[i]);
		if (*current == MIDI_META_EVENT) {
			event->delta_time = delta_time;
			event->is_meta = 1;
			read_midi_meta_event(&current, event);
		} else if (*current & (char)0x80) {
			print_hex_chars(current, 12);
			break;
		} else {
			print_hex_chars(current, 1);
			break;
		}
		printf("  %i - event: %2x\n", delta_time, event->event);
		printf("      length : %i\n", event->data_len);
		printf("      data : ");
		print_hex_chars(event->data, event->data_len);
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

	// fd = fopen("beethoven_fur_elise.mid", "r");
	fd = fopen("Beethoven_Symphony_No._5_4th.mid", "r");

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
	read_format(buffer, &format);

	printf("Midi Info:\n" );
	printf("  Format: %i\n", format.format);
	printf("  Delta Time Ticks: %i\n", format.deltatime_ticks);
	printf("  # of Tracks: %i\n", format.number_of_tracks);

	// read tracks
	for(i=0;i< format.number_of_tracks; i++) {
		fread(buffer, 1, 8, fd);
		trk_len = read_track_length(buffer);
		printf("Track %i: length = %i\n", i, trk_len);
		read_count = fread(buffer, 1, trk_len, fd);
		if (read_count != trk_len) {
			printf("unable to read track.\n");
			fclose(fd);
			return 1;
		}
		read_midi_events(buffer, trk_len, &tracks[i]);
	}

	fclose(fd);
	return 0;
}
