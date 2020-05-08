#include <buttonctrl.h>

#define PIN_BUTTON D8

// Register a long click after the button has been pressed for 5 seconds
ButtonCtrl button = ButtonCtrl(PIN_BUTTON, 5000);

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(2000);
  while(!Serial) { }

  button.begin();
}

void loop() {
  const ButtonEvent btn_ev = button.handle();

  if (btn_ev == LongClick) {
    Serial.println("This is a long click");
  }
}
