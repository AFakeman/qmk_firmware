#include QMK_KEYBOARD_H

enum custom_keycodes {
    AF_ZERO = SAFE_RANGE,
    AF_ONE,
    AF_LEN_1,
    AF_LEN_2,
    AF_LEN_3,
    AF_LEN_4,
    AF_RESET,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [0] = LAYOUT( /* Base */
        AF_ONE,  AF_LEN_2, AF_LEN_4, AF_RESET,
        AF_ZERO, AF_LEN_1, AF_LEN_3, LGUI(KC_SPACE)
    ),
};

uint8_t colors[8][3] = {
    {255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255},
    {255, 255, 255}, {0, 0, 0}, {0, 0, 0}, {255, 255, 255},
};

void matrix_scan_user(void) {
  //user matrix
}

enum af_color {
    AF_COLOR_BLUE,
    AF_COLOR_YELLOW,
    AF_COLOR_RED
};

struct af_message {
    uint8_t key;
    uint8_t color;
};

void rgb_matrix_indicators_user(void) {
  for (uint8_t i = 0; i < 8; ++i) {
      rgb_matrix_set_color(i, colors[i][0], colors[i][1], colors[i][2]);
  }
}

uint8_t char_position = 0;
uint8_t char_length = 0;
uint32_t char_keycode = 0;

void key_highlight(uint8_t key) {
    colors[key][0] = 255;
    colors[key][1] = 255;
    colors[key][2] = 255;
}

void key_filled(uint8_t key) {
    colors[key][0] = 0;
    colors[key][1] = 255;
    colors[key][2] = 0;
}

void unhighlight(uint8_t key) {
    colors[key][0] = 0;
    colors[key][1] = 0;
    colors[key][2] = 0;
}

void set_bit(uint8_t bit) {
    char_keycode <<= 1;
    char_keycode |= bit;
    char_position++;
    switch (char_position / 4) {
        case 4:
            key_filled(2);
        case 3:
            key_filled(6);
        case 2:
            key_filled(1);
        case 1:
            key_filled(5);
    }
}

void reset_binary_input(void) {
  char_position = 0;
  char_keycode = 0;
  char_length = 0;
  unhighlight(1);
  unhighlight(2);
  unhighlight(5);
  unhighlight(6);
}

void matrix_init_user(void) {
  //user initialization
  set_unicode_input_mode(UC_OSX);
  reset_binary_input();
}

void set_length(uint8_t length) {
  reset_binary_input();
  char_length = length;
  switch (char_length) {
    case 4:
      key_highlight(2);
    case 3:
      key_highlight(6);
    case 2:
      key_highlight(1);
    case 1:
      key_highlight(5);
  }
}

void maybe_send_code(void) {
    if (char_position == char_length * 4) {
        unicode_input_start ();
        register_hex(char_keycode);
        unicode_input_finish();
        reset_binary_input();
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  uint8_t bit = 0;
  switch (keycode) {
    case AF_ONE:
      bit = 1;
      // fallthrough
    case AF_ZERO:
      if (record->event.pressed) {
          if (char_length == 0) {
              set_length(4);
          }
          set_bit(bit);
          maybe_send_code();
      }
      return false;
      break;
    case AF_LEN_1:
    case AF_LEN_2:
    case AF_LEN_3:
    case AF_LEN_4:
      set_length(keycode - AF_LEN_1 + 1);
      return false;
      break;
    case AF_RESET:
      reset_binary_input();
      return false;
      break;
  }
  return true;
}
