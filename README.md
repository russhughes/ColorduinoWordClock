# WORD CLOCK - 8x8 Colorduino Desktop Edition
Hacked up by Russ Hughes

Adapted and Remixed from:
WORD CLOCK - 8x8 NeoPixel Desktop Edition by Andy Doro

Hardware:

- Colorduino
- Tripple Color RGB common Anode Display
- DS3231 RTC breakout
- Two pcb mount push buttons & tiny PC board

Software:

This code requires the following libraries:  
- ColorDuino Library from https://github.com/lincomatic/Colorduino/archive/master.zip  
- Adarfruit RTClib from https://github.com/adafruit/RTClib/archive/master.zip  		

    grid pattern

    A T W E N T Y D
    Q U A R T E R Y
    F I V E H A L F
    D P A S T O R O
    F I V E I G H T
    S I X T H R E E
    T W E L E V E N
    F O U R N I N E

Acknowledgements:
- Thanks Dano for faceplate / 3D models & project inspiration!
- Thanks Andy Doro for his NeoPixel Word Clock
- Thanks Sam C. Lin <lincomatic@hotmail.com> for the Colorduino Library

Hardware:

Connect the RTC module to the SCA, SCL, GND and VDD pins on the Colorduino  
Connect one pin of a push button to RXD on the Colorduino and the other to GND to adjust the hours   
Connect one pin of a push button to TXD on the Colorduino and the other to GND to adjuet the minutes  
	
	
