snooze-coffee
=============

[![schematics](https://raw.github.com/hezhao/snooze-coffee/master/schematics-small.jpg)](https://raw.github.com/hezhao/snooze-coffee/master/schematics.jpg)

Notes
=====
* Sony Dream Machine MCU - UTC LM8560 uses 10VAC, which is not suitable to power Arduino Pro Mini. The final product uses a 120VAC-5VDC USB adapter.
* LM8560 Alarm Output is 900Hz 10V AC signal, a voltage divider is used to convert 10V to 5V logic level. Transistor level converter circuit wouldn't work since it is AC signal.
* Low pass filter may be used to smooth the alarm output AC signal from UT LM8560 to to a rough DC signal. 
