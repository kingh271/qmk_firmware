#pragma once

/* Select hand configuration */

#define MASTER_LEFT
// #define MASTER_RIGHT
//#define EE_HANDS

#undef USE_I2C
#undef SSD1306OLED

#define USE_SERIAL_PD2

#define TAPPING_FORCE_HOLD
#define TAPPING_TERM 190

#define TAP_CODE_DELAY 100

#define OLED_DISABLE_TIMEOUT

#define ENCODERS_PAD_A { F4 }
#define ENCODERS_PAD_B { F5 }
#define ENCODER_RESOLUTION 4

//Custom keycodes
