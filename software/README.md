# Firmware

Firmware runs on an esp32. The firmware is open source and can be modified to change the functionality.

## Installation and Usage

- Clone this repo
- Install esp-idf to compile
- Run ~/esp/esp-idf/export.sh to import the idf tools to the command line
- Run idf.py build to build the code

Follow the steps on ['ESP-IDF Get Started'](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/get-started/index.html#installation-step-by-step) to install the esp-idf which is used to compile.

## Troubleshooting

#### Installing esp-idf on macos

Only version that worked was 'release/v4.2' to get this run the following commands:
$ git checkout --track origin/release/v4.2
$ git submodule update --recursive

#### USB device not showing up on macos

- Install CP2102 driver from https://www.silabs.com/developers/usb-to-uart-bridge-vcp-drivers
- During install it request to 'Open Security and Privacy', open it and click the lock in the bottom left, then click allow where it says that VCP driver is requesting to make changes


# Licence
For licence see main readme
