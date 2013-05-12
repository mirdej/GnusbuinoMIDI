/*---------------------------------------------------------------------------------------------

  Gnusbuino MIDI Library 2012 by Michael Egger
 
  SEND NOTES EXAMPLE
  Send a chord of three notes to the host over MIDI
 
  This example code is in the public domain.

--------------------------------------------------------------------------------------------- */



#include <MIDI.h>        // you MUST include the Gnusbuino MIDI library

unsigned long lastTime;            // variable to store the last time we sent a chord

void setup() {}


// the loop routine runs over and over again forever:
void loop() {

  if (millis()-lastTime >= 500)  {             // every 500 miliseconds = 2 times per second

        //MIDI.write(MIDI_NOTEON, note , velocity )
        
         MIDI.write(MIDI_NOTEON,60,127);            // put three notes into the MIDI send queue
         MIDI.write(MIDI_NOTEON,64,127);
         MIDI.write(MIDI_NOTEON,67,127);
         lastTime = millis();      
  }   
}





/*---------------------------------------------------------------------------------------------
Some exercises:

  - change the notes to create a Gmaj7 chord  (tip: instead of numerical values you can also write note names eg. _Cis3 )
  - have the code also send the correct note off messages
  - change duration via a potentiometer
  - add buttons to build a keyboard
  - play arpeggios
  - build a subroutine that can play a lot of chords
  
*/
