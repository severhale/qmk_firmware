#pragma once

#define EE_HANDS
#define SPLIT_USB_DETECT
#define SPLIT_TRANSPORT_MIRROR
#define DYNAMIC_KEYMAP_LAYER_COUNT 5

// Chordal Hold resolves home row mods by hand: same-hand keys pressed
// during the hold window are typing rolls (tap), opposite-hand keys are
// intended chords (hold). Tapping term is high because Chordal Hold
// buffers the decision inside it.
#define TAPPING_TERM 250
#define PERMISSIVE_HOLD
#define CHORDAL_HOLD

// F is a real Cmd modifier: get_tapping_term gives F its own short
// window, so holding it this long settles F as LGUI on its own — any
// key pressed afterward (either hand, repeatedly) dispatches instantly
// with Cmd. Shorter intervals are typing rolls and stay plain "f".
#define TAPPING_TERM_PER_KEY
#define F_CMD_HOLD_MS 100

// RPC channel syncing the master's keypress count to the slave OLED
#define SPLIT_TRANSACTION_IDS_USER PUT_KEYPRESS_COUNT

// #define NO_ACTION_ONESHOT

#ifdef AUDIO_ENABLE
#    define AUDIO_PIN B5
#    define NO_MUSIC_MODE
#    define AUDIO_CLICKY
#endif
