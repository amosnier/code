#Blink LED with STM32CubeF4

##Background

The idea of this application is to port the blink LED program to STM32CubeF4
which is a software package provided by ST. As far as we are concerned the
important part of that software package is a complete set of drivers in C-source
code. One might think that using that software package is a breach towards the
minimalist approach of this project. However, assuming that we want to use most
of the features offered by the boards we have access to, the alternative would
be to rewrite the whole set of device drivers from scratch. One just needs to
have a look at the number of pages of the datasheet and and the reference manual
for the STM32F407xx MCU (185 and 1718, respectively) to realize what volume of
code we are talking about. Device driver code for a whole MCU is big, boring,
and error prone! I will rather spend my time at the application level.

##Board support package

Given that we are using the STM32F4-Discovery board in this application, which
is a standard ST board, we even have one more level of ready to use code in
STM32CubeF4: the board support package (BSP) for the board. The BSP not only
knows about all the GPIO pins on the MCU, it also knows how they are connected
to LED1 to LED4, and can therefore provide functions like `BSP_LED_Toggle(LED1)`.
