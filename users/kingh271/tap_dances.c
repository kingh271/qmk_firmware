#include "tap_dances.h"

int cur_dance (qk_tap_dance_state_t *state);

void aw_finished (qk_tap_dance_state_t *state, void *user_data);
void aw_reset (qk_tap_dance_state_t *state, void *user_data);
void eaw_finished (qk_tap_dance_state_t *state, void *user_data);
void eaw_reset (qk_tap_dance_state_t *state, void *user_data);
void navnum_finished (qk_tap_dance_state_t *state, void *user_data);
void navnum_reset (qk_tap_dance_state_t *state, void *user_data);
void ptt_finished (qk_tap_dance_state_t *state, void *user_data);
void ptt_reset (qk_tap_dance_state_t *state, void *user_data);
void gn_finished (qk_tap_dance_state_t *state, void *user_data);
void gn_reset (qk_tap_dance_state_t *state, void *user_data);
void cn_finished (qk_tap_dance_state_t *state, void *user_data);
void cn_reset (qk_tap_dance_state_t *state, void *user_data);

//Tap dance stuff
int cur_dance (qk_tap_dance_state_t *state) {
  if (state->count == 1) {
    //if (state->interrupted || !state->pressed)  return SINGLE_TAP;
    if (!state->pressed)  return SINGLE_TAP;
    //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
    else return SINGLE_HOLD;
  }
  else if (state->count == 2) {
     //* DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
     //* action when hitting 'pp'. Suggested use case for this return value is when you want to send two
     //* keystrokes of the key, and not the 'double tap' action/macro.
    //if (state->interrupted) return DOUBLE_SINGLE_TAP;
    //else if (state->pressed) return DOUBLE_HOLD;
    if (state->pressed) return DOUBLE_HOLD;
    else return DOUBLE_TAP;
  }
  //Assumes no one is trying to type the same letter three times (at least not quickly).
  //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
  //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
  if (state->count == 3) {
    if (state->interrupted || !state->pressed)  return TRIPLE_TAP;
    else return TRIPLE_HOLD;
  }
  else return 8; //magic number. At some point this method will expand to work for more presses
}

static tap aw_state = {
  .is_press_action = true,
  .state = 0
};

void aw_finished (qk_tap_dance_state_t *state, void *user_data) {
  aw_state.state = cur_dance(state);
  switch (aw_state.state) {
    case SINGLE_HOLD: register_code(KC_LALT); break;
    case DOUBLE_HOLD: register_code(KC_LGUI); break;
    case DOUBLE_TAP: register_code(KC_LGUI); break;
  }
}

void aw_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (aw_state.state) {
    case SINGLE_HOLD: unregister_code(KC_LALT); break;
    case DOUBLE_HOLD: unregister_code(KC_LGUI); break;
    case DOUBLE_TAP: unregister_code(KC_LGUI); break;
  }
  aw_state.state = 0;
}

static tap eaw_state = {
  .is_press_action = true,
  .state = 0
};

void eaw_finished (qk_tap_dance_state_t *state, void *user_data) {
  eaw_state.state = cur_dance(state);
  switch (eaw_state.state) {
    case SINGLE_TAP: register_code(KC_ESC); break;
    case SINGLE_HOLD: register_code(KC_LALT); break;
    case DOUBLE_HOLD: register_code(KC_LGUI); break;
    case DOUBLE_TAP: register_code(KC_LGUI); break;
  }
}

void eaw_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (eaw_state.state) {
    case SINGLE_TAP: unregister_code(KC_ESC); break;
    case SINGLE_HOLD: unregister_code(KC_LALT); break;
    case DOUBLE_HOLD: unregister_code(KC_LGUI); break;
    case DOUBLE_TAP: unregister_code(KC_LGUI); break;
  }
  eaw_state.state = 0;
}

static tap navnum_state = { 
  .is_press_action = true,
  .state = 0
};

void navnum_finished (qk_tap_dance_state_t *state, void *user_data) {
  navnum_state.state = cur_dance(state);
  switch (navnum_state.state) {
    case SINGLE_HOLD: layer_on(_NUM); break;
    case DOUBLE_HOLD: layer_on(_NAV); break;
  }
}

void navnum_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (navnum_state.state) {
    case SINGLE_HOLD: layer_off(_NUM); break;
    case DOUBLE_HOLD: layer_off(_NAV); break;
  }
  navnum_state.state = 0;
}

static tap ptt_state = {
  .is_press_action = true,
  .state = 0
};

void ptt_finished (qk_tap_dance_state_t *state, void *user_data) {
  ptt_state.state = cur_dance(state);
  switch (ptt_state.state) {
    case SINGLE_HOLD: register_code(KC_LCTL); break;
    case DOUBLE_HOLD: register_code(KC_F9); break;
  }
}

void ptt_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (ptt_state.state) {
    case SINGLE_HOLD: unregister_code(KC_LCTL); break;
    case DOUBLE_HOLD: unregister_code(KC_F9); break;
  }
  ptt_state.state = 0;
}

static tap gn_state = {
  .is_press_action = true,
  .state = 0
};

void gn_finished (qk_tap_dance_state_t *state, void *user_data) {
  gn_state.state = cur_dance(state);
  switch (gn_state.state) {
    case SINGLE_HOLD: layer_on(_NAV); break;
  }
}

void gn_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (gn_state.state) {
    case SINGLE_HOLD: layer_off(_NAV); break;
    case DOUBLE_TAP: default_layer_set(0x00000002); break;
    case TRIPLE_TAP: default_layer_set(0x00000004); break;
  }
  gn_state.state = 0;
}

static tap cn_state = {
  .is_press_action = true,
  .state = 0
};

void cn_finished (qk_tap_dance_state_t *state, void *user_data) {
  cn_state.state = cur_dance(state);
  switch (cn_state.state) {
    case SINGLE_HOLD: layer_on(_NAV); break;
  }
}

void cn_reset (qk_tap_dance_state_t *state, void *user_data) {
  switch (cn_state.state) {
    case SINGLE_HOLD: layer_off(_NAV); break;
    case DOUBLE_TAP: default_layer_set(0x00000001); break;
  }
  cn_state.state = 0;
}

qk_tap_dance_action_t tap_dance_actions[] = {
  [aw]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, aw_finished, aw_reset),
  [eaw]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, eaw_finished, eaw_reset),
  [navnum]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, navnum_finished, navnum_reset),
  [ptt]     = ACTION_TAP_DANCE_FN_ADVANCED(NULL, ptt_finished, ptt_reset),
  [gn]     = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, gn_finished, gn_reset, 300),
  [cn]     = ACTION_TAP_DANCE_FN_ADVANCED_TIME(NULL, cn_finished, cn_reset, 300),
};

