#pragma once

enum layers {
    _QWERTY,
    _NAV,
    _SYM,
    _COLEMAK,
    _NUM,
};

enum custom_keycodes { QWERTY = SAFE_RANGE, LOWER, RAISE, ADJUST, RGBRST };

#define S_MOD MT(MOD_LCTL, KC_S)
#define D_MOD MT(MOD_LALT, KC_D)
#define F_MOD MT(MOD_LGUI, KC_F)
#define J_MOD MT(MOD_RGUI, KC_J)
#define K_MOD MT(MOD_RALT, KC_K)
#define L_MOD MT(MOD_RCTL, KC_L)

#define KC_PLAY C(A(LCA(LGUI(LCAG(KC_P)))))
#define KC_SKIP C(A(LCA(LGUI(LCAG(KC_RIGHT)))))
#define KC_SLEEP C(S(KC_POWER))
#define VOLUP S(A(KC_VOLU))
#define VOLDWN S(A(KC_VOLD))
