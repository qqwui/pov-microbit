# Microbit Persistance of Vision display
This is a thing I made for SMRRF 2026. You basically wave it, and it displays a message. See https://hackaday.com/2019/10/29/the-basics-of-persistence-of-vision-projects/ for more info.

## How to run
This project was made using the Arduino IDE. Both the 2.0 and 1.9 version should work, but i used the 1.9 legacy version. I've programmed it for the microbit v2; you'll need to make some changes for the ROW and COL pins as well as redoing `output_cols()` if you want to use the v1. Some v1 variants have a separate magnetometer and accelerometer so you'll have to use the MMA8653 library.

The following instructions are paraphrased from https://learn.adafruit.com/use-micro-bit-with-arduino/overview

1. Download the board support pack. Paste https://sandeepmistry.github.io/arduino-nRF5/package_nRF5_boards_index.json into the Additional Board Manager URL text box in Preferences.
2. Install the board. Install "Nordic Semiconductor nRF5 Boards" in the board manager
  - The toolchain is 32 bit only, so if you get a "not found" error when compiling on an x86_64 pc, you'll need to install 32 bit libraries.
3. Install the accelerometer library by searching LSM303AGR and installing the one from STM32duino. 
