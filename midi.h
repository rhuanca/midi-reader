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

typedef struct midi_format_struct {
	int format;
	int number_of_tracks;
	int deltatime_ticks;
} midi_format;



bool check_file(char *buffer);
bool check_length(char *buffer);
void read_format(char *buffer, midi_format *format);
int read_track_length(char *buffer);
#endif /* MIDI_H_ */
