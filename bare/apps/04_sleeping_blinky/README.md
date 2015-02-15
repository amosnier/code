#Sleeping blinky

##Background

The previous application was a busy waiting blinky application. As showed
[here](https://www.youtube.com/watch?v=nNzC8n989tg), the current draw was around
75 mA when the LED was unlit, and around 85 mA when it was lit. The purpose of
this application is to base the LED toggling on timer interrupts instead of busy
waiting, and to let the processor sleep between interrupts. We will then measure
the current draw again. Hopefully, it will be much lower.
