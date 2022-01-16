#pragma once
#include QMK_KEYBOARD_H


#include "version.h"
#ifdef TAP_DANCE_ENABLE
#    include "tap_dances.h"
#endif
#include "keycodes.h"

enum userspace_layers {
  _COLEMAK = 0,
  _GAME,
  _QWERTY,
  _NUM,
  _NAV,
  _FN
};