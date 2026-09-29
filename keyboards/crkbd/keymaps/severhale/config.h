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

// F+letter one-handed ⌘ chords (see combos in keymap.c). "ft"/"fs" are
// common bigrams, so those two combos must be held deliberately.
#define COMBO_TERM 50
#define COMBO_HOLD_TERM 200
#define COMBO_MUST_HOLD_PER_COMBO

// RPC channel syncing the master's keypress count to the slave OLED
#define SPLIT_TRANSACTION_IDS_USER PUT_KEYPRESS_COUNT

// Thumb tap followed within this window by a key press = shifted key
// instead of backspace (see process_record_user in keymap.c). 20ms
// proved tighter than natural thumb-to-letter rebound; misses erased
// the previous character as backspace instead of capitalizing.
#define TAP_SHIFT_WINDOW 60

// Per-key permissive-hold override (keymap.c disables it for the space
// layer-tap so fast typing rolls never engage the NUM layer).
#define PERMISSIVE_HOLD_PER_KEY

// #define NO_ACTION_ONESHOT

#ifdef AUDIO_ENABLE
#    define AUDIO_PIN B5
#    define NO_MUSIC_MODE
#    define AUDIO_CLICKY
#endif
