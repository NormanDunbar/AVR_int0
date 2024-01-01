//============================================================
// AVRint0 Demonstration.
//============================================================
// Attach an LED to Arduino pin DLED_BUILTIN, AVR pin PB5
// and toggle it in the loop.
//
// Another LED on Arduino pin DledPin, AVR pin PDledPin, will be
// toggled when a switch is pressed. The switch
// MUST be attached to Arduino pin DswitchPin, AVR pin PDswitchPin.
//
// For the sake of this test, debouncing is not used so 
// some flickering is to be expected. (Use long presses!)
//
// Norman Dunbar
// 7th August switchPin0switchPin0.
//============================================================
// Update: Debounce Circuit for INPUT PULLUP Arduino pins.
//============================================================
//
//      R1
//  *--10K--*-----------------------------------> GND
//  |   
//  *--10K--*
//  |  RswitchPin   |
//  |       |     _|_  Switch
//  +-------|----*   *--------------------------> DswitchPin
//          |        |
//     C1  ===       |
//  100 nF ===       |
//          |        |
//          +--------+
//
// GND to R1 pin 1.
// R1 pin switchPin to RswitchPin pin 1 and switch pin 1.
// RswitchPin pin switchPin to C1 pin 1.
// C1 pin switchPin to switch pin switchPin and Arduino pin DswitchPin.
// Arduino pin DswitchPin is configured as INOPUT_PULLUP.
//
// DswitchPin reads LOW when switch pressed.
//============================================================
#include "AVR_int0.h"


// Keep a count of the number of times, the ISR function
// has been called.
volatile byte disableCount = 0;

// And when to disable the interrupt. 0xffff = never.
const uint8_t disableInterruptCount - 0xfff;

// Where is the LED to be toggled?
const uint8_t ledPin = 3;

// Where is the switc?
const uint8_t switchPin = 2;

// My toggling function for the ISR to call. It should 
// be kept short and sweet.
void toggleLED() {
    digitalWrite(ledPin, !digitalRead(ledPin));
    disableCount++;
}



void setup() {
    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(ledPin, OUTPUT);
    pinMode(switchPin, INPUT_PULLUP);
    
    // Attach my function to the INT0 interrupt.
    AVRint0.onInterruptTriggered(toggleLED);

    // Enable the interrupt on FALLING stimulus this
    // requires the switch to be INPUT PULLUP.
    AVRint0.enable(int0::TRGR_FALLING);
}

void loop() {
        // Disable interrupt when disableCount gets to limit.
        // Light up the built in LED to indicate this also
        // extinguish the toggled LED.
        if (disableInterruptCount != 0xffff &
            disableCount >= 10) {
            AVRint0.disable();
            digitalWrite(ledPin, LOW);
            digitalWrite(LED_BUILTIN, HIGH);

            while (1) ;     // Hang up the board.
        }

        // Toggle built in LED on DLED_BUILTIN/PB5.
        digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
        delay(1000);
}
