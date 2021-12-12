# CURLY-MEMORY

Delay effect based on a PT2399 and an ESP32.

PT2399 set up like a basic delay. ESP32 controls digital pots on pin 2 and pin 6. Also allow for resistors to be placed directly on pin 2 and pin 6.
ESP32 also connected to output of pin 5 to allow the exact frequency of the delay to be measured.

INPUTS:
 - Audio in
 - Osc in for delay length (pin 6)
 - Osc in for chorus (pin 2)

OUTPUTS:
 - Audio out
 - +/-5V variable outputs (x2) (these allow the osc in inputs to be controlled without the need for an oscillator, just a patch cable connecting the two)

CONTROLS:
 - Potentiometer controls for +/-5V variable outputs

## References

https://www.electrosmash.com/pt2399-analysis
https://intellijel.com/support/eurorack-101/
