/*
 * midi_constants.h
 *
 *  Created on: Feb 5, 2014
 *      Author: renan
 */


// ref: http://www.petesqbsite.com/sections/express/issue19/midifilespart2.html
#ifndef MIDI_CONSTANTS_H_
#define MIDI_CONSTANTS_H_

// ----------------------
//  Constant Definitions
// ----------------------
// -------------------
//  MIDI File Formats
// -------------------
#define SingleTrack          0
#define MultipleTracksSync   1
#define MultipleTracksAsync  2

// ----------------------------------
//  MIDI Status Constant Definitions
// ----------------------------------
#define NoteOff              0x80
#define NoteOn               0x90
#define PolyKeypress         0xA0
#define ControllerChange     0xB0
#define ProgramChange        0xC0
#define ChannelPressure      0xD0
#define PitchBend            0xE0
#define SysExMessage         0xF0

// -----------------------------------
//  MIDI Controller Numbers Constants
// -----------------------------------
#define MolulationWheel      1
#define BreathController     2
#define FootController       4
#define PortamentoTime       5
#define MainVolume           7
#define Balance              8
#define Pan                  10
#define ExpressController    11
#define DamperPedal          64
#define Portamento           65
#define Sostenuto            66
#define SoftPedal            67
#define Hold2                69
#define ExternalFXDepth      91
#define TremeloDepth         92
#define ChorusDepth          93
#define DetuneDepth          94
#define PhaserDepth          95
#define DataIncrement        96
#define DataDecrement        97

typedef struct midi_time_structure {
  short int bar;
  short int beat;
  short int tick;
} midi_time;

/*typedef struct midi_event_structure {
	midi_time event_time;
	char event_delta_time;
	char status_byte;
	char channel_byte;
	char data_byte_one;
	char data_byte_two;
} midi_event;*/

/*typedef struct midi_track_structure {
	short int track_number;
	short int track_event_count;
	midi_event midi_events[131072];
};*/

#endif /* MIDI_CONSTANTS_H_ */
