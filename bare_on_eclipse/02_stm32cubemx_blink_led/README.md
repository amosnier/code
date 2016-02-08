#"Blink LED" program based on STM32CubeMX
Procedure:
- Standard project for STM32F4-Discovery generated from STM32CubeMX with the
following options:
  - Toolchain SW4STM32
  - Copy only the necessary library files
  - Generate peripheral initialization
- [GNU ARM Eclipse](http://GNU ARM Eclipse) project generated for STM32F4xx.
All files are then removed.
- Files for the CubeMX project are then added manually under a custom file
structure and the compiler and linker flags are also adpated manually.

##Binary size
```bash
Invoking: Cross ARM GNU Print Size
arm-none-eabi-size --format=berkeley "02_stm32cubemx_blink_led.elf"
   text	   data	    bss	    dec	    hex	filename
   4068	     12	   1572	   5652	   1614	02_stm32cubemx_blink_led.elf
Finished building: 02_stm32cubemx_blink_led.siz
```
##Compiler flags
An arbitrary generated compiling command for the record:
```bash
Building file: ../application/main.c
Invoking: Cross ARM C Compiler
arm-none-eabi-gcc -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -DSTM32F407xx -DUSE_HAL_DRIVER -I"/home/alain/custom/code_public/bare_on_eclipse/02_stm32cubemx_blink_led/application/headers" -I"/home/alain/custom/code_public/bare_on_eclipse/02_stm32cubemx_blink_led/drivers/CMSIS/Device/ST/STM32F4xx/Include" -I"/home/alain/custom/code_public/bare_on_eclipse/02_stm32cubemx_blink_led/drivers/STM32F4xx_HAL_Driver/Inc/Legacy" -I"/home/alain/custom/code_public/bare_on_eclipse/02_stm32cubemx_blink_led/drivers/STM32F4xx_HAL_Driver/Inc" -I"/home/alain/custom/code_public/bare_on_eclipse/02_stm32cubemx_blink_led/drivers/CMSIS/Include" -std=gnu11 -MMD -MP -MF"application/main.d" -MT"application/main.o" -c -o "application/main.o" "../application/main.c"
Finished building: ../application/main.c
```
##Linker flags
The linking command for the record:
```bash
Building target: 02_stm32cubemx_blink_led.elf
Invoking: Cross ARM C++ Linker
arm-none-eabi-g++ -mcpu=cortex-m4 -mthumb -mfloat-abi=soft -Og -fmessage-length=0 -fsigned-char -ffunction-sections -fdata-sections -ffreestanding -fno-move-loop-invariants -Wall -Wextra  -g3 -T STM32F407VGTx_FLASH.ld -Xlinker --gc-sections -L"/home/alain/custom/code_public/bare_on_eclipse/02_stm32cubemx_blink_led/link" -Wl,-Map,"02_stm32cubemx_blink_led.map" --specs=nano.specs -specs=nosys.specs -o "02_stm32cubemx_blink_led.elf"  ./drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal.o ./drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_cortex.o ./drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma.o ./drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_dma_ex.o ./drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash.o ./drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ex.o ./drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_flash_ramfunc.o ./drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_gpio.o ./drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr.o ./drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_pwr_ex.o ./drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc.o ./drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rcc_ex.o ./drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc.o ./drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_rtc_ex.o ./drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim.o ./drivers/STM32F4xx_HAL_Driver/Src/stm32f4xx_hal_tim_ex.o  ./drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/gcc/startup_stm32f407xx.o  ./drivers/CMSIS/Device/ST/STM32F4xx/Source/Templates/system_stm32f4xx.o  ./application/gpio.o ./application/main.o ./application/stm32f4xx_hal_msp.o ./application/stm32f4xx_it.o   
Finished building target: 02_stm32cubemx_blink_led.elf
```
