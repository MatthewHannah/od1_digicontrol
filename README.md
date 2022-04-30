# OD-1 knock-off Control Program

This project contains an MBED program to provide digital control of the OD-1 knock off circuit in [this schematic](schematic_print.pdf).

The main digital control is through an MCP4151 digipot that is controlled via SPI. An additional volume control could be controlled digitally
by replacing RV1 with another MCP4151, but I had issues with audio frequency oscillations in the circuit after adding another.

The skeleton in main.cpp uses buttons inputs that are unlisted in the schematic, but any digital control of the MBED can be substituted to set the MCP4151 wiper settings.