# CURLY-MEMORY

Open source eurorack hardware using an ESP32.

ESP32 acts like anything you want, just reprogram with new firmware.

## Features

### INPUTS:
 - Analogue input x4
  - 1/8" jack x3 (IN0, IN1, IN2)
  - 2.54mm pin header x2 (IN2, IN3)

### OUTPUTS:
 - Analogue output x4
  - 1/8" jack x3 (OUT0, OUT1, OUT2)
  - 2.54mm pin header x3 (OUT2, OUT3)

### CONTROLS:
 - Potentiometer input x4
 - Tactile switch x2

### OTHER:
 - Feedback resistor (digital pot connecting OUT0 to IN0)
 - Digital pot output on 2.54mm pin header
 - Dry/wet mixer (IN0 + OUT0 - connecting to digital pot)
 - WS2812B LEDs x2

### POWER:
 - Eurorack standard 10 pin IDC connector
 - 12V input

### FIRMWARE:
 - ESP-IDF or Arduino

## Images

!(main-cad)[resources/pcb-stackup-cad-front.png]

## References

- https://www.electrosmash.com/pt2399-analysis
- https://intellijel.com/support/eurorack-101/
- https://docs.espressif.com/projects/esp-idf/en/latest/esp32/api-reference/peripherals/spi_master.html

## Influences

- https://ornament-and-cri.me/
