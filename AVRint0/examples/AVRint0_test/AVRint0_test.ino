//============================================================
// AVRint0 Demonstration.
//============================================================
// Attach an LED to Arduino pin D13, AVR pin PB5
// and toggle it in the loop.
//
// Another LED on Arduino pin D3, AVR pin PD3, will be
// toggled when a switch is pressed. The switch
// MUST be attached to Arduino pin D2, AVR pin PD2.
//
// For the sake of this test, debouncing is not used so 
// some flickering is to be expected. (Use long presses!)
//
// Norman Dunbar
// 7th August 2020.
//============================================================
// Update: Debounce Circuit for INPUT PULLUP Arduino pins.
//============================================================
//
//      R1
//  *--10K--*-----------------------------------> GND
//  |   
//  *--10K--*
//  |  R2   |
//  |       |     _|_  Switch
//  +-------|----*   *--------------------------> D2
//          |        |
//     C1  ===       |
//  100 nF ===       |
//          |        |
//          +--------+
//
// GND to R1 pin 1.
// R1 pin 2 to R2 pin 1 and switch pin 1.
// R2 pin 2 to C1 pin 1.
// C1 pin 2 to switch pin 2 and Arduino pin D2.
// Arduino pin D2 is configured as INOPUT_PULLUP.
//
// D2 reads LOW when switch pressed.
//============================================================
#include "AVR_int0.h"


// Keep a count of the number of times, the ISR function
// has been called.
volatile byte disableCount = 0;


// My toggling function for the ISR to call. It should 
// be kept short and sweet.
void toggleLED() {
    digitalWrite(3, !digitalRead(3));
    disableCount++;
}



void setup() {
    pinMode(13, OUTPUT);
    pinMode(3, OUTPUT);
    pinMode(2, INPUT_PULLUP);
    
    // Attach my function to the INT0 interrupt.
    AVRint0.onInterruptTriggered(toggleLED);

    // Enable the interrupt on FALLING stimulus this
    // requires the switch to be INPUT PULLUP.
    AVRint0.enable(int0::TRGR_FALLING);
}

void loop() {
        // Disable interrupt when disableCount gets to 10.
        // Light up the built in LED to indicate this also
        // extinguish the toggled LED.
        if (disableCount >= 10) {
            AVRint0.disable();
            digitalWrite(3, LOW);
            digitalWrite(13, HIGH);

            while (1) ;     // Hang up the board.
        }

        // Toggle built in LED on D13/PB5.
        digitalWrite(13, !digitalRead(13));
        delay(1000);
}
