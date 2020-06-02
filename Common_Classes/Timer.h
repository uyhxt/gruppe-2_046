/*
 * Timer.h
 *
 *    Author: Max Zuidberg
 *     Email: m.zuidberg@icloud.com
 */

#ifndef TIMER_H_
#define TIMER_H_


/*
 * stdbool.h:               Boolean definitions for the C99 standard
 * stdint.h:                Variable definitions for the C99 standard
 * System.h:                Access to current CPU clock and other functions.
 */
#include <stdbool.h>
#include <stdint.h>
#include "System.h"


class Timer
{
public:
    Timer();
    virtual ~Timer();
    void init(System* sys, uint32_t base, void (*ISR)(void), uint32_t freq = 0);
    void start();
    void stop();
    void clearInterruptFlag();
    void setPeriodUS(uint32_t periodUS);
    void setFreq(uint32_t frequency);
    uint32_t getFreq();
    uint32_t getPeriodUS();
private:
    /*
     * The following array is needed to let the compiler know that the
     * precompiled class library needs space for its private variables.
     * Or in shorter terms: simply ignore it.
     */
    uint32_t spaceForLib[13];

};

#endif /* TIMER_H_ */
