# CSE1106-Final-Project
Smart Study Room Occupancy Tracker
# Smart Study Room Occupancy Tracker

CSE 1106 Final Project

Team Members:
- Aarav Raj Rana
- Olumide Olaoye

## Description
This project uses a Raspberry Pi 4 and a C program
to monitor occupancy in a university study room.

## Features
- Student entry and exit tracking
- Maximum capacity enforcement
- Room status display
- LED full-room warning
- Adjustable maximum capacity
- CSV event logging

## Hardware
- Raspberry Pi 4
- Breadboard
- LED
- 1000-ohm resistor
- Jumper wires

GPIO17 (physical pin 11) controls the LED.
GND is connected to physical pin 6.

## Compilation
gcc -Wall -pthread -o tracker src/main.c -lpigpio -lrt

## Execution
sudo ./tracker

## Menu
1. Student enters
2. Student exits
3. Change room capacity
4. Exit program
