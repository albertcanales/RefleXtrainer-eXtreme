#include <Adafruit_NeoPixel.h>
#include <Adafruit_GFX.h>    // Libreria de graficos
#include <Adafruit_TFTLCD.h> // Libreria de LCD 

#define LCD_CS A3 // Chip Select - Pin analogico 3
#define LCD_CD A2 // Command/Data - Pin Analogico 2
#define LCD_WR A1 // LCD Write - Pin Analogico 1
#define LCD_RD A0 // LCD Read - Pin Analogico 0
#define LCD_RESET A4 // LCD Reset - Pin Analogico 4
#define PIN 6
#define NUM_PIXELS 8

Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET); // Instancia del LCD
Adafruit_NeoPixel rightDown = Adafruit_NeoPixel(2, 22, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leftDown = Adafruit_NeoPixel(2, 24, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel rightUp = Adafruit_NeoPixel(2, 26, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel leftUp = Adafruit_NeoPixel(2, 28, NEO_GRB + NEO_KHZ800);

// This could be any of the pixel objects
const uint32_t CYAN = rightDown.Color(255, 0, 255);
const uint32_t RED = rightDown.Color(0, 255, 0);
const uint32_t BLUE = rightDown.Color(255, 0, 0);
const uint32_t GREEN = rightDown.Color(0, 0, 255);
const uint32_t WHITE = rightDown.Color(255, 255, 255);
const uint32_t MAGENTA = rightDown.Color(255, 255, 0);
const uint32_t YELLOW = rightDown.Color(15, 255, 185);
const uint32_t NONE = rightDown.Color(0, 0, 0);

const uint32_t COLORS[] = {RED, BLUE, GREEN, WHITE, MAGENTA, YELLOW, CYAN, NONE};
const int buttons[] = {44, 50, 38, 32, 36, 30, 42, 48};

#define  black   0x0000
//#define CYAN    0x07FF

uint32_t actualSequence[NUM_PIXELS];

const unsigned long CHRONO_TIME = 10 * 1000; // Time of Chrono mode in miliseconds
unsigned long t;

void setup() {
  tft.begin(0x9341);
  Serial.begin(9600);
  rightDown.begin();
  rightUp.begin();
  leftDown.begin();
  leftUp.begin();
  randomSeed(analogRead(A6));
  for (int i = 31; i <= 38; i++)
    pinMode(i, INPUT);

}

void loop() {
  delay(200);
  tft.fillScreen(black);
  bool rainbowLooping = rainbowCycle(5);
  while(rainbowLooping)
    rainbowLooping = rainbowCycle(5);
  bool chronoLooping = chronoGameMode(true);
    while(chronoLooping)
    chronoLooping = chronoGameMode(false);
}
