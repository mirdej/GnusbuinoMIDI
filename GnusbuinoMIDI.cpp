/*
  MIDI.cpp - MIDI library for Midi-Gnusbuino
  Copyright (c) 2012 Michael Egger, me@anyma.ch

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

/******************************************************************************
 * Includes
 ******************************************************************************/

#include "Arduino.h"
#include "GnusbuinoMIDI.h"
#include "usbdrv.h"






/*---------------------------------------------------------------------------*/
/* PUT MIDI DATA INTO SEND-QUEUE                                             */ 
/*---------------------------------------------------------------------------*/
void MIDIClass::write(unsigned char command, unsigned char pitch,unsigned char velocity){

	// see if this command is already in queue, replace value
	for (unsigned char i = 0; i < MIDI_MAX_BUFFER; i++) {
		if (_midiSendQueue[3*i] == command) {
			if (_midiSendQueue[3*i+1] == pitch) {
				_midiSendQueue[3*i+2] = velocity;
				return;
			}
		}
	}
	_midiSendQueue[_midiSendEnqueueIdx++] = command;
	_midiSendQueue[_midiSendEnqueueIdx++] = pitch;
	_midiSendQueue[_midiSendEnqueueIdx++] = velocity;
	
	_midiSendEnqueueIdx %= MIDI_MAX_BUFFER * 3;
}


void MIDIClass::receiveMIDI(unsigned char command, unsigned char pitch,unsigned char velocity){
}

unsigned char MIDIClass::read(MIDIMessage* msg) {
}





void MIDIClass::sendMIDI(void) {

	if (usbInterruptIsReady()) {	// ready to send some MIDI ?
		if (_midiSendEnqueueIdx != _midiSendDequeueIdx) {

			unsigned char cmd;
			cmd = _midiSendQueue[_midiSendDequeueIdx];

			this->_midiOutData[0] = ((cmd>>4) & 0x0F) | ((cmd<<4) & 0xF0); //swap high/low nibble
			this->_midiOutData[1] = cmd;
			this->_midiOutData[2] = _midiSendQueue[_midiSendDequeueIdx+1];
			this->_midiOutData[3] = _midiSendQueue[_midiSendDequeueIdx+2];


			_midiSendQueue[_midiSendDequeueIdx++] = 0;
			_midiSendQueue[_midiSendDequeueIdx++] = 0;
			_midiSendQueue[_midiSendDequeueIdx++] = 0;

			_midiSendDequeueIdx %= MIDI_MAX_BUFFER * 3;

			usbSetInterrupt(this->_midiOutData, 4);
			
		}
	}
}




