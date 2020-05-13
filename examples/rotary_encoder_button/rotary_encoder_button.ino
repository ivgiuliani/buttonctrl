#include <buttonctrl.h>
   
// Rotary encoder buttons on a KY-040 are HIGH when released and
// LOW when pressed, whereas in "normal" push buttons it's the
// other way around. Whilst the default on a released state is
// LOW, we can override it in the initializer so that we can
// use buttonctrl to control the button on rotary encoders.
ButtonCtrl<D3, HIGH> button;

void setup() {
  Serial.begin(9600);
  Serial.setTimeout(2000);
  while(!Serial) { }

  // By default, we set the pin as `INPUT`, but by passing `true`
  // here we instead set it as `INPUT_PULLUP`.
  button.begin(true);
}

void loop() {
  const ButtonEvent btn_ev = button.handle();
  if (btn_ev == Click) {
    Serial.println("Clicked!");
  }
}
