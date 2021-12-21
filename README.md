# CURLY-MEMORY

Open source delay effect based on a PT2399 using an ESP32.

ESP32 acts like PT2399, takes audio in via ADC, outputs audio with delay via DAC.

INPUTS:
 - Audio in
 - Osc in for delay length
 - Osc in for feedback

OUTPUTS:
 - Audio out
 - +/-5V variable outputs (x2) (these allow the osc in inputs to be controlled without the need for an oscillator, just a patch cable connecting the two)

CONTROLS:
 - Potentiometer controls for +/-5V variable outputs

## References

- https://www.electrosmash.com/pt2399-analysis
- https://intellijel.com/support/eurorack-101/
- https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/spi_master.html
