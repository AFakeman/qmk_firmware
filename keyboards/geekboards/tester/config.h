#pragma once

#include "config_common.h"


#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x1319
#define DEVICE_VER      0x0001
#define MANUFACTURER    Geekboards
#define PRODUCT         Geekboards Tester
#define DESCRIPTION     Geekboards 8-keys macropad


#define MATRIX_ROWS 2
#define MATRIX_COLS 4

#define MATRIX_ROW_PINS { B0, D4}
#define MATRIX_COL_PINS { F7, F6, D2, D3}
#define UNUSED_PINS

#define DIODE_DIRECTION COL2ROW
#define LOCKING_SUPPORT_ENABL
#define LOCKING_RESYNC_ENABLE

#define DEBOUNCE 3
#define RGB_DISABLE_AFTER_TIMEOUT 0
#define RGB_DISABLE_WHEN_USB_SUSPENDED true
#define RGB_MATRIX_KEYPRESSES
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_NONE
#define DISABLE_RGB_MATRIX_SPLASH
#define DISABLE_RGB_MATRIX_MULTISPLASH
#define DISABLE_RGB_MATRIX_SOLID_SPLASH
#define DISABLE_RGB_MATRIX_SOLID_MULTISPLASH
#define DRIVER_ADDR_1 0b1110100
#define DRIVER_ADDR_2 0b1110101

#define DRIVER_COUNT 2
#define DRIVER_1_LED_TOTAL 8
#define DRIVER_2_LED_TOTAL 0
#define DRIVER_LED_TOTAL (DRIVER_1_LED_TOTAL + DRIVER_2_LED_TOTAL)
