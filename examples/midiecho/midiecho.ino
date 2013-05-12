/*---------------------------------------------------------------------------------------------

  Gnusbuino MIDI Library 2012 by Michael Egger
 
  MIDIECHO EXAMPLE
  Echoes anything it receives back over MIDI.
 
  This example code is in the public domain.

--------------------------------------------------------------------------------------------- */

 
#include "MIDI.h"            // you have to include the Gnusbuino MIDI library

MIDIMessage message;        // Variable to hold most recent midi message

void setup() {               // nothing to do in setup, pins are inputs by default
}


void loop() {
  
    if (MIDI.read(&message)) {                                    // need to put the ampersand "&" before "message"
        MIDI.write(message.command,message.key,message.value);
    }
    
 }
 
 
 /*---------------------------------------------------------------------------------------------
Some exercises:
   
   - build a patch in pd / MaxMSP that measures MIDI latency of the Gnusbuino
*/   
