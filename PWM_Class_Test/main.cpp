/*
 * main.cpp
 *

 *    Author: Max Zuidberg
 *    Email: m.zuidberg@icloud.com
 *
 *
 *  Test program for the PWM class. It allows to control two motors, each
 *  connected to an H-Bridge. Each motor can be controlled with two GPIO
 *  pins. One is to increase the duty cycle in steps of 10% and the other
 *  one to reverse the direction.

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
#include "PWM.h"


int main(void)
{
    while (1)
    {

    }
}
