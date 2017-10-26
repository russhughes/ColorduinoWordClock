/*

    WORD CLOCK - 8x8 Colorduino Desktop Edition
    Hacked up by Russ Hughes

    Adapted and Remixed from:

    WORD CLOCK - 8x8 NeoPixel Desktop Edition
    by Andy Doro

    Hardware:

    - Colorduino
    - Tripple Color RGB common Anode Display
    - DS3231 RTC breakout
    - Two pcb mount push buttons & tiny PC board

    Software:

    This code requires the following libraries:
 	ColorDuino Library from https://github.com/lincomatic/Colorduino/archive/master.zip
 	Adarfruit RTClib from https://github.com/adafruit/RTClib/archive/master.zip		

    A word clock using a Colorduino and 8x8 RGB LEDs for a color shift effect.

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

*/

// include the library code:
#include <SPI.h>
#include <Wire.h>
#include <RTClib.h>
#include <Colorduino.h>

// define masks for each word. we add them with "bitwise or" to generate a mask for the entire "phrase".
// have to use two different 32-bits numbers, luckily none of the words are spread across top and bottom halves of the NeoMatrix.

#define MFIVE topMask |= 0xF000        // these are in hexadecimal
#define MTEN topMask |= 0x58000000
#define AQUARTER topMask |= 0x80FE0000
#define TWENTY topMask |= 0x7E000000
#define HALF topMask |= 0xF00
#define PAST topMask |= 0x78
#define TO topMask |= 0xC
#define ONE bottomMask |= 0x43
#define TWO bottomMask |= 0xC040
#define THREE bottomMask |= 0x1F0000
#define FOUR bottomMask |= 0xF0
#define FIVE bottomMask |= 0xF0000000
#define SIX bottomMask |= 0xE00000
#define SEVEN bottomMask |= 0x800F00
#define EIGHT bottomMask |= 0x1F000000
#define NINE bottomMask |= 0xF
#define TEN bottomMask |= 0x1010100
#define ELEVEN bottomMask |= 0x3F00
#define TWELVE bottomMask |= 0xF600
#define ANDYDORO topMask |= 0x89010087

// define delays

#define SHIFTDELAY 100	// controls color shifting speed

// define pins for time adjust buttons

#define HOURPIN 0
#define MINPIN 1

// Globals

unsigned long long topMask;			// 64-bits is too big!
unsigned long bottomMask;			// use two 32-bit numbers to create masks.

RTC_DS3231 RTC; 					// Clock object
DateTime thetime; 					// Current clock time

unsigned long currentMillis;		// used for delay
unsigned long previousMillis = 0;	// used for delay

unsigned char whiteBalVal[3] = {36, 63, 63}; 			// for LEDSEE 6x6cm round matrix

int j;   // integer for the color shifting effect

void setup() {

    // time setting pins
    pinMode(HOURPIN, INPUT_PULLUP);
    pinMode(MINPIN, INPUT_PULLUP);

    // start clock
    Wire.begin();
    RTC.begin();

    // if the rtc lost power set the date & time
    if (RTC.lostPower()) {
        RTC.adjust(DateTime("Dec 31 2016", "12:00:00"));
    }

    Colorduino.Init(); 						// initialize the board
    Colorduino.SetWhiteBal(whiteBalVal);	// Correct white balance
    rainbowCycle(1);						// Show a rainbow of colors on powerup
}

void loop() {

    thetime = RTC.now();

    if (digitalRead(HOURPIN) == LOW)  {
        while (digitalRead(HOURPIN) == LOW)
            ;

        RTC.adjust(thetime + TimeSpan(0, 1, 0, 0));
    }

    if (digitalRead(MINPIN) == LOW)  {
        while (digitalRead(MINPIN) == LOW)
            ;

        RTC.adjust(thetime + TimeSpan(0, 0, 1, 0));
    }

    displayTime();
}

