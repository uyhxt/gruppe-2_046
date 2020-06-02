/*
 * PWM.h
 *
 *    Author:
 *     Email:
 */

#ifndef PWM_H_
#define PWM_H_


/*
 * stdbool.h:               Boolean definitions for the C99 standard
 * stdint.h:                Variable definitions for the C99 standard
 * System.h:                Access to current CPU clock and other functions.
 */
#include <stdbool.h>
#include <stdint.h>
#include "System.h"


class PWM
{
public:
    PWM();
    virtual ~PWM();
    void init(System *sys,uint32_t portBase, uint32_t pin1, uint32_t pin2,
              bool invert = false, uint32_t freq = 5000);
    void setFreq(uint32_t freq);
    void setDuty(float duty);
private:
    /*
     * The following array is needed to let the compiler know that the
     * precompiled class library needs space for its private variables.
     * Or in shorter terms: simply ignore it.
     */
    uint32_t spaceForLib[12];

};

#endif /* PWM_H_ */
