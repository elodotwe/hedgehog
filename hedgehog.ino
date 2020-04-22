#include <Adafruit_NeoPixel.h>

#define LED_PIN 3
#define LED_COUNT 8

Adafruit_NeoPixel strip(LED_COUNT, LED_PIN);

#define NOSE_SWITCH 6
#define TOP_SWITCH 4
#define SWITCH_COMMON 5
#define SWITCH_COMMON2 7

void setup() {
  strip.begin();
  strip.show();

  Serial.begin(9600);
  Serial.println("Hedgehog online!");

  pinMode(SWITCH_COMMON, OUTPUT);
  digitalWrite(SWITCH_COMMON, LOW);

  pinMode(SWITCH_COMMON2, OUTPUT);
  digitalWrite(SWITCH_COMMON2, LOW);

  pinMode(NOSE_SWITCH, INPUT_PULLUP);
  pinMode(TOP_SWITCH, INPUT_PULLUP);
}

void setColor(uint32_t color) {
  strip.fill(color, 0, LED_COUNT);
  strip.show();
}

#define RED strip.Color(255,0,0)
#define GREEN strip.Color(0,255,0)

unsigned long last_boop = 0;
unsigned long last_beep = 0;

//msec
#define DEBOUNCE 50

void loop() {
  if (Serial.available()) {
    int command = Serial.read();
    switch (command) {
      case 'r':
        Serial.println("red");
        setColor(RED);
        break;
      case 'g':
        Serial.println("green");
        setColor(GREEN);
        break;
      case '0':
        Serial.println("off");
        setColor(0);
        break;
      default:
        Serial.println("unknown command");
        Serial.println("r=red, g=green, 0=off");
    }
  }

  if (digitalRead(NOSE_SWITCH) == LOW) {
    if (millis() - last_boop > 50) {
      Serial.println("boop");
      setColor(0);
    }
    last_boop = millis();
  }

  if (digitalRead(TOP_SWITCH) == LOW) {
    if (millis() - last_beep > 50) {
      Serial.println("beep");
      setColor(strip.Color(random(256), random(256), random(256)));
    }
    last_beep = millis();
  }
}
