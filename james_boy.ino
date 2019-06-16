
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "loading_screen_map.h"
#include "menu_screen_map.h"

// https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives
// http://marlinfw.org/tools/u8glib/converter.html

char selectGame = 'a';  // Key to steer left
char selectSetup = 's'; // Key to steer right

enum states {
    START,
    MENU,
    SETUP,
    GAME,
} state;

states currentState = MENU;

enum events {
    START_INIT,
    HIGHLIGHT_GAME_MODE,
    HIGHLIGHT_SETUP_MODE,
    SELECT_MODE,
    SETUP_MODE,
    GAME_MODE
};

void step_state(enum events event) {
    switch(currentState) {
    case START:
        // run intro sequence here
        break;
    case MENU:
        switch(event) {
        case HIGHLIGHT_GAME_MODE:
            select(games_text_X, games_text_Y, games_text_BMPWIDTH, games_text_BMPHEIGHT);
            clearSelect(setup_text_X, setup_text_Y, setup_text_BMPWIDTH, setup_text_BMPHEIGHT);
            break;
        case HIGHLIGHT_SETUP_MODE:
            select(setup_text_X, setup_text_Y, setup_text_BMPWIDTH, setup_text_BMPHEIGHT);
            clearSelect(games_text_X, games_text_Y, games_text_BMPWIDTH, games_text_BMPHEIGHT);
            break;
        case SELECT_MODE:
            printf("Highlight Selection");
//            state = X; - Change state to new view
            break;
        }
    }
}

#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);

#define DELTAY 2

#define XPOS 0
#define YPOS 0

#if (SSD1306_LCDHEIGHT != 32)
#error("Height incorrect, please fix Adafruit_SSD1306.h!");
#endif

#define SIZE 200

void setup()
{
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3C (for the 128x32)
  // init done

  // Clear the buffer.
  display.clearDisplay();

  // Intro Sequence.
  delay(200);
  display.clearDisplay();
  animateStars(stars_bmp, starsh, starsw);
  display.display();
  delay(200);
  display.clearDisplay();
  animateStars(stars_bmp, starsh, starsw);
  display.display();
  delay(200);
  display.clearDisplay();
  animateStars(stars_bmp, starsh, starsw);
  display.display();
  delay(200);
  display.clearDisplay();
  animateStars(stars_bmp, starsh, starsw);
  display.display();
  delay(200);
  display.clearDisplay();
  animateStars(stars_bmp, starsh, starsw);
  display.display();
  delay(200);
  display.clearDisplay();
  animateStars(stars_bmp, starsh, starsw);
  display.display();
  delay(200);
  display.clearDisplay();
  animateStars(stars_bmp, starsh, starsw);
  drawBitmap(0, 0, james_boy_logo, CISWZT_BMPWIDTH, CISWZT_BMPHEIGHT);
  display.display();
  delay(200);
  display.clearDisplay();
  animateStars(stars_bmp, starsh, starsw);
  drawBitmap(0, 0, james_boy_logo, CISWZT_BMPWIDTH, CISWZT_BMPHEIGHT);
  display.display();
  delay(200);
  display.clearDisplay();
  animateStars(stars_bmp, starsh, starsw);
  drawBitmap(0, 0, james_boy_logo, CISWZT_BMPWIDTH, CISWZT_BMPHEIGHT);
  display.display();
  delay(200);
  display.clearDisplay();
  animateStars(stars_bmp, starsh, starsw);
  drawBitmap(0, 0, james_boy_logo, CISWZT_BMPWIDTH, CISWZT_BMPHEIGHT);
  display.display();
  delay(200);
  display.clearDisplay();
  animateStars(stars_bmp, starsh, starsw);
  drawBitmap(0, 0, james_boy_logo, CISWZT_BMPWIDTH, CISWZT_BMPHEIGHT);
  display.display();
  delay(200);
  display.clearDisplay();
  animateStars(stars_bmp, starsh, starsw);
  drawBitmap(0, 0, james_boy_logo, CISWZT_BMPWIDTH, CISWZT_BMPHEIGHT);
  display.display();
  delay(200);
  display.clearDisplay();
  animateStars(stars_bmp, starsh, starsw);
  drawBitmap(0, 0, james_boy_logo, CISWZT_BMPWIDTH, CISWZT_BMPHEIGHT);
  display.display();
  delay(200);
  display.clearDisplay();
  animateStars(stars_bmp, starsh, starsw);
  drawBitmap(0, 0, james_boy_logo, CISWZT_BMPWIDTH, CISWZT_BMPHEIGHT);
  display.display();
  delay(200);
  display.clearDisplay();
  animateStars(stars_bmp, starsh, starsw);
  display.display();
  delay(200);
  display.clearDisplay();
  animateStars(stars_bmp, starsh, starsw);
  display.display();
  delay(200);
  display.clearDisplay();
  animateStars(stars_bmp, starsh, starsw);
  display.display();
  delay(200);
  display.clearDisplay();
  animateStars(stars_bmp, starsh, starsw);
  display.display();
  delay(200);
  display.clearDisplay();
  animateStars(stars_bmp, starsh, starsw);
  display.display();
  delay(200);
  display.clearDisplay();
  display.display();
  drawBitmap(45, 1, menu_title, menu_title_BMPWIDTH, menu_title_BMPHEIGHT);
  drawBitmap(games_text_X, games_text_Y, games_text, games_text_BMPWIDTH, games_text_BMPHEIGHT);
  drawBitmap(setup_text_X, setup_text_Y, setup_text, setup_text_BMPWIDTH, setup_text_BMPHEIGHT);
  display.display();
}



// Games or Setup
void select(short int start_x, short int start_y, short int width, short int height)
{
  short int selectLineY = start_y + height + 2;
  short int selectLineEndX = start_x + width;
  // display.drawLine from x, from y, tox, toy, colour.
  display.drawLine(start_x, selectLineY, selectLineEndX, selectLineY, WHITE);
  display.display();
}
void clearSelect(short int start_x, short int start_y, short int width, short int height)
{
  short int selectLineY = start_y + height + 2;
  short int selectLineEndX = start_x + width;
  // display.drawLine from x, from y, tox, toy, colour.
  display.drawLine(start_x, selectLineY, selectLineEndX, selectLineY, BLACK);
  display.display();
}

void loop()
{
 if (Serial.available()) {  // Returns true if there is serial input.
    char ch = Serial.read();
    if (ch == selectGame) {
      step_state(HIGHLIGHT_GAME_MODE);
      Serial.write("Game");
    }
    if (ch == selectSetup) {
      step_state(HIGHLIGHT_SETUP_MODE);
      Serial.write("Setup");
    }
  }
}

void animateStars(const uint8_t *bitmap, uint8_t w, uint8_t h)
{
  for (uint8_t f = 0; f < 100; f++)
  {
    int x = random(display.width());
    int y = random(display.height());
    display.drawPixel(x, y, WHITE);
  }
}

// draws bitmap exactly as defined
void drawBitmap(uint8_t xpos, uint8_t ypos, const uint8_t *bitmap, uint8_t w, uint8_t h)
{
  display.drawBitmap(xpos, ypos, bitmap, w, h, WHITE);
  display.display();
}

