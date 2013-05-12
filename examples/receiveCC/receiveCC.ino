/*---------------------------------------------------------------------------------------------

  Gnusbuino MIDI Library 2012 by Michael Egger
 
  How to listen to MIDI ControlChange Messages:
  This example assumes that you have a LED wired to pin 3 of the Gnusbuino.
  Now you can control the brightness of that LED from the computer via control change messages

  This example code is in the public domain.

--------------------------------------------------------------------------------------------- */

 
#include "MIDI.h"            // you have to include the Gnusbuino MIDI library


MIDIMessage message;         // variable to store the last received MIDI message


void setup() {               
  pinMode(3,OUTPUT);         // Pin 3 (and 4) on the Gnusbuino has a PWM ("analog") output
}


void loop() {
  
    if (MIDI.read(&message)) {                            // see if we have received a new MIDI message and store it in our variable
                                                          // don't forget the ampersand (&) before the variable name !
        if(message.command == MIDI_CONTROLCHANGE) {
                analogWrite(3,message.value);              
        }
    }    
    
 }
 
 
 /*---------------------------------------------------------------------------------------------
  Some exercises:

    - only respnd to a specific controller
    - add an RGB led to three pins and control its colour through MIDI
    
  */
