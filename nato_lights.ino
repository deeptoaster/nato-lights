#define DEBUG

#include "src/common.h"
#include "src/lights.h"
#include "src/pattern.h"
#include "src/patterns/pattern_colors.h"

int next_button_state_debounced;
int next_button_state;
int pattern_index = 0;
unsigned long debounce;
CRGB leds[LED_COUNT];
Lights *lights;

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif

  FastLED.addLeds<LED_TYPE, LED_PIN_1>(leds, LED_OFFSET_1, LED_COUNT_1);
  FastLED.addLeds<LED_TYPE, LED_PIN_2>(leds, LED_OFFSET_2, LED_COUNT_2);
  FastLED.addLeds<LED_TYPE, LED_PIN_3>(leds, LED_OFFSET_3, LED_COUNT_3);
  lights = new Lights();
  lights->addPattern<PatternColors>();
  debounce = 0;
  next_button_state = HIGH;
  pinMode(NEXT_BUTTON_PIN, INPUT);
}

void loop() {
  int next = digitalRead(NEXT_BUTTON_PIN);

  if (next != next_button_state) {
#ifdef DEBUG
    Serial.print("Button state: ");
    Serial.println(next);
#endif

    next_button_state = next;
    debounce = millis();
  }

  if (millis() - debounce >= BUTTON_DEBOUNCE) {
    if (next != next_button_state_debounced) {
      next_button_state_debounced = next;

      if (next_button_state_debounced == HIGH) {
        lights->nextPattern();
      }
    }
  }

  lights->step();
  FastLED.show();
  delay(1);
}
