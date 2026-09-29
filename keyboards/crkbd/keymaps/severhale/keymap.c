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

  // SYM: LL position = NUM, backspace position = one-shot shift
  [_SYM] = LAYOUT_split_3x6_3(
  //|-----------------------------------------------------|                    |-----------------------------------------------------|
     _______, KC_TILD, KC_PIPE, KC_DQUO, KC_QUES, _______,                      _______, KC_LBRC,  KC_RBRC,  KC_MINUS,KC_EQUAL,_______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                      KC_CIRC, KC_LCBR,  KC_RCBR,  KC_AMPR, KC_ASTR, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
     _______, KC_GRV,  KC_BSLS, KC_QUOT, KC_SLSH, _______,                      _______, KC_LPRN,  KC_RPRN,  KC_UNDS, KC_PLUS, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                         XXXXXXX, MO(_NUM),OSM(MOD_LSFT),     _______, _______, XXXXXXX
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

  // One-shot mods don't consume one-shot layers, so the SYM one-shot
  // from RL would survive the shift key and hit the next keypress as a
  // symbol. End the layer one-shot as soon as the shift OSM fires.
  // clear_oneshot_layer_state (unlike reset_oneshot_layer) also turns the
  // layer off, so it cannot be orphaned on.
  if (keycode == OSM(MOD_LSFT) && record->event.pressed) {
      clear_oneshot_layer_state((oneshot_fullfillment_t)(ONESHOT_START | ONESHOT_TOGGLED));
  }

  // Shift + space = shift+enter (shift comes from RL+BSPC — OSM tap,
  // armed one-shot, or held; other mod+space passes through natively).
  if (keycode == KC_SPC && record->event.pressed && ((get_mods() | get_oneshot_mods()) & MOD_MASK_SHIFT)) {
      tap_code16(S(KC_ENT));
      return false;
  }

  return true;
}
