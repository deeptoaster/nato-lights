#include "common.h"

HardwareControl::HardwareControl() {
  debounce = 0;
  nextButtonState = HIGH;
  nextButtonStateDebounced = HIGH;
  pinMode(NEXT_BUTTON_PIN, INPUT);
}

bool HardwareControl::getNextButtonPressed() {
  int next_button_read = digitalRead(NEXT_BUTTON_PIN);
  bool pressed = false;

  if (next_button_read != nextButtonState) {
#ifdef DEBUG
    Serial.print("[Hardware] Button state: ");
    Serial.println(next_button_read);
#endif

    nextButtonState = next_button_read;
    debounce = millis();
  }

  if (millis() - debounce >= BUTTON_DEBOUNCE) {
    if (next_button_read != nextButtonStateDebounced) {
      nextButtonStateDebounced = next_button_read;

      if (nextButtonStateDebounced == HIGH) {
        pressed = true;
      }
    }
  }

  return pressed;
}

int HardwareControl::getPot1Value() {
  int value = analogRead(POT_1_PIN);

#ifdef DEBUG
  Serial.print("[Hardware] Potentiometer 1 value: ");
  Serial.println(value);
#endif

  return value;
}

int HardwareControl::getPot2Value() {
  int value = analogRead(POT_2_PIN);

#ifdef DEBUG
  Serial.print("[Hardware] Potentiometer 2 value: ");
  Serial.println(value);
#endif

  return value;
}
