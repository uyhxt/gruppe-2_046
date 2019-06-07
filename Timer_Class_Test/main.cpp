/*
 * main.cpp
 *
 *    Author:
 *     Email:
 */

/*
 * stdbool.h:           Boolean definitions for the C99 standard
 * stdint.h:            Variable definitions for the C99 standard
 * System.h:            Header file for the System class
 *                      (needed for example for clock settings)
 * GPIO.h:              Header file for the GPIO class
 * Timer.h:             Header file for the Timer class
 */
#include <stdbool.h>
#include <stdint.h>
#include "System.h"
#include "GPIO.h"
#include "Timer.h"

/*
 * Template for ISR on timer x:
 * void ISRx()
 * {
 *     //Clear interrupt flag
 *     timerx.clearInterruptFlag();
 *
 *     // Your code
 * }
 */

int main(void)
{
    while (1)
    {

    }
}
