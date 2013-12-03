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



/******************************************************************************
 * Constructors
 ******************************************************************************/

/******************************************************************************
 * User API
 ******************************************************************************/
// ------------------------------------------------------------------------------
// - MIDI SEND QUEUE
// ------------------------------------------------------------------------------


MIDIQueue::MIDIQueue() {
       front = 0;
       rear = 0;
       count = 0;
   }      
 
void MIDIQueue::Enqueue(unsigned char cmd, unsigned char data1, unsigned char data2) {

		if (this->count >= MIDI_MAX_BUFFER-1) {				// avoid overflow
			unsigned char  t[4];
			this->Dequeue(t);	
	//	PORTB |= (1 << 0);
		}
		
       MIDIQueueNode* tmp = new MIDIQueueNode();		       // Create a new node

       tmp->cmd = cmd;
       tmp->data1 = data1 & 0x7F;
       tmp->data2 = data2 & 0x7F;  //midi is 7 bits only
       tmp->next = 0;

       if ( isEmpty() ) {
           front = rear = tmp;		// Add the first element
       } else {
           rear->next = tmp;		  // Append to the list
           rear = tmp;
       }
       this->count++;
   }      

unsigned char MIDIQueue::Dequeue(unsigned char* data) {          
       if ( !isEmpty() ) {

			data[0] = ((front->cmd>>4) & 0x0F) | ((front->cmd<<4) & 0xF0); //swap high/low nibble
			data[1] = front->cmd;
			data[2] = front->data1;
			data[3] = front->data2;
			
      		MIDIQueueNode* tmp = front;
      		front = front->next; // Move the front pointer to next node
     		this->count--;
    		delete tmp; 
    		return 1;
    	} else return 0;
   } 
   
   	int MIDIQueue::Size() { return this->count;}
	bool MIDIQueue::isEmpty(){ return this->count == 0 ? true : false; }




/*---------------------------------------------------------------------------*/
/* PUT MIDI DATA INTO SEND-QUEUE                                             */ 
/*---------------------------------------------------------------------------*/
void MIDIClass::write(unsigned char command, unsigned char pitch,unsigned char velocity){
	_midiSendQueue.Enqueue(command,pitch,velocity);
}


void MIDIClass::receiveMIDI(unsigned char command, unsigned char pitch,unsigned char velocity){
	_midiReceiveQueue.Enqueue(command,pitch,velocity);
}

unsigned char MIDIClass::read(MIDIMessage* msg) {
	
	if (_midiReceiveQueue.Dequeue(this->_midiMsg2)) {
			msg->command = this->_midiMsg2[1];
			msg->key = this->_midiMsg2[2];
			msg->value = this->_midiMsg2[3];
			return 1;
	} else {
			return 0;
	}
}





void MIDIClass::sendMIDI(void) {

	if (usbInterruptIsReady()) {	// ready to send some MIDI ?
		if (_midiSendQueue.Dequeue(this->_midiMsg)) {
				//statusLedBlink(StatusLed_Yellow);
				usbSetInterrupt(this->_midiMsg, 4);
		}
	}
}




