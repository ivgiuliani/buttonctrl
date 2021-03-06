#ifndef __BUTTONCTRL_H__
#define __BUTTONCTRL_H__

#include <Arduino.h>

enum ButtonEvent {
  // Raised when nothing has happened.
  None = 0,

  // Raised when the button has just been clicked.
  ClickDown = 1,

  // Raised when the button has been clicked and then released.
  Click = 2,

  // Raised when the button is released.
  ClickUp = 3,

  // Raised when the button is pressed for a long time (configurable via
  // `long_click_ms` in the initialiser).
  LongClick = 4,
};

/**
 * Helper class for handling (push) buttons on an arduino-compatible board.
 **/
template <uint8_t pin,
          uint8_t button_released_signal = LOW,
          uint8_t pin_mode = INPUT>
class ButtonCtrl {
public:
  /**
   * @param long_click_ms minimum time for the button to be pressed to raise a long click
   */
  ButtonCtrl(const uint16_t long_click_ms = 1500) {
    this->long_click_ms = long_click_ms;
  }

  void begin() {
    current_state = None;
    pinMode(pin, pin_mode);
  }

  ButtonEvent handle() {
    const long now = millis();
    const bool is_btn_released = digitalRead(pin) == button_released_signal;

    // We only want to take action right after the button has been
    // released, we don't care about the button state at rest.
    if (is_btn_released) {
      switch(current_state) {
        case ClickDown:
          return emit(Click);
        case Click:
        case LongClick:
          last_click = 0;
          return emit(ClickUp);
        default:
          return emit(None);
      }
    }

    // The button is pressed at this point, other than triggering
    // the right ClickDown event we should check for how long this
    // has been going on in case we need to trigger a LongClick.
    switch(current_state) {
      case None:
        last_click = now;
        return emit(ClickDown);
      case ClickDown:
      case LongClick:
        if (now - last_click > long_click_ms) {
          return emit(LongClick);
        }
        return emit(ClickDown);
      default:
        // It shouldn't be possible to get here.
        return emit(None);
    }
  }

  static const char *str_from_event(const ButtonEvent event) {
    switch (event) {
      case ClickDown:
        return "click_down";
      case ClickUp:
        return "click_up";
      case Click:
        return "click";
      case LongClick:
        return "long_click";
      case None:
      default:
        return NULL;
    }
  }

private:
  uint16_t long_click_ms;
  uint32_t last_click = 0;

  ButtonEvent current_state = None;

  ButtonEvent emit(const ButtonEvent event) {
    if (current_state == event) {
      // return None when state has not changed in between calls
      return None;
    }
    current_state = event;
    return event;
  }
};

#endif // __BUTTONCTRL_H__
