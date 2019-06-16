
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// SYSTEM Bitmaps
#include "loading_screen_map.h"
#include "menu_screen_map.h"
#include "game_screen_map.h"
#include "setup_screen_map.h"
#include "ui_map.h"

// GAME Bitmaps
#include "games/maze_xy/maze_xy_map.h"

// Games
// ...

// https://learn.adafruit.com/adafruit-gfx-graphics-library/graphics-primitives
// http://marlinfw.org/tools/u8glib/converter.html

// TODO move states and events to a header file.
enum states
{
  START,
  MENU,
  SETUP,
  GAME,
} state;

enum events
{
  START_INIT,
  HIGHLIGHT_GAME_MODE,
  HIGHLIGHT_SETUP_MODE,
  SELECT_MODE,
  HIGHLIGHT_GAME,
  HIGHLIGHT_BACK_BUTTON,
  SETUP_MODE,
  GAME_MODE
};

states currentState;
events currentEvent;

short int screen_width = 128;
short int screen_height = 32;

// Tech debt... This shouldn't be globally scoped.
short int maze_xy_x;

void stateController(enum events event)
{
  switch (currentState)
  {
  case START:
    // run intro sequence here
    break;
  case MENU:
    switch (event)
    {
    case HIGHLIGHT_GAME_MODE:
      select(games_text_X, games_text_Y, games_text_BMPWIDTH, games_text_BMPHEIGHT);
      clearSelect(setup_text_X, setup_text_Y, setup_text_BMPWIDTH, setup_text_BMPHEIGHT);
      break;
    case HIGHLIGHT_SETUP_MODE:
      select(setup_text_X, setup_text_Y, setup_text_BMPWIDTH, setup_text_BMPHEIGHT);
      clearSelect(games_text_X, games_text_Y, games_text_BMPWIDTH, games_text_BMPHEIGHT);
      break;
    case SELECT_MODE:
      if (currentEvent == HIGHLIGHT_GAME_MODE)
      {
        gamesView();
        setState(GAME);
      }
      if (currentEvent == HIGHLIGHT_SETUP_MODE)
      {
        setupView();
        setState(SETUP);
      }
      break;
    }
  case GAME:
    switch (event)
    {
    case HIGHLIGHT_BACK_BUTTON:
      select(0, 1, arrow_back_BMPWIDTH, arrow_back_BMPHEIGHT);
      clearSelect(maze_xy_x, 20, maze_xy_BMPWIDTH, maze_xy_BMPHEIGHT);
      break;
    case HIGHLIGHT_GAME:
      select(maze_xy_x, 20, maze_xy_BMPWIDTH, maze_xy_BMPHEIGHT);
      clearSelect(games_text_X, games_text_Y, games_text_BMPWIDTH, games_text_BMPHEIGHT);
      break;
    }
    break;
  }
  setEvent(event);
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
const int SW_pin = 8; // digital pin connected to switch output

void setup()
{
  Serial.begin(9600);

  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3C (for the 128x32)
  // init done

  // Clear the buffer.
  display.clearDisplay();

  // Dev Testing - Views TODO - Create a View Controller class
  // to handle the view based on state.

  // Show Intro
  // states currentState = START;
  // events currentEvent = START_INIT;
  // intro();

  // Show Menu
  setState(MENU);
  menuView();
}

void intro()
{
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
  setState(MENU);
}

void setState(states _state)
{
  currentState = _state;
}

void setEvent(events _event)
{
  currentEvent = _event;
}

int getCenter(int dimensionLength, int itemLength)
{
  return (dimensionLength - itemLength) / 2;
}

void menuView()
{
  display.clearDisplay();
  drawBitmap(45, 1, menu_title, menu_title_BMPWIDTH, menu_title_BMPHEIGHT);
  drawBitmap(games_text_X, games_text_Y, games_text, games_text_BMPWIDTH, games_text_BMPHEIGHT);
  drawBitmap(setup_text_X, setup_text_Y, setup_text, setup_text_BMPWIDTH, setup_text_BMPHEIGHT);
  select(games_text_X, games_text_Y, games_text_BMPWIDTH, games_text_BMPHEIGHT);
  display.display();
}

void gamesView()
{
  display.clearDisplay();
  short int game_title_x = getCenter(screen_width, game_title_BMPWIDTH);
  short int maze_xy_x = getCenter(screen_width, maze_xy_BMPWIDTH);
  drawBitmap(game_title_x, 1, game_title, game_title_BMPWIDTH, game_title_BMPHEIGHT);
  drawBitmap(0, 1, arrow_back, arrow_back_BMPWIDTH, arrow_back_BMPHEIGHT);
  drawBitmap(maze_xy_x, 20, maze_xy, maze_xy_BMPWIDTH, maze_xy_BMPHEIGHT);
  display.display();
}

void setupView()
{
  display.clearDisplay();
  drawBitmap(64 - setup_title_BMPWIDTH / 2, 1, setup_title, setup_title_BMPWIDTH, setup_title_BMPHEIGHT);
  drawBitmap(0, 1, arrow_back, arrow_back_BMPWIDTH, arrow_back_BMPHEIGHT);
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

int value = 0;

void loop()
{

  // MENU STATE Event Handling. TODO Move to a controller that considers state.
  if (currentState == MENU)
  {
    if (analogRead(A0) < 10)
    {
      Serial.print("GAME MODE");
      stateController(HIGHLIGHT_GAME_MODE);
    }
    if (analogRead(A0) > 1013)
    {
      Serial.print("SETUP MODE");
      stateController(HIGHLIGHT_SETUP_MODE);
    }
    if (digitalRead(SW_pin) == 0)
    {
      stateController(SELECT_MODE);
    }
  }
  if (currentState == GAME_MODE)
  {
    if (analogRead(A0) < 10) // Back
    {
      Serial.print("HIGHLIGHT_BACK_BUTTON");
      stateController(HIGHLIGHT_BACK_BUTTON);
    }
    if (analogRead(A0) > 1013) // Game
    {
      Serial.print("HIGHLIGHT_GAME");
      stateController(HIGHLIGHT_GAME);
    }
    if (digitalRead(SW_pin) == 0)
    {
      stateController(SELECT_MODE);
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
