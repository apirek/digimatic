# Digimatic USB-Adaptor
Read out Mitutoyo measuring instruments via USB.

## Usage
The adaptor presents itself as a serial device to the computer.
Any input (e.g. newline) requests a measurement.
The measured value is output as a decimal number with `.` (dot) separator in the unit of measurement of the instrument, followed by a newline.
Errors are reported on lines starting with `#` (hash).

## Build
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
