#Simplest "blink LED" program
"Blink LED"-program based on as little code as possible:
- No CPU clock configuration, the blinking frequency is arbitrary.
- A startup C-code taken from [GCC ARM Embedded]
(https://launchpad.net/gcc-arm-embedded) samples.
- No involvement of STM32F4Cube yet, but the memory part of the linker script is
adapted do the STM32F407xx
##Binary size
```bash
Invoking: Cross ARM GNU Print Size
arm-none-eabi-size --format=berkeley "01_blink_led.elf"
   text	   data	    bss	    dec	    hex	filename
    568	     12	     28	    608	    260	01_blink_led.elf
Finished building: 01_blink_led.siz
```
##Compiler flags
An arbitrary generated compiling command for the record:
```bash
Building file: ../app/main.cpp
Invoking: Cross ARM C++ Compiler
arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op  -g3 -D__STARTUP_CLEAR_BSS -D__START=main -D__NO_SYSTEM_INIT -std=c++1y -fabi-version=0 -Wctor-dtor-privacy -Wnoexcept -Wnon-virtual-dtor -Wstrict-null-sentinel -Wsign-promo -Weffc++ -MMD -MP -MF"app/main.d" -MT"app/main.o" -c -o "app/main.o" "../app/main.cpp"
Finished building: ../app/main.cpp
```
##Linker flags
The linking command for the record:
```bash
Building target: 01_blink_led.elf
Invoking: Cross ARM C++ Linker
arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -Wunused -Wuninitialized -Wall -Wextra -Wmissing-declarations -Wconversion -Wpointer-arith -Wshadow -Wlogical-op  -g3 -T "/home/alain/custom/code_public/bare_on_eclipse/01_blink_led/link/mcu/stm32f407vgtx/mem.ld" -T "/home/alain/custom/code_public/bare_on_eclipse/01_blink_led/link/mcu/arm_cortex_m4/link.ld" -Xlinker --gc-sections -L../../shared/link -Wl,-Map,"01_blink_led.map" --specs=nano.specs --specs=nosys.specs -o "01_blink_led.elf"  ./startup/mcu/arm_cortex_m4/startup.o  ./app/main.o   
Finished building target: 01_blink_led.elf
```
