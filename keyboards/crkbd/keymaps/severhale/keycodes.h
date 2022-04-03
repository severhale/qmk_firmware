#pragma once

enum layers {
    _QWERTY,
    _NAV,
    _SYM,
    _COLEMAK,
    _BSP,
    _NUM,
};

enum custom_keycodes { QWERTY = SAFE_RANGE, LOWER, RAISE, ADJUST, RGBRST };

#define SFT_EQ MT(MOD_LSFT, KC_EQL)
#define SFT_QT MT(MOD_RSFT, KC_QUOT)

#define SFT_A MT(MOD_LSFT, KC_A)
#define CTL_Z MT(MOD_LCTL, KC_Z)

#define SFT_SCLN MT(MOD_RSFT, KC_SCLN)
#define CTL_SLSH MT(MOD_RCTL, KC_SLSH)

#define LOW_SPC LT(_LOWER, KC_SPC)
#define RAI_EQ LT(_RAISE, KC_EQL)
#define RAI_ENT LT(_RAISE, KC_ENT)
#define LOW_BSP LT(_LOWER, KC_BSPC)
#define LOW_DEL LT(_LOWER, KC_DEL)
#define ADJ_GRV LT(_ADJUST, KC_GRV)
#define KC_ANGL LSFT(KC_COMM)
#define KC_ANGR LSFT(KC_DOT)

#define KC_PLAY C(A(LCA(LWIN(LCAG(KC_P)))))
#define KC_SKIP C(A(LCA(LWIN(LCAG(KC_RIGHT)))))
#define KC_SLEEP C(S(KC_POWER))
#define VOLUP S(A(KC_VOLU))
#define VOLDWN S(A(KC_VOLD))

#define S_MOD MT(MOD_LCTL,KC_S)
#define D_MOD MT(MOD_LALT,KC_D)
#define F_MOD MT(MOD_LGUI,KC_F)
#define J_MOD MT(MOD_RGUI,KC_J)
#define K_MOD MT(MOD_RALT,KC_K)
#define L_MOD MT(MOD_RCTL,KC_L)
#define A_MOD MT(MOD_LSFT,KC_A)

#define S_MODS MT(MOD_LCTL,S(KC_S))
#define D_MODS MT(MOD_LALT,S(KC_D))
#define F_MODS MT(MOD_LGUI,S(KC_F))
#define J_MODS MT(MOD_RGUI,S(KC_J))
#define K_MODS MT(MOD_RALT,S(KC_K))
#define L_MODS MT(MOD_RCTL,S(KC_L))
#define A_MODS MT(MOD_LSFT,S(KC_A))
