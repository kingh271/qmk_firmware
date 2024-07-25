#pragma once
#include "kingh271.h"

//Tap dance stuff
typedef struct {
  bool is_press_action;
  int state;
} tap;

enum {
  SINGLE_TAP = 1,
  SINGLE_HOLD = 2,
  DOUBLE_TAP = 3,
  DOUBLE_HOLD = 4,
  DOUBLE_SINGLE_TAP = 5, //send two single taps
  TRIPLE_TAP = 6,
  TRIPLE_HOLD = 7
};

//Tap dance enums
enum {
  aw = 0,
  eaw,
  navnum,
  ptt,
  gn,
  cn
};

//Custom keycodes
#define ALT_WIN TD(aw)
#define EALTWIN TD(eaw)
#define PTT TD(ptt)
#define GAME_NAV TD(gn)
#define COLE_NAV TD(cn)