#include "AVR_int0.h"

namespace int0 {

// Constructor. Set up the base class details
// to define an INT0 handler. We use:
// INT0 as the enable bit,
// INTF0 as the interrupt flag bit,
// ISC01:0 as the trigger bit mask.
AVR_int0::AVR_int0() 
    : intbase::AVR_int_base(INT0, INTF0, ((1 << ISC01)|(1 << ISC00)) ) {}

} // end of namespace


// Define our one instance of the i0::AVR_int0 class.
int0::AVR_int0 AVRint0;


// This is the ISR for the INT0 interrupt. It will
// call the required user function if there is one.
ISR(INT0_vect) {
   AVRint0.interrupt();
}

