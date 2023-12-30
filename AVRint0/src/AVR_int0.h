#ifndef INT0_H
#define INT0_H

#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include "AVR_int_base.h"

namespace int0 {

    // Enumeration of the 4 different INT0
    // triggering stimuli.
    typedef enum trigger : uint8_t {
        TRGR_LOW = 0,
        TRGR_CHANGE,
        TRGR_FALLING,
        TRGR_RISING
    } trigger_t ;


    class AVR_int0 : public intbase::AVR_int_base {

    public:

        // Constructor. There's no destructor as the one
        // AVRint0 object will never be destructed.
        AVR_int0();
    };

} // end of namespace.

//There will be one of these in the cpp file for this class.
extern int0::AVR_int0 AVRint0;

#endif // INT0_H
