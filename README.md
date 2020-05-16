# buttonctrl

Arduino helper library for translating push buttons state into click events

## Example

```cpp
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

  if (btn_ev != None) {
    Serial.println(button.str_from_event(btn_ev));
  }

  switch (btn_ev) {
    case Click:
      Serial.println("Clicked!");
      break;
    case LongClick:
      Serial.println("Long click!");
      break;
    default:
      break;
  }
}
```

## Events

- `Click`: the button has been clicked and then released. This is the
  event you want to handle if you want to trigger some action when the
  button is clicked.
- `LongClick`: the button has been pressed for longer than `long_click_ms`.
  Note that a `Click` event will *not* be raised after a long click
  (but `ClickDown` and `ClickUp` will be raised as normal). If you don't
  need to handle long clicks, then you should handle `Click` and `LongClick`
  events in the same way.
  By default, long clicks will be triggered after the button has been pressed
  for longer than 1500ms but this duration is configurable (see
  `examples/longclick`)
- `ClickDown`: the button has just been pressed down
- `ClickUp`: the button has just been released
