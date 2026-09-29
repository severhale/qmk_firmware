#include QMK_KEYBOARD_H
#include "custom_keycodes.h"
#include "print.h"

#ifdef OLED_ENABLE
#    include "oled.c"
#endif

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     XXXXXXX, KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX, KC_A,    S_MOD,   D_MOD,   F_MOD,   KC_G,                         KC_H,    J_MOD,   K_MOD,   L_MOD,   KC_SCLN, XXXXXXX,
  //---------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     XXXXXXX, KC_Z,    KC_X,    KC_C,    KC_V,    KC_ESC,                       KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  XXXXXXX,
  //---------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         XXXXXXX, OSL(_NAV),KC_BSPC,     KC_SPC,  OSL(_SYM),XXXXXXX
                                      //|--------------------------|  |--------------------------|

  ),

  // Colemak-DH matrix; ESC takes the / slot (slash lives on the SYM layer)
  [_COLEMAK] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     _______, KC_Q,    KC_W,    KC_F,    KC_P,    KC_B,                         KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, KC_A,    KC_R,    KC_S,    KC_T,    KC_G,                         KC_M,    KC_N,    KC_E,    KC_I,    KC_O,    _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, KC_Z,    KC_X,    KC_C,    KC_D,    KC_V,                         KC_K,    KC_H,    KC_COMM, KC_DOT,  KC_ESC, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         XXXXXXX, _______, _______,    _______, _______, XXXXXXX
                                      //|--------------------------|  |--------------------------|
  ),

  // NAV: space = enter, RL position = tab, backspace position = caps word
  [_NAV] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     _______, _______, TG(_COLEMAK),G(S(KC_F9)),S(KC_F6),_______,                _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, C(S(KC_PWR)),S_MOD,A(KC_F12),_______,_______,                    KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,_______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, A(G(C(KC_P))),KC_MNXT,A(S(KC_VOLD)),A(S(KC_VOLU)),_______,        _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         XXXXXXX,_______,QK_CAPS_WORD_TOGGLE,     KC_ENT,  KC_TAB, XXXXXXX
                                      //|--------------------------|  |--------------------------|
  ),

  // SYM: LL position = NUM, backspace position = shift (tap = one-shot, hold = held)
  [_SYM] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     _______, KC_TILD, KC_PIPE, KC_DQUO, KC_QUES, _______,                      _______, KC_LBRC,  KC_RBRC,  KC_MINUS,KC_EQUAL,_______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                      KC_CIRC, KC_LCBR,  KC_RCBR,  KC_AMPR, KC_ASTR, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, KC_GRV,  KC_BSLS, KC_QUOT, KC_SLSH, _______,                      _______, KC_LPRN,  KC_RPRN,  KC_UNDS, KC_PLUS, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         XXXXXXX, MO(_NUM),THUMB_SHIFT,     _______, _______, XXXXXXX
                                      //|--------------------------|  |--------------------------|
  ),

  [_NUM] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, _______, _______, _______, _______, _______,                      _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         XXXXXXX, _______, _______,    _______, _______, XXXXXXX
                                      //|--------------------------|  |--------------------------|
  ),
};

// F is a real Cmd modifier rather than a chord key: get_tapping_term
// gives F its own short window (F_CMD_HOLD_MS), so holding it that long
// settles F as LGUI on its own and any key pressed afterward (either
// hand, repeatedly — two T taps for two tabs) dispatches instantly with
// Cmd. Shorter F-to-key intervals are typing rolls and stay plain
// letters via Chordal Hold's same-hand rule.
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    if (keycode == F_MOD) {
        return F_CMD_HOLD_MS;
    }
    return TAPPING_TERM;
}

// A lone F pressed slowly (held past the anchor with no other key)
// settles as a bare held modifier and types nothing. This fork has no
// standalone RETRO_TAPPING, so send the "f" tap manually on release.
static bool     f_cmd_lone_press = false;
static uint16_t f_cmd_press_time = 0;

// queuedUpdates/lastKeyPress are defined in oled.c and drive the OLED
// game of life; this replaces the old fork's process_oled core patch.
// Runs on the master only; oled.c syncs a keypress count to the slave
// so its OLED animates too.
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
    queuedUpdates++;
    lastKeyPress = timer_read();
#ifdef SPLIT_KEYBOARD
    keypress_count++;
#endif
  }

  // Retro-tap tracking for a slowly-pressed lone F (see above).
  if (record->event.pressed) {
      if (keycode == F_MOD) {
          f_cmd_lone_press = true;
          f_cmd_press_time = record->event.time;
      } else {
          f_cmd_lone_press = false;
      }
  } else if (keycode == F_MOD && f_cmd_lone_press && timer_elapsed(f_cmd_press_time) >= F_CMD_HOLD_MS) {
      f_cmd_lone_press = false;
      tap_code(KC_F);
  }

  // RL+BSPC shift (THUMB_SHIFT, on the SYM layer): the press registers
  // real shift immediately — hold it for runs of capitals; a release with
  // no key pressed in between converts to a one-shot so the next key is
  // capitalized. The SYM layer is torn down on press (bit off + tracking
  // cleared together, so it can't be orphaned) and the next key lands on
  // the base layer.
  static bool thumb_shift_held = false;
  static bool thumb_shift_used = false;

  if (keycode == THUMB_SHIFT) {
      if (record->event.pressed) {
          thumb_shift_held = true;
          thumb_shift_used = false;
          register_mods(MOD_LSFT);
          layer_off(_SYM);
          reset_oneshot_layer();
      } else {
          thumb_shift_held = false;
          unregister_mods(MOD_LSFT);
          if (!thumb_shift_used) {
              set_oneshot_mods(MOD_LSFT);
          }
      }
      return false;
  }

  // While the thumb shift is held, space as the FIRST key pressed sends
  // shift+enter (hold shift, tap space = newline). Any later space is a
  // plain space so caps sentences keep their word gaps; mid-paragraph
  // shift+enter stays available via LL+space, whose enter dispatch
  // carries the held shift natively.
  if (keycode == KC_SPC && record->event.pressed && thumb_shift_held && !thumb_shift_used) {
      thumb_shift_used = true;
      tap_code16(S(KC_ENT));
      return false;
  }

  if (thumb_shift_held && record->event.pressed) {
      thumb_shift_used = true;
  }

  return true;
}
