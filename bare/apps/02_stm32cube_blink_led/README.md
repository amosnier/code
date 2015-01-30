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

##Implementation

###Pointing to the cube

Using `BSP_LED_Toggle(LED1)` and the like will simplify the blink program to a
minimum. However, integrating STM32CubeF4 (let's call it the cube) is the
complicated part here. The cube is designed to be configured by a few own source
files provided as templates, but otherwise not changed at all by the application
developer. Therefore, I chose not to copy the whole code in this repository, but
rather to point to a standard cube extraction outside of the project directory
([cube](https://github.com/amosnier/code/blob/master/bare/stm32cube)).

###Makefile
Introducing the cube as a source code resource that is external to the project
directory forces us to introduce a non-trivial Makefile structure. Therefore, the
opportunity was taken to solve common Makefile issues:

- Automatic generation of header dependencies.
- General handling of code source in multiple directories.
- Sharing of Makefile code between applications.

###C-runtime environment
We also took the opportunity of this application to use standard C-runtime
environment resources from our tool chain, as well as assembly startup file and
linker script from the toolchain's examples. In that respect, relevant Makefile
flags are:

1. `-specs=nosys.specs`
2. `-D__STARTUP_CLEAR_BSS`
3. `-D__START=main`

These seem to work together for an environment without standard input/output and
imply that we do not invoke `_mainCRTStartup` provided by libgloss, but instead
clear the BSS segment in our startup assembly file and then directly branch to
our main function. I have experimented with `-specs=rdimon.specs` instead, but
then `_mainCRTStartup` was invoked and that led to an exception. I am not sure
why yet, but I guess that in order to use `rdimon.specs`, one needs to provide a
proper semi-hosting environment, i.e. somehow specify standard in and out. This
will be for a later application.
