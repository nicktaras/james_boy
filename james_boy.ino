
//        _|    _|_|    _|      _|  _|_|_|_|    _|_|_|  _|_|_|      _|_|    _|      _|
//        _|  _|    _|  _|_|  _|_|  _|        _|        _|    _|  _|    _|    _|  _|
//        _|  _|_|_|_|  _|  _|  _|  _|_|_|      _|_|    _|_|_|    _|    _|      _|
//  _|    _|  _|    _|  _|      _|  _|              _|  _|    _|  _|    _|      _|
//    _|_|    _|    _|  _|      _|  _|_|_|_|  _|_|_|    _|_|_|      _|_|        _|

// James Boy 2019. Entertainment games system.
// The core design of this code is to independantly:
// A. Boot up games upon Selection
// B. Enable some core device settings
// C. Save user preferences

// The Inter-integrated Circuit (I2C) Protocol is a protocol
// intended to allow multiple "slave" digital integrated circuits
// ("chips") to communicate with one or more "master" chips
// Adafruit_SSD1306 library enables the application of graphics via the I2C protocol.
#include <Adafruit_SSD1306.h>
// Enables some of the core features within C, to perform various input and output methods such as print.
#include <stdio.h>
// Enables the use of the many variable types such as short int.
#include <stdlib.h>
// Assists with various input and output types, including the infamous NULL pointer.
#include <unistd.h>

// SYSTEM Bitmap Graphics.
#include "loading_screen_map.h"
#include "menu_screen_map.h"
#include "game_screen_map.h"
#include "setup_screen_map.h"
#include "ui_map.h"

// Game Height and Width settings.
// Exposes two public variables: screen_width, screen_height.
#include "system_display_config.h";

// GAME Bitmaps.
#include "games/maze_xy/maze_xy_map.h"
#include "games/quiz_num/quiz_num_map.h"

// Games Array Loader. Should look up all games. TODO.
// Define Game Index as 0 on init.
// Selection of Games live inside the publically defined games array.
int currentGameIndex = 0;
char *games[2] = {maze_xy, quiz_num};

// All Game System States.
#include "states.h";
states currentState;

// All Game System Events.
#include "events.h";
events currentEvent;

void stateController(enum events event)
{
  switch (currentState)
  {
  case START:
    intro();
    break;
  case MENU:
    switch (event)
    {
    case MAIN_MENU:
      menuView();
      break;
    case HIGHLIGHT_GAME_MENU:
      select(games_text_X, games_text_Y, games_text_BMPWIDTH, games_text_BMPHEIGHT);
      clearSelect(setup_text_X, setup_text_Y, setup_text_BMPWIDTH, setup_text_BMPHEIGHT);
      break;
    case HIGHLIGHT_SETUP_MENU:
      select(setup_text_X, setup_text_Y, setup_text_BMPWIDTH, setup_text_BMPHEIGHT);
      clearSelect(games_text_X, games_text_Y, games_text_BMPWIDTH, games_text_BMPHEIGHT);
      break;
    case SELECT_MODE:
      if (currentEvent == HIGHLIGHT_GAME_MENU)
      {
        gamesView();
        setState(GAME);
      }
      if (currentEvent == HIGHLIGHT_SETUP_MENU)
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
      //select(0, 1, arrow_back_BMPWIDTH, arrow_back_BMPHEIGHT);
      //clearSelect(maze_xy_x, 20, maze_xy_BMPWIDTH, maze_xy_BMPHEIGHT);
      break;
    case HIGHLIGHT_GAME:
      //select(maze_xy_x, 20, maze_xy_BMPWIDTH, maze_xy_BMPHEIGHT);
      //clearSelect(games_text_X, games_text_Y, games_text_BMPWIDTH, games_text_BMPHEIGHT);
      break;
    case SHOW_NEXT_GAME:
      currentGameIndex = getNextSelectedGame();
      gamesView();
      setState(GAME);
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

// #define SIZE 200
const int SW_pin = 8; // digital pin connected to switch output

void setup()
{
  Serial.begin(9600);

  // Setup Pins
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);

  // Notes from Adafruit sketch - must investigate.
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3C (for the 128x32)

  // Clear the display buffer.
  display.clearDisplay();

  // Initial Sequence. Show intro.
  setState(START);
  stateController(START_INIT);
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
  // Move to menu.
  setState(MENU);
  stateController(MAIN_MENU);
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

int getNextSelectedGame()
{
  return (currentGameIndex + 1) % sizeof(currentGameIndex);
}

void menuView()
{
  display.clearDisplay();
  drawBitmap(45, 1, menu_title, menu_title_BMPWIDTH, menu_title_BMPHEIGHT);
  drawBitmap(games_text_X, games_text_Y, games_text, games_text_BMPWIDTH, games_text_BMPHEIGHT);
  drawBitmap(setup_text_X, setup_text_Y, setup_text, setup_text_BMPWIDTH, setup_text_BMPHEIGHT);
  // Highlight First menu item onload of view.
  stateController(HIGHLIGHT_GAME_MENU);
  display.display();
}

void gamesView()
{
  display.clearDisplay();
  // All Logos must be the following dimenstions.
  short int _gameLogoWidth = 68;
  short int _gameLogoHeight = 8;
  // Calculate the center point for Menu and Games bitmaps.
  short int _game_menu_title_x = getCenter(screen_width, game_title_BMPWIDTH);
  short int _curr_game_logo_x = getCenter(screen_width, _gameLogoWidth);
  // GAMES MENU //
  drawBitmap(_game_menu_title_x, 1, game_title, game_title_BMPWIDTH, game_title_BMPHEIGHT);
  drawBitmap(_curr_game_logo_x, 20, games[currentGameIndex], _gameLogoWidth, _gameLogoHeight);
  // Render display
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

void loop()
{

  // MENU STATE Event Handling. TODO Move to a controller that considers state.
  if (currentState == MENU)
  {
    if (analogRead(A0) < 10)
    {
      Serial.print("GAME MODE");
      stateController(HIGHLIGHT_GAME_MENU);
    }
    if (analogRead(A0) > 1013)
    {
      Serial.print("SETUP MODE");
      stateController(HIGHLIGHT_SETUP_MENU);
    }
    if (digitalRead(SW_pin) == 0)
    {
      stateController(SELECT_MODE);
    }
  }
  if (currentState == GAME)
  {
    // if UP is used
    // if (analogRead(A0) < 10) // Back
    // {
    //   Serial.print("HIGHLIGHT_BACK_BUTTON");
    //   stateController(HIGHLIGHT_BACK_BUTTON);
    // }
    if (analogRead(A0) < 10 || analogRead(A0) > 1013) // Game
    {
      // Serial.print("HIGHLIGHT_GAME");
      // stateController(HIGHLIGHT_GAME);
      Serial.print("SHOW_NEXT_GAME");
      stateController(SHOW_NEXT_GAME);
    }
    if (digitalRead(SW_pin) == 0)
    {
      stateController(SELECT_MODE);
    }
  }
}

// Loading Stars effect.
void animateStars(const uint8_t *bitmap, uint8_t w, uint8_t h)
{
  for (uint8_t f = 0; f < 100; f++)
  {
    int x = random(display.width());
    int y = random(display.height());
    display.drawPixel(x, y, WHITE);
  }
}

// Draw bitmap exactly as defined.
void drawBitmap(uint8_t xpos, uint8_t ypos, const uint8_t *bitmap, uint8_t w, uint8_t h)
{
  display.drawBitmap(xpos, ypos, bitmap, w, h, WHITE);
  display.display();
}
