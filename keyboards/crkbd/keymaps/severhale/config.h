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
// common bigrams, so those two combos require a short deliberate hold;
// typing stays safe because releasing either key before this term
// expires drops the combo back to plain letters. Combos are also
// order-sensitive: F must be pressed first (it's the cmd anchor), so
// reversed bigrams like "awful" (w→f) or "cfg" (c→f) never fire them.
#define COMBO_TERM 50
#define COMBO_HOLD_TERM 100
#define COMBO_MUST_HOLD_PER_COMBO
#define COMBO_MUST_PRESS_IN_ORDER

// RPC channel syncing the master's keypress count to the slave OLED
#define SPLIT_TRANSACTION_IDS_USER PUT_KEYPRESS_COUNT

// #define NO_ACTION_ONESHOT

#ifdef AUDIO_ENABLE
#    define AUDIO_PIN B5
#    define NO_MUSIC_MODE
#    define AUDIO_CLICKY
#endif
