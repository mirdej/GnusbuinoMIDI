/*---------------------------------------------------------------------------------------------

  Gnusbuino MIDI Library 2012 by Michael Egger
 
  RECEIVE NOTE EXAMPLE
  Light an LED when the Gnusbuino receives a note-on message. Turns it off again on note-off

  This example code is in the public domain.

--------------------------------------------------------------------------------------------- */

 
#include "GnusbuinoMIDI.h"            // you have to include the Gnusbuino MIDI library


MIDIMessage message;          

void setup() {               
  pinMode(3,OUTPUT);
}


void loop() {
  
    if (MIDI.read(&message)) {
      
        switch(message.command) {
            case MIDI_NOTEON:
              digitalWrite(3,message.value);        // MaxMSP actually sends "noteon x 0" instead of "noteoff"
              break;

            case MIDI_NOTEOFF:
              digitalWrite(3,0);        
             
        }
    }
 }
 
 
/*---------------------------------------------------------------------------------------------
  Some exercises:
  
    - only respond to specific notes
    - more leds on separate notes
    - control led brightness with velocity
    - add relays to control arbitray electric equipment through MIDI note messages
    
*/

