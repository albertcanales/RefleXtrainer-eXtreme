void ChronoModeSetup() {
  clearScreen();
  tft.fillScreen(black);
  Serial.println("Welcome to Chrono Gamemode!");
  tft.setRotation(45);
  tft.setCursor(40, 50);
  tft.setTextSize(5);
  tft.setTextColor(CYAN);
  tft.println("Press to");
  tft.println("   START");
}

bool chronoGameMode(bool start) {
  if (start) {
    colorAll(NONE);
    ChronoModeSetup();
    while (buttonPressed() == -1);
  }
  countdown();
  tft.fillScreen(black);
  int count = 0;
  printCount(count);
  bool gameFinished = false;
  randomSequence(RED);
  t = 1UL * millis();
  int sec = (1UL * millis() - t) / 1000;
  while (!gameFinished) {
    if (timeOver(t)) {
      Serial.println("Time out!");
      blinkColor(WHITE);
      gameFinished = true;
    }
    else {
      if ((millis() - t) / 1000 != sec) {
        sec = (millis() - t) / 1000;
        printTime(sec);
        Serial.print("Seconds passed: ");
        Serial.println(sec);
      }
      int button = buttonPressed();
      if (button != -1) {
        if (correctButton(button, actualSequence, RED)) {
          count++;
          printCount(count);
          Serial.print("Count: ");
          Serial.println(count);
          randomSequence(RED);
        }
        else {
          Serial.println("Wrong button!");
          gameFinished = true;
          blinkColor(RED);
        }
      }
    }
  }
  Serial.println("Game finished!");
  Serial.print("Your result is: ");
  Serial.println(count);
  bool res = printResult(count);  
  return res;
}



void randomSeqs() {
  while (true) {
    randomSequence(RED);
    for (int i = 0; i < NUM_PIXELS; i++) {
      if (actualSequence[i] == RED)
        int red_i = i;
    }
    Serial.println("");
    delay(1000);
  }
}



void lightOnFocus() {
  while (true) {
    colorAll(NONE);
    int button = buttonPressed();
    if (button != -1) {
      uint32_t colors[NUM_PIXELS];
      for (int i = 0; i < NUM_PIXELS; i++) {
        if (i == button)
          colors[i] = COLORS[random(1, 7)];
        else
          colors[i] = NONE;
      }
      setPixels(colors);
      delay(100);
    }
  }
}

bool rainbowCycle(int SpeedDelay) {
  byte *c;
  uint16_t i, j;

  for(j=0; j<256; j++) {
    for(i=0; i< NUM_PIXELS; i++) {
      c=Wheel(((i * 256 / NUM_PIXELS) + j) & 255);
      individualPixel(i, rightDown.Color(*c, *(c+1), *(c+2)));
    }
    delay(SpeedDelay);
  }
  return buttonPressed() == -1;
}

byte * Wheel(byte WheelPos) {
  static byte c[3];
  
  if(WheelPos < 85) {
   c[0]=WheelPos * 3;
   c[1]=255 - WheelPos * 3;
   c[2]=0;
  } else if(WheelPos < 170) {
   WheelPos -= 85;
   c[0]=255 - WheelPos * 3;
   c[1]=0;
   c[2]=WheelPos * 3;
  } else {
   WheelPos -= 170;
   c[0]=0;
   c[1]=WheelPos * 3;
   c[2]=255 - WheelPos * 3;
  }

  return c;
}
