/*
  GnusbuinoMIDI.h - MIDI over USB library for the Gnusbuino
  http://gnusb.sourceforge.net
  
  Copyright (c) 2012 Michael Egger.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef MIDICLASS_h
#define MIDICLASS_h

#include <inttypes.h>
#include "GnusbuinoMIDInotes.h"

/******************************************************************************
 * Definitions
 ******************************************************************************/
// MIDI Status Bytes

#define MIDI_NOTEOFF			0x80
#define MIDI_NOTEON				0x90
#define MIDI_POLYAFTERTOUCH		0xA0
#define MIDI_CONTROLCHANGE		0xB0
#define MIDI_PROGRAMCHANGE		0xC0
#define MIDI_CHANNELAFTERTOUCH	0xD0
#define MIDI_PITCHBEND			0xE0

//Realtime Messages
#define MIDI_QUARTERFRAME		0xF1
#define MIDI_SONGPOS			0xF2
#define MIDI_SONGSELECT			0xF3
#define MIDI_TIMINGCLOCK		0xF8
#define MIDI_START				0xFA
#define MIDI_CONTINUE			0xFB
#define MIDI_STOP				0xFC


#define MIDI_MAX_BUFFER		64


typedef struct {
	unsigned char command;
	unsigned char key;
	unsigned char value;
} MIDIMessage;

/******************************************************************************
 * MIDI QUEUE
 ******************************************************************************/
class MIDIQueueNode {
	public: 
		unsigned char cmd;
		unsigned char data1;
		unsigned char data2;
	   	MIDIQueueNode* next;
};

class MIDIQueue {  
private:
   MIDIQueueNode* front;
   MIDIQueueNode* rear;
   int count;

public:
    MIDIQueue();
	void Enqueue(unsigned char cmd, unsigned char data1, unsigned char data2);
   	unsigned char Dequeue(unsigned char* data);
   	int Size();
	bool isEmpty();
};


/******************************************************************************
 * MIDI Class
 ******************************************************************************/

class MIDIClass {

public:
	void write(uint8_t,uint8_t,uint8_t);
	uint8_t read(MIDIMessage*);

	void sendMIDI(void);
	void receiveMIDI(uint8_t,uint8_t,uint8_t);
	
	private:
		uint8_t _midiMsg[8];
		uint8_t _midiMsg2[4];
		MIDIQueue _midiSendQueue;
		MIDIQueue _midiReceiveQueue;
  
};

	extern MIDIClass MIDI;

#endif

