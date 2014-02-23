/*
 * midi.h
 *
 *  Created on: Feb 8, 2014
 *      Author: renan
 */

#ifndef MIDI_H_
#define MIDI_H_

// for programmer
#define bool int;
#define true 1
#define false 0

// for midi
#define SINGLE_TRACK 0;
#define MULTIPLE_TRACKS_SYNC 1;
#define MULTIPLE_TRACKS_ASYNC 2;

// midi commands

#define MIDI_META_EVENT ((char)0xff)



// midi meta commands
#define MIDI_META_TIME_SIGNATURE_EVENT ((char)0x58)
#define MIDI_END_OF_TRACK_EVENT ((char)0x2F)

typedef struct midi_format_struct {
	int format;
	int number_of_tracks;
	int deltatime_ticks;
} midi_format;

typedef struct midi_event_structure {
	long delta_time;
	int is_meta;
	char event;
	char data[4];
	char data_len;
} midi_event;

typedef struct midi_track_structure {
	short int track_number;
	short int track_event_count;
	midi_event midi_events[1024];
} midi_track;



int check_file(char *buffer);
int check_length(char *buffer);
void read_format(char *buffer, midi_format *format);
int read_track_length(char *buffer);
int read_midi_events(char *buffer, int num_tracks, midi_track *track);
void read_midi_meta_event(char **buffer, midi_event *event);
void read_midi_event(char **buffer, midi_event *event);

void print_midi_event_desc(char evt);

#endif /* MIDI_H_ */
