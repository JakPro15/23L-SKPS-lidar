### lidar

This project contains software for a simple lidar for Raspberry Pi platform, made of a servomechanism and a
time-of-flight distance sensor.
The `lidar` directory contains the main program handling hardware components as an OpenWRT package.
Raspberry Pi sends measurement data over to a PC, which
displays it using the program contained in `zadanie_domowe/visual`.
There is also a program simulating the Raspberry Pi part of the project in `zadanie_domowe/synthetic_data_generator`.

The project is written in C, using SDL2 library for visualization and minor libraries for handling
hardware components.

More detailed documentation is available in Polish in the file
`Dokumentacja_projekt.pdf`.
