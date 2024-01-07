#ifndef __GLOBAL_H__
#define __GLOBAL_H__

#include <U8g2lib.h>

constexpr uint8_t BUTTON_PIN = 2;
extern U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g;
extern bool swapDisplayBuffer;

#endif