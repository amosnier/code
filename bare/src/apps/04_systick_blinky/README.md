#SysTick blinky

##Background
This is a variant of the famous blinky program, where the LED toggling is
performed in the SysTick ISR instead of in the `main()` loop. That also implies
that the `main()` loop is empty.

##Implementation
A simplistic scheduler, that supports the registration of run-to-completion
functions in a static list with each its time period, was created. The actual
scheduling is done in the SysTick ISR. In the standard ST HAL code, the
SysTick's period is 1 ms. This is among others used for timeouts in device
drivers. We keep that standard configuration in this application, and 1 ms is
the lowest possible period for a scheduled function. In the case of this
application, only one function is scheduled, with a period of 1000 ms.
