// ####################### NEOPIXEL ##################################

void setPixels(uint32_t colors[]) {
  for (int i = 0; i < NUM_PIXELS; i++) {
    individualPixel(i, colors[i]);
  }
}

void randomSequence(uint32_t target) {
  // Although it is void, it "returns" a change made in the global variable actualSequence
  // Programmed this way to avoid using annoying pointers xD
  uint32_t colors [NUM_PIXELS];
  int i_target = random(0, NUM_PIXELS);
  colors[i_target] = target;
  for (int i = 0; i < NUM_PIXELS; i++) {
    if (i != i_target) {
      colors[i] = COLORS[random(1, 7)];
      while (colors[i] == target)
        colors[i] = COLORS[random(1, 7)];
    }
  }
  setPixels(colors);
  copyToActualSequence(colors);
}

void copyToActualSequence(uint32_t arr[]) {
  for (int i = 0; i < NUM_PIXELS; i++)
    actualSequence[i] = arr[i];
}

void individualPixel(int i, uint32_t color) {
  if (i < 2) {
    rightDown.setPixelColor(i % 2, color);
    rightDown.show();
  }
  else if (i < 4) {
    leftDown.setPixelColor(i % 2, color);
    leftDown.show();
  }
  else if (i < 6) {
    rightUp.setPixelColor(i % 2, color);
    rightUp.show();
  }
  else {
    leftUp.setPixelColor(i % 2, color);
    leftUp.show();
  }
}

void colorAll(uint32_t color) {
  uint32_t colors [NUM_PIXELS];
  for (int i = 0; i < NUM_PIXELS; i++)
    colors[i] = color;
  setPixels(colors);
}

void blinkColor(uint32_t color) {
  colorAll(NONE);
  delay(200);
  colorAll(color);
  delay(200);
  colorAll(NONE);
  delay(150);
  colorAll(color);
  delay(200);
  colorAll(NONE);
}

// ####################### BUTTONS ##################################

int lastButton = -1;

int buttonPressed() {
  for (int i = 0; i < 8; i++) {
    if (digitalRead(buttons[i])) {
      delay(5);
      if (lastButton != i) {
        lastButton = i;
        Serial.println("Button state changed");
        return i;
      }
      else {
        return -1;
      }
    }
  }
  lastButton = -1;
  return -1;
}

bool correctButton(int button, uint32_t colors[], uint32_t COLOR) {
  return colors[button] == COLOR;
}

// ####################### SERIAL ##################################

void clearScreen() {
  for (int i = 0; i < 200; i++) {
    Serial.println("");
  }
}

// ####################### TIME ##################################

boolean timeOver(unsigned long t) {
  return 1UL * millis() - t > CHRONO_TIME;
}

// ####################### SCREEN ##################################

void printCount(int count) {
  tft.setRotation(45);
  tft.setTextSize(15);
  tft.setTextColor(CYAN);
  if (count < 10) {
    tft.fillRect(120, 60, 80, 110, black);
    tft.setCursor(120, 60);
  }
  else {
    tft.fillRect(120, 60, 160, 110, black);
    tft.setCursor(100, 60);
  }
  tft.println(count);
}

void printTime(int t) {
  tft.setRotation(45);
  tft.setTextSize(5);
  tft.setTextColor(CYAN);
  if (t < 10) {
    tft.fillRect(280, 200, 30, 35, black);
    tft.setCursor(280, 200);
  }
  else {
    tft.fillRect(270, 200, 60, 35, black);
    tft.setCursor(260, 200);
  }
  tft.println(t);
}

bool printResult(int count) {
  tft.fillScreen(black);
  tft.setRotation(45);
  tft.setTextSize(4);
  tft.setTextColor(CYAN);
  tft.setCursor(0, 20);
  tft.println("  Well done!");
  tft.setTextSize(2);
  tft.println("");
  tft.setTextSize(7);
  tft.print("   ");
  tft.println(count);
  tft.setTextSize(2);
  tft.println("");
  tft.setTextSize(5);
  tft.print(" Press to");
  tft.print("   RESTART");

  return isLooping();
}

// ####################### OTHER ##################################

bool isLooping() {
  int countRed = 0;
  int countCyan = 0;
  boolean choices[NUM_PIXELS];
  for (int i = 0; i < NUM_PIXELS; i++) {
    choices[i] = random(0, 2);
    Serial.println(choices[i]);
    if (countRed >= NUM_PIXELS / 2) {
      choices[i] = true;
      individualPixel(i, CYAN);
      countCyan++;
    }
    else if (countCyan >= NUM_PIXELS / 2) {
      choices[i] = false;
      individualPixel(i, RED);
      countRed++;
    }
    else {
      individualPixel(i, choices[i] ? CYAN : RED);
      if (choices[i]) countCyan++;
      else countRed++;
    }
  }
  while (true) {
    int button = buttonPressed();
    if (button != -1)
      return choices[button];
  }
}

void countdown() {
  colorAll(NONE);
  delay(250);
  colorAll(RED);
  delay(700);
  colorAll(NONE);
  delay(250);
  colorAll(YELLOW);
  delay(700);
  colorAll(NONE);
  delay(250);
  colorAll(GREEN);
  delay(700);
  colorAll(NONE);
  delay(250);
}
