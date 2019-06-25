# james_boy

A retro arcade system prototype.

#### Dev notes Mac:

Compile Cpp on mac:
1. Create cpp file / project
2. run file make
3. run ./file

#### Board Setup:

1. PINS JOYSTICK:
   GND - GND / 5 = 5 / VRX = A0 / VRY = A1 / SW = 8

2. PINS SCREEN:
   SDA = A4 / SCL = A5 / VCC = 5 / GND = GND

// Deprcated code that maybe useful.

// Left Arrow.
drawBitmap(0, 1, arrow_back, arrow_back_BMPWIDTH, arrow_back_BMPHEIGHT);

#### References:

https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives
http://marlinfw.org/tools/u8glib/converter.html