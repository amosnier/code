shell openocd -f board/stm32f4discovery.cfg > /dev/null 2>&1 &
target remote localhost:3333
