/*
 * ADC.h
 *
 *    Author:
 *     Email:
 */

#ifndef ADC_H_
#define ADC_H_


/*
 * stdbool.h:               Boolean definitions for the C99 standard
 * stdint.h:                Variable definitions for the C99 standard
 * System.h:                Access to current CPU clock and other functions.
 */
#include <stdbool.h>
#include <stdint.h>
#include "System.h"


class ADC
{
public:
    ADC();
    virtual ~ADC();
    void init(System *sys, uint32_t base, uint32_t sampleSeq, uint32_t analogInput);
    void setHWAveraging(uint32_t averaging);
    uint32_t read();
    float readVolt();
private:
    /*
     * The following array is needed to let the compiler know that the
     * precompiled class library needs space for its private variables.
     * Or in shorter terms: simply ignore it.
     */
    uint32_t spaceForLib[41];

};


#endif /* ADC_H_ */
