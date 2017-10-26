
void SetPixelXY(byte x, byte y, uint32_t color) {
    color = (color & 0x00FFFFFF);
    byte b = (color & 0x0000FF); 	//channel Blue
    color = (color >> 8);
    byte g  = (color & 0x0000FF); 	//channel Green
    color = (color >> 8);
    byte r = (color & 0x0000FF); 	//channel Red

    Colorduino.SetPixel(x, y, r, g, b);
}

void SetPixel(byte i, uint32_t color) {

    byte x = 7 - (i % 8);
    byte y = (i / 8);

    SetPixelXY(x, y, color);
}

// show colorshift through the phrase mask. for each pixel either show a color or show nothing!

void applyMask() {

    // top mask
    for (byte i = 0; i < 32; i++) {
        if (bitRead(topMask, 31 - i)) 	// bitread is backwards because bitRead reads rightmost digits first. could have defined the word masks differently to avoid this but whatever.
            SetPixel(i, Wheel(((i * 4) + j) & 255) );
        else
            SetPixel(i, 0);
    }

    // bottom mask
    for (byte i = 32; i < 64; i++) {
        if (bitRead(bottomMask, 63 - i))
            SetPixel(i, Wheel(((i * 4) + j) & 255) );
        else
            SetPixel(i, 0);
    }

    Colorduino.FlipPage();

    currentMillis = millis();
    while ((currentMillis - previousMillis) < SHIFTDELAY)
        currentMillis = millis();
    previousMillis = currentMillis;

    j++; // move the colors forward
    j = j % (256 * 5);

    // reset masks for next time
    topMask = 0;
    bottomMask = 0;
}

// Input a value 0 to 255 to get a color value.
// The colours are a transition r - g - b - back to r.

uint32_t Wheel(byte WheelPos) {
    WheelPos = 255 - WheelPos;
    if (WheelPos < 85) {
        return Color(255 - WheelPos * 3, 0, WheelPos * 3);
    } else if (WheelPos < 170) {
        WheelPos -= 85;
        return Color(0, WheelPos * 3, 255 - WheelPos * 3);
    } else {
        WheelPos -= 170;
        return Color(WheelPos * 3, 255 - WheelPos * 3, 0);
    }
}

// Slightly different, this makes the rainbow equally distributed throughout
void rainbowCycle(uint8_t wait) {
    uint16_t i, j;

    for (j = 0; j < 256 * 5; j++) { // 5 cycles of all colors on wheel
        for (i = 0; i < 64; i++) {
            SetPixelXY(i / 8, i % 8, Wheel(((i * 256 / 64) + j) & 255));
        }
        Colorduino.FlipPage();
        delay(wait);
    }
}

uint32_t Color(uint8_t r, uint8_t g, uint8_t b) {
    return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b;
}

