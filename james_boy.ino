
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

//
#include "pitches.h"

// SYSTEM Bitmap Graphics.
#include "loading_screen_map.h"
#include "menu_screen_map.h"
#include "game_screen_map.h"
#include "setup_screen_map.h"

// GAME Bitmaps.
#include "games/maze_xy/maze_xy_map.h"
#include "games/quiz_num/quiz_num_map.h"

// Reset Pin.
#define OLED_RESET 4

// Initialise Adafruit_SSD1306 display.
Adafruit_SSD1306 display(OLED_RESET);

// Ensure the hardware is the correct resolution.
#if (SSD1306_LCDHEIGHT != 32 || SSD1306_LCDWIDTH != 128)
#error("Incorrect display resolution");
#endif

// Games Array Loader. Should look up all games. TODO.
// Define Game Index as 0 on init.
// Selection of Games live inside the publically defined games array.
int currentGameIndex = 0;
char *games[2] = {maze_xy, quiz_num};

// Pins Piezo
// 2 is ground
// 1 is PWR
int buzzer = 9;
int volume = 1;
int tempo = 200;
int melody[] = {
    NOTE_C4, NOTE_C3, NOTE_C2, NOTE_C1, NOTE_C4, NOTE_C3, NOTE_C2, NOTE_C1, NOTE_C4, NOTE_C3, NOTE_C2, NOTE_C1, NOTE_C4, NOTE_C3, NOTE_C2, NOTE_C1,
    NOTE_D4, NOTE_D3, NOTE_D2, NOTE_D1, NOTE_E4, NOTE_E3, NOTE_E2, NOTE_E1, NOTE_G4, NOTE_G3, NOTE_C2, NOTE_D1, NOTE_D4, NOTE_E3, NOTE_E2, NOTE_E1,
    NOTE_C4, NOTE_C3, NOTE_C2, NOTE_C1, NOTE_C4, NOTE_C3, NOTE_C2, NOTE_C1, NOTE_C4, NOTE_C3, NOTE_C2, NOTE_C1, NOTE_C4, NOTE_C3, NOTE_C2, NOTE_C1,
    NOTE_D4, NOTE_D3, NOTE_D2, NOTE_D1, NOTE_E4, NOTE_E3, NOTE_E2, NOTE_E1, NOTE_G4, NOTE_G3, NOTE_C2, NOTE_D1, NOTE_D4, NOTE_E3, NOTE_E2, 0};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations[] = {
    1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4,
    1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4,
    1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4,
    1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 4, 1, 2, 3, 0};

// All Game System States.
#include "states.h";
states currentState;

// All Game System Events.
#include "events.h";
events currentEvent;

// Joy - Actual values.
//int joyRight = 667;
//int joyLeft = 0;
//int joUp = 0;
//int joyDown = 667;
// Joy Usage with buffer.
int joyRight = 640;
int joyLeft = 30;
int joyUp = 30;
int joyDown = 640;

// stateController(HIGHLIGHT_GAME_MENU);
void menuStateController(enum events event)
{
  switch (event)
  {
  case MAIN_MENU_INIT:
    // Fix only redraw page when it isn't already drawn.
    if (currentEvent != MAIN_MENU_INIT)
    {
      menuView();
      select(games_text_X, games_text_Y, games_text_BMPWIDTH, games_text_BMPHEIGHT);
      clearSelect(setup_text_X, setup_text_Y, setup_text_BMPWIDTH, setup_text_BMPHEIGHT);
      setEvent(HIGHLIGHT_GAME_MENU);
    }
    break;
  case HIGHLIGHT_GAME_MENU:
    Serial.print("HIGHLIGHT_GAME_MENU");
    select(games_text_X, games_text_Y, games_text_BMPWIDTH, games_text_BMPHEIGHT);
    clearSelect(setup_text_X, setup_text_Y, setup_text_BMPWIDTH, setup_text_BMPHEIGHT);
    break;
  case HIGHLIGHT_SETUP_MENU:
    select(setup_text_X, setup_text_Y, setup_text_BMPWIDTH, setup_text_BMPHEIGHT);
    clearSelect(games_text_X, games_text_Y, games_text_BMPWIDTH, games_text_BMPHEIGHT);
    break;
  case SELECT:
    if (currentEvent == HIGHLIGHT_GAME_MENU)
    {
      setState(GAME);
      stateController(GAME_MENU_INIT);
    }
    if (currentEvent == HIGHLIGHT_SETUP_MENU)
    {
      setState(SETUP);
      stateController(SETUP_MENU_INIT);
    }
    break;
  default:
    Serial.print("do nothing");
  }
}

void setupStateController(enum events event)
{
  switch (event)
  {
  case MAIN_MENU_INIT: // BACK TO MENU
    setState(MENU);
    stateController(MAIN_MENU_INIT);
    break;
  case SETUP_MENU_INIT:
    setupView();
    break;
  default:
    Serial.print("do nothing");
    break;
  }
}

void gameStateController(enum events event)
{
  switch (event)
  {
  case MAIN_MENU_INIT: // BACK TO MENU
    setState(MENU);
    stateController(MAIN_MENU_INIT);
    break;
  case GAME_MENU_INIT: // INIT GAME MENU
    gamesView();
    select(30, 20, 68, 8); // underline game title logo
    break;
  case SHOW_NEXT_GAME: // SHOW NEXT GAME TITLE
    currentGameIndex = getNextSelectedGame();
    gamesView();
    select(30, 20, 68, 8); // underline game title logo
    break;
  case SHOW_PREV_GAME: // SHOW PREV GAME TITLE
    currentGameIndex = getPrevSelectedGame();
    gamesView();
    select(30, 20, 68, 8); // underline game title logo
    break;
  case SELECT: // SELECT
    break;
  default:
    Serial.print("do nothing");
  }
}

void stateController(enum events event)
{
  switch (currentState)
  {
  case START:
    intro();
    // DEVELOPMENT > Jump to other states for testing.
    // setState(MENU);
    // menuStateController(MAIN_MENU_INIT);
    break;
  case MENU:
    menuStateController(event);
    break;
  case SETUP:
    setupStateController(event);
  case GAME:
    gameStateController(event);
  default:
    Serial.print("CurrentState is not defined");
  }
  setEvent(event);
}

// #define SIZE 200
const int SW_pin = 8; // digital pin connected to switch output

unsigned long previousMillis = 0; // will store last time LED was updated

void setup()
{
  Serial.begin(9600);

  // Sound
  pinMode(buzzer, OUTPUT); // Set buzzer - pin 9 as an output SETUP...!!!
  analogWrite(buzzer, volume);

  // Setup Pins
  pinMode(SW_pin, INPUT);
  digitalWrite(SW_pin, HIGH);
  noTone(buzzer);

  // Notes from Adafruit sketch - must investigate.
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C); // initialize with the I2C addr 0x3C (for the 128x32)

  // Clear the display buffer.
  display.clearDisplay();

  // Initial Sequence. Show intro.
  setState(START);
  stateController(START_INTRO_INIT);

  // TODO Fix Non-blocking sound sequence!!

  //   for (int thisNote = 0; thisNote < 75; thisNote++) {
  //
  //      // to calculate the note duration, take one second divided by the note type.
  //      //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
  //      int noteDuration = tempo / noteDurations[thisNote];
  //      tone(buzzer, melody[thisNote], noteDuration);
  //
  //      // to distinguish the notes, set a minimum time between them.
  //      // the note's duration + 30% seems to work well:
  //      int pauseBetweenNotes = noteDuration * 1.30;
  //
  //      delay(pauseBetweenNotes);
  //
  //      unsigned long currentMillis = millis();

  //      if (currentMillis - previousMillis >= pauseBetweenNotes) {
  //
  //        // save the last time you blinked the LED
  //        previousMillis = currentMillis;
  //
  //        // stop the tone playing:
  //        noTone(buzzer);
  //
  //      }

  //      noTone(buzzer);
  //
  //  }
  //
  //  noTone(buzzer);
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
  stateController(MAIN_MENU_INIT);
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
int getPrevSelectedGame()
{
  return (currentGameIndex - 1) % sizeof(currentGameIndex);
}

void menuView()
{
  display.clearDisplay();
  drawBitmap(45, 1, menu_title, menu_title_BMPWIDTH, menu_title_BMPHEIGHT);
  drawBitmap(games_text_X, games_text_Y, games_text, games_text_BMPWIDTH, games_text_BMPHEIGHT);
  drawBitmap(setup_text_X, setup_text_Y, setup_text, setup_text_BMPWIDTH, setup_text_BMPHEIGHT);
  display.display();
}

void gamesView()
{
  display.clearDisplay();
  // All Logos must be the following dimenstions.
  short int _gameLogoWidth = 68;
  short int _gameLogoHeight = 8;
  // Calculate the center point for Menu and Games bitmaps.
  short int _game_menu_title_x = getCenter(SSD1306_LCDWIDTH, game_title_BMPWIDTH);
  short int _curr_game_logo_x = getCenter(SSD1306_LCDWIDTH, _gameLogoWidth);
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

  // Reference:
  //int joyRight = 655;
  //int joyLeft = 15;
  //int joUp = 15;
  //int joyDown = 655;

  // MENU STATE Event Handling. TODO Move to a controller that considers state.
  if (currentState == MENU)
  {
    if (analogRead(A0) < joyLeft)
    {
      stateController(HIGHLIGHT_GAME_MENU);
    }
    if (analogRead(A0) > joyRight)
    {
      stateController(HIGHLIGHT_SETUP_MENU);
    }
    if (digitalRead(SW_pin) == 0)
    {
      stateController(SELECT);
    }
  }
  if (currentState == GAME)
  {
    if (analogRead(A1) < joyUp) // Back on Up press
    {
      stateController(MAIN_MENU_INIT);
    }
    if (analogRead(A0) < 10 || analogRead(A0) > 1013) // Game
    {
      stateController(SELECT);
    }
    if (analogRead(A0) < joyLeft)
    {
      stateController(SHOW_PREV_GAME);
    }
    if (analogRead(A0) > joyRight)
    {
      stateController(SHOW_NEXT_GAME);
    }
  }
  if (currentState == SETUP)
  {
    if (analogRead(A1) < joyUp) // Back on Up press
    {
      stateController(MAIN_MENU_INIT);
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
