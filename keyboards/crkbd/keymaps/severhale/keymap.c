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
                                         XXXXXXX, OSL(_NAV),SFT_BSPC,     NUM_SPC, OSL(_SYM),XXXXXXX
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

  // Hold NAV + space = enter; backspace stays backspace (falls through)
  [_NAV] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     _______, _______, TG(_COLEMAK),G(S(KC_F9)),S(KC_F6),_______,                _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, C(S(KC_PWR)),S_MOD,A(KC_F12),_______,_______,                    KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,_______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, A(G(C(KC_P))),KC_MNXT,A(S(KC_VOLD)),A(S(KC_VOLU)),_______,        _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         XXXXXXX,_______,QK_CAPS_WORD_TOGGLE,     KC_ENT,  MO(_NUM),XXXXXXX
                                      //|--------------------------|  |--------------------------|
  ),

  // Hold SYM + backspace = tab; space stays space (falls through)
  [_SYM] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     _______, KC_TILD, KC_PIPE, KC_DQUO, KC_QUES, _______,                      _______, KC_LBRC,  KC_RBRC,  KC_MINUS,KC_EQUAL,_______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                      KC_CIRC, KC_LCBR,  KC_RCBR,  KC_AMPR, KC_ASTR, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, KC_GRV,  KC_BSLS, KC_QUOT, KC_SLSH, _______,                      _______, KC_LPRN,  KC_RPRN,  KC_UNDS, KC_PLUS, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         XXXXXXX, MO(_NUM),KC_TAB,     _______, _______, XXXXXXX
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

// One-handed Cmd shortcuts. F is the home-row Cmd mod-tap, but Chordal Hold
// resolves same-hand chords as typing rolls, so F+letter needs explicit
// combos. Definitions use the mod-tap keycodes (F_MOD/S_MOD) because the
// combo engine matches on the emitted key event, not the tap keycode.
const uint16_t PROGMEM cmd_s_combo[] = {F_MOD, S_MOD, COMBO_END};
const uint16_t PROGMEM cmd_w_combo[] = {F_MOD, KC_W, COMBO_END};
const uint16_t PROGMEM cmd_t_combo[] = {F_MOD, KC_T, COMBO_END};
const uint16_t PROGMEM cmd_c_combo[] = {F_MOD, KC_C, COMBO_END};
const uint16_t PROGMEM cmd_v_combo[] = {F_MOD, KC_V, COMBO_END};

combo_t key_combos[] = {
    COMBO(cmd_s_combo, LGUI(KC_S)), // save
    COMBO(cmd_w_combo, LGUI(KC_W)), // close tab
    COMBO(cmd_t_combo, LGUI(KC_T)), // new tab
    COMBO(cmd_c_combo, LGUI(KC_C)), // copy
    COMBO(cmd_v_combo, LGUI(KC_V)), // paste
};

// "ft" (after/often/software) and "fs" (offset/offspring) are common
// enough to misfire as quick chords, so those combos require a
// deliberate hold; the rest fire on a fast chord.
bool get_combo_must_hold(uint16_t combo_index, combo_t *combo) {
    return combo->keycode == LGUI(KC_T) || combo->keycode == LGUI(KC_S);
}

// The space thumb (NUM_SPC) must settle as a tap when interrupted by
// typing rolls — chordal/permissive would otherwise read space+letter
// as a hold and swallow the space mid-word. Holding it past
// TAPPING_TERM (250ms, same as every other tap/hold key) activates the
// NUM layer.
bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record, uint16_t other_keycode, keyrecord_t *other_record) {
    if (tap_hold_keycode == NUM_SPC) {
        return false;
    }
    return get_chordal_hold_default(tap_hold_record, other_record);
}

bool get_permissive_hold(uint16_t keycode, keyrecord_t *record) {
    if (keycode == NUM_SPC) {
        return false;
    }
    return true;
}

// Left thumb (SFT_BSPC): hold = shift for any key on either hand; tap =
// backspace, unless a key lands within TAP_SHIFT_WINDOW ms of the tap,
// in which case that key is shifted (tap-shift).
static bool         tap_shift_pending = false;
static bool         tap_shift_armed   = false;
static deferred_token tap_shift_token = INVALID_DEFERRED_TOKEN;
static bool         thumb_down       = false;
static bool         thumb_shifted    = false;
static uint16_t     thumb_press_time = 0;
static bool         thumb_repeating  = false;
static uint16_t     thumb_last_release = 0;

static uint32_t tap_shift_send_backspace(uint32_t trigger_time, void *cb_arg) {
    tap_shift_token   = INVALID_DEFERRED_TOKEN;
    tap_shift_pending = false;
    tap_code(KC_BSPC);
    return 0;
}

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

  // A key pressed inside the tap-shift window: shift it instead of
  // sending the thumb's backspace.
  if (tap_shift_pending && record->event.pressed && keycode != SFT_BSPC) {
      tap_shift_pending = false;
      if (tap_shift_token != INVALID_DEFERRED_TOKEN) {
          cancel_deferred_exec(tap_shift_token);
          tap_shift_token = INVALID_DEFERRED_TOKEN;
      }
      register_mods(MOD_LSFT);
      tap_shift_armed = true;
  } else if (tap_shift_armed && !record->event.pressed) {
      unregister_mods(MOD_LSFT);
      tap_shift_armed = false;
  }

  if (keycode == SFT_BSPC) {
      if (record->event.pressed) {
          if (timer_elapsed(thumb_last_release) < TAPPING_TERM) {
              // Double-tap: hold to repeat backspace (native key repeat).
              thumb_repeating = true;
              if (tap_shift_pending) {
                  cancel_deferred_exec(tap_shift_token);
                  tap_shift_token   = INVALID_DEFERRED_TOKEN;
                  tap_shift_pending = false;
              }
              register_code(KC_BSPC);
          } else {
              thumb_repeating = false;
              thumb_down       = true;
              thumb_shifted    = false;
              thumb_press_time = timer_read();
          }
      } else {
          thumb_last_release = timer_read();
          if (thumb_repeating) {
              thumb_repeating = false;
              unregister_code(KC_BSPC);
          } else {
              thumb_down = false;
              if (thumb_shifted) {
                  unregister_mods(MOD_LSFT);
              } else if (timer_elapsed(thumb_press_time) < TAPPING_TERM) {
                  // Quick tap: backspace, unless a key arrives within the
                  // tap-shift window.
                  tap_shift_token   = defer_exec(TAP_SHIFT_WINDOW, tap_shift_send_backspace, NULL);
                  tap_shift_pending = tap_shift_token != INVALID_DEFERRED_TOKEN;
                  if (!tap_shift_pending) {
                      tap_code(KC_BSPC);
                  }
              }
              // Held past TAPPING_TERM with no other key: plain shift, nothing to send.
          }
      }
      return false;
  }

  // Any other key pressed while the thumb is held gets shifted.
  if (thumb_down && record->event.pressed) {
      thumb_shifted = true;
      register_mods(MOD_LSFT);
  }

  // Space with mods held bypasses the layer-tap: thumb shift + space =
  // shift+enter; other mod+space (cmd+space etc.) = plain space tap.
  if (keycode == NUM_SPC && get_mods()) {
      if (record->event.pressed) {
          if (get_mods() & MOD_MASK_SHIFT) {
              tap_code(KC_ENT);
          } else {
              tap_code(KC_SPC);
          }
      }
      return false;
  }

  return true;
}
