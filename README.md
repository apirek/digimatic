# Digimatic USB-Adaptor
Read out Mitutoyo measuring instruments via USB.

Tested with ID-SX2 indicator.

## Usage
The adaptor presents itself as a serial device to the computer.
Any input (e.g. newline) requests a measurement.
The measured value is output as a decimal number with `.` (dot) separator in the unit of measurement of the instrument, followed by a newline.
Errors are reported on lines starting with `#` (hash).

## Wiring
A wiring diagram can be found [here](schematics/Digimatic%20USB%20Adaptor.pdf).

The DATA and CK signals are connected directly to GPIOs.
The REQ signal is switched to ground with a NPN transistor.

The connector of the Digimatic data cables fits Molex 70246 series or 2.54 mm headers.
Looking at the connector of the cable face-on with the key up, pos. 1 is top left and pos. 2 is below, bottom left.

## Build
The Pico C SDK and TinyUSB are required and included as Git submodules.
Git submodules may need to be initialized after a clone:
```sh
git submodule update --init --recursive
```

Build with CMake:
```sh
mkdir src/build
cd src/build
cmake ..
make

## Flash binary by copying via USB
# cp digimatic.uf2 ~/media/RPI-RP2
## OR flash binary with OpenOCD
# openocd -f interface/cmsis-dap.cfg -f target/rp2040.cfg -c "adapter speed 5000" -c "program digimatic.elf verify reset exit"
```

## References
* https://forum.arduino.cc/t/mitutoyo-digimatic-spc/78312 and https://github.com/Roger-random/mitutoyo for a general understanding of the protocol and interface.
* Mitutoyo manual no. 99MAH059D1 for technical description and connector pinout.
