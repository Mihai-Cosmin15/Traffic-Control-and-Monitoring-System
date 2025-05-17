#include "timers.h"

void init_timer1()
{
    TCCR1A = 0;
    TCCR1B = 0;

    // set CTC
    TCCR1B |= (1 << WGM12);

    // set prescaler to 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);

    // enable compare interrupt
    TIMSK1 |= (1 << OCIE1A);

    // Need to count 1s, using prescaler 1024 => OCR1A = 16000000 / 1024 - 1
    OCR1A = 15624;
}
