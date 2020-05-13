#include <buttonctrl.h>
   
#define PIN_BUTTON D8
ButtonCtrl<PIN_BUTTON> button;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(2000);
  while(!Serial) { }

  button.begin();
}

void loop() {
  const ButtonEvent btn_ev = button.handle();
  if (btn_ev == Click) {
    Serial.println("Clicked!");
  }
}
