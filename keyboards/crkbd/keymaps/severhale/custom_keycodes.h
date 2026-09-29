#pragma once

// Colemak must sit below NAV/SYM: QMK resolves each keypress against
// the highest active layer, so a toggled Colemak layered above NAV would
// shadow the NAV-layer TG(_COLEMAK) toggle (and NAV/SYM keys generally)
// with its own letters — Colemak could be switched on but never off.
enum layers {
    _QWERTY,
    _COLEMAK,
    _NAV,
    _SYM,
    _NUM,
};

enum custom_keycodes { QWERTY = SAFE_RANGE, LOWER, RAISE, ADJUST, RGBRST };

// Left thumb shift: tap = backspace, hold = shift. Chordal Hold's
// same-hand rule is overridden for this key in keymap.c so left-hand
// letters capitalize too.
#define SFT_BSPC MT(MOD_LSFT, KC_BSPC)

#define S_MOD MT(MOD_LCTL, KC_S)
#define D_MOD MT(MOD_LALT, KC_D)
#define F_MOD MT(MOD_LGUI, KC_F)
#define J_MOD MT(MOD_RGUI, KC_J)
#define K_MOD MT(MOD_RALT, KC_K)
#define L_MOD MT(MOD_RCTL, KC_L)

#define KC_PLAY C(A(LCA(LGUI(LCAG(KC_P)))))
#define KC_SKIP C(A(LCA(LGUI(LCAG(KC_RIGHT)))))
#define KC_SLEEP C(S(KC_PWR))
#define VOLUP S(A(KC_VOLU))
#define VOLDWN S(A(KC_VOLD))
