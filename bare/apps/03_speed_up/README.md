#Speed up

##Background

So far we have not touched the MCU frequency after reset. According to the
datasheet and reference manual the STM32F407VG can run at a frequency of up to
168 Mhz, but its clocking source at reset is the HSI oscillator that gives it a
frequency of 16 MHz. This is the theory. The LED blinking frequency in our
previous blinking projects tends to very roughly confirm that (I do not
currently have a scope at home, so I will satisfy myself with very rough
estimates until further notice).

Fortunately, the cube template for the STM32F4-Discovery board has a `main.c`
that includes a `SystemClock_Config()` function that as far as I understand
maximizes speeds (MCU frequency and peripheral buses), which will do for now
(there is a point in limiting frequencies from a power consumption perspective,
but we will look into that later).

For now, the purpose of this application is to do the same as the previous one,
but as fast as possible (without overclocking), and in the simplest possible
manner.

##Implementation

Since the contents of the template's `main.c` are mostly init and clock
plumbing, I think it rather belongs to a separate file, which I have renamed to
`clock_init.c`. I have also renamed the template's `main()` to `clock_init()`
and invoke it from my own `main()`. Doing this is however not enough, because
`clock_init()` invokes `HAL_Init()` which, without digging too far down in gory
details, seemed good to have. `HAL_Init()` does however set up a Systick timer
that increases a global counter every 1 ms. I do not really need it right now,
but I did not feel like cutting what seems like standard HAL functionality, and
it does not feel that disturbing. For that timer to work, I of course need to
provide an interrupt handler. That is solved in the template in a file named
`stm32f4xx_it.c`, which I also included for this application.

That, the corresponding header files, an `#include clock_init.h` in my `main.c`,
and I just have to invoke `clock_init()` in `main()` to multiply blinking
frequency by 10 or so :-).
