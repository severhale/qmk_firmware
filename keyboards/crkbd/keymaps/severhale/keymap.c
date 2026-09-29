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
                                         XXXXXXX, OSL(_NAV),SFT_BSPC,     KC_SPC,  OSL(_SYM),XXXXXXX
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
     _______, C(S(KC_PWR)),S_MOD,A(KC_F12),_______,A(KC_BSPC),                  KC_LEFT, KC_DOWN, KC_UP,   KC_RIGHT,_______, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, A(G(C(KC_P))),KC_MNXT,A(S(KC_VOLD)),A(S(KC_VOLU)),_______,        _______, _______, _______, _______, _______, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         XXXXXXX,_______,_______,     KC_ENT,  MO(_NUM),XXXXXXX
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

// Caps word: squeeze-and-hold both left thumbs (shift + NAV) for ~0.2s.
const uint16_t PROGMEM caps_word_combo[] = {SFT_BSPC, OSL(_NAV), COMBO_END};

combo_t key_combos[] = {
    COMBO(cmd_s_combo, LGUI(KC_S)), // save
    COMBO(cmd_w_combo, LGUI(KC_W)), // close tab
    COMBO(cmd_t_combo, LGUI(KC_T)), // new tab
    COMBO(cmd_c_combo, LGUI(KC_C)), // copy
    COMBO(cmd_v_combo, LGUI(KC_V)), // paste
    COMBO(caps_word_combo, QK_CAPS_WORD_TOGGLE),
};

// "ft" (after/often/software) and "fs" (offset/offspring) are common
// enough to misfire as quick chords, so those combos require a
// deliberate hold; the caps-word toggle likewise demands a deliberate
// hold so fast shift+nav gestures don't trigger it.
bool get_combo_must_hold(uint16_t combo_index, combo_t *combo) {
    return combo->keycode == LGUI(KC_T) || combo->keycode == LGUI(KC_S) || combo->keycode == QK_CAPS_WORD_TOGGLE;
}

// Chordal Hold serves the home-row mods well, but the thumb shift must
// resolve as held even for same-hand keys — the same-hand rule would
// otherwise turn left-hand shift+letter rolls into backspace taps.
bool get_chordal_hold(uint16_t tap_hold_keycode, keyrecord_t *tap_hold_record, uint16_t other_keycode, keyrecord_t *other_record) {
    if (tap_hold_keycode == SFT_BSPC) {
        return true;
    }
    return get_chordal_hold_default(tap_hold_record, other_record);
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

  return true;
}
