#Minimal MCU init for STM32F407xx

Pretty much a copy/paste of the STM32F4-Discovery template from ST. It seems
general for the MCU. However main.h/.c were renamed to mcu_init.h/.c, since it
felt like a cleaner structure.

This whole directory will be compiled and linked to the application, that will
typically invoke `mcu_init()` as its first invokation in `main()`. This
directory will also belong to the include directories for the application.
