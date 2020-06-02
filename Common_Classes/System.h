/*
 * System.h
 *
 *    Author: Max Zuidberg
 *     Email: m.zuidberg@icloud.com
 * Co-author: Henri Hornburg
 *     Email: henri.hornburg@student.kit.edu
 */

#ifndef SYSTEM_H_
#define SYSTEM_H_


/*
 * stdbool.h:               Boolean definitions for the C99 standard
 * stdint.h:                Variable definitions for the C99 standard
 * inc/hw_types.h:          Macros for hardware access, both direct and via the
 *                          bit-band region.
 * inc/hw_memmap.h:         Macros defining the memory map of the Tiva C Series
 *                          device. This includes defines such as peripheral
 *                          base address locations such as GPIO_PORTF_BASE.
 * inc/hw_gpio.h:           Defines for the GPIO register offsets.
 * driverlib/pin_map.h:     Mapping of peripherals to pins for all parts.
 * driverlib/sysctl.h:      Defines and macros for the System Control API of
 *                          DriverLib. This includes API functions such as
 *                          SysCtlClockSet.
 * driverlib/interrupt.h:   Defines and macros for NVIC Controller (Interrupt)
 *                          API of driverLib. This includes API functions such
 *                          as IntEnable and IntPrioritySet.
 * driverlib/fpu.h:         Prototypes for the floating point manipulation
 *                          routines.
 * driverlib/gpio.h:        Defines and macros for GPIO API of DriverLib. This
 *                          includes API functions such as GPIOPinWrite.
 * uartstdio.h:             Utility driver to provide simple UART console
 *                          functions.
 * ErrorCodes.h:            Enum with error codes for the error method.
 */
#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_types.h"
#include "inc/hw_memmap.h"
#include "inc/hw_gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "uartstdio.h"
#include "ErrorCodes.h"


class System
{
public:
    System();
    virtual ~System();
    void init(uint32_t clk);
    void error(ErrorCodes ErrorCode = UnknownError,
               void *faultOrigin0 = 0,
               void *faultOrigin1 = 0,
               void *faultOrigin2 = 0);
    void enableFPU();
    uint32_t getClockFreq();
    uint32_t getPWMClockDiv();
    void delayCycles(uint32_t cycles);
    void delayUS(uint32_t us);
    void setDebugging(bool debug);
    void setDebugVal(const char* name, int32_t value);
    void sendDebugVals();

private:
    bool systemDebugEnabled = true;
    bool systemDebugNewLabel = false;
    const static uint32_t systemMaxDebugVals = 8;
    const char systemDebugUnused[1] = "";
    int32_t systemDebugVals[systemMaxDebugVals];
    const char* systemDebugNames[systemMaxDebugVals] = {systemDebugUnused,
                                                        systemDebugUnused,
                                                        systemDebugUnused,
                                                        systemDebugUnused,
                                                        systemDebugUnused,
                                                        systemDebugUnused,
                                                        systemDebugUnused,
                                                        systemDebugUnused};
    bool systemTooManyDebugVals = false;

    uint32_t systemClockFrequency = 0;
    uint32_t systemPWMClockDiv = 0;

    // All peripherals of the uC
    const uint_fast8_t systemPeripheralsCount = 49;
    const uint32_t systemPeripherals[49] = {SYSCTL_PERIPH_WDOG0,
                                            SYSCTL_PERIPH_WDOG1,
                                            SYSCTL_PERIPH_TIMER0,
                                            SYSCTL_PERIPH_TIMER1,
                                            SYSCTL_PERIPH_TIMER2,
                                            SYSCTL_PERIPH_TIMER3,
                                            SYSCTL_PERIPH_TIMER4,
                                            SYSCTL_PERIPH_TIMER5,
                                            SYSCTL_PERIPH_GPIOA,
                                            SYSCTL_PERIPH_GPIOB,
                                            SYSCTL_PERIPH_GPIOC,
                                            SYSCTL_PERIPH_GPIOD,
                                            SYSCTL_PERIPH_GPIOE,
                                            SYSCTL_PERIPH_GPIOF,
                                            SYSCTL_PERIPH_UDMA,
                                            SYSCTL_PERIPH_HIBERNATE,
                                            SYSCTL_PERIPH_UART0,
                                            SYSCTL_PERIPH_UART1,
                                            SYSCTL_PERIPH_UART2,
                                            SYSCTL_PERIPH_UART3,
                                            SYSCTL_PERIPH_UART4,
                                            SYSCTL_PERIPH_UART5,
                                            SYSCTL_PERIPH_UART6,
                                            SYSCTL_PERIPH_UART7,
                                            SYSCTL_PERIPH_SSI0,
                                            SYSCTL_PERIPH_SSI1,
                                            SYSCTL_PERIPH_SSI2,
                                            SYSCTL_PERIPH_SSI3,
                                            SYSCTL_PERIPH_I2C0,
                                            SYSCTL_PERIPH_I2C1,
                                            SYSCTL_PERIPH_I2C2,
                                            SYSCTL_PERIPH_I2C3,
                                            SYSCTL_PERIPH_USB0,
                                            SYSCTL_PERIPH_CAN0,
                                            SYSCTL_PERIPH_CAN1,
                                            SYSCTL_PERIPH_ADC0,
                                            SYSCTL_PERIPH_ADC1,
                                            SYSCTL_PERIPH_COMP0,
                                            SYSCTL_PERIPH_PWM0,
                                            SYSCTL_PERIPH_PWM1,
                                            SYSCTL_PERIPH_QEI0,
                                            SYSCTL_PERIPH_QEI1,
                                            SYSCTL_PERIPH_EEPROM0,
                                            SYSCTL_PERIPH_WTIMER0,
                                            SYSCTL_PERIPH_WTIMER1,
                                            SYSCTL_PERIPH_WTIMER2,
                                            SYSCTL_PERIPH_WTIMER3,
                                            SYSCTL_PERIPH_WTIMER4,
                                            SYSCTL_PERIPH_WTIMER5};
};


#endif /* SYSTEM_H_ */
