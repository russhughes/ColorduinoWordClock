# WORD CLOCK - 8x8 Colorduino Desktop Edition
I Hacked up, Adapted and Remixed from WORD CLOCK - 8x8 NeoPixel Desktop Edition by Andy Doro 

WORD CLOCK - 8x8 NeoPixel Desktop Edition by Andy Doro

## Hardware:

- Colorduino
- Tripple Color RGB common Anode Display
- DS3231 RTC breakout
- Two pcb mount push buttons & tiny PC board

## Software:

This code requires the following libraries:  
- ColorDuino Library from https://github.com/lincomatic/Colorduino/archive/master.zip  
- Adarfruit RTClib from https://github.com/adafruit/RTClib/archive/master.zip  		

## Wiring:

Connect the RTC module to the SCA, SCL, GND and VDD pins on the Colorduino  
Connect one pin of a push button to RXD on the Colorduino and the other to GND to adjust the hours   
Connect one pin of a push button to TXD on the Colorduino and the other to GND to adjuet the minutes  

## Acknowledgements:
- Thanks Dano for faceplate / 3D models & project inspiration!
- Thanks Andy Doro for his NeoPixel Word Clock
- Thanks Sam C. Lin <lincomatic@hotmail.com> for the Colorduino Library
