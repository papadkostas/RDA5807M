//--------------------------------------------------------------
// File     : RDA5807M.h
//--------------------------------------------------------------
//--------------------------------------------------------------
#ifndef __RDA5807M_H
#define __RDA5807M_H

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32_ub_lcd_ili9341.h"
#include "stm32_ub_font.h"
#include "stm32_ub_i2c3.h"
#include <stdio.h>

//--------------------------------------------------------------
// Global Functions
//--------------------------------------------------------------

int8_t RDA5807_Init();
int8_t RDA5807_PowerToogle();

//--------------------------------------------------------------
// Definitions
//--------------------------------------------------------------
#define RDAaddress 0x10

/* Register 0x00H (16Bits) */
#define RDA_CHIP_ID     0x0058

/* Register 0x02H (16Bits) */
#define RDA_DHIZ        0x8000
#define RDA_MUTE        0x4000
#define RDA_MONO        0x2000
#define RDA_BASS        0x1000
#define RDA_RCLK_MODE   0x0800
#define RDA_RCLK_DIRECT 0x0400
#define RDA_SEEK_UP     0x0200
#define RDA_SEEK_EN     0x0100
#define RDA_SEEK_MODE   0x0080
#define RDA_CLK_0327    0x0000
#define RDA_CLK_1200    0x0010
#define RDA_CLK_2400    0x0050
#define RDA_CLK_1300    0x0020
#define RDA_CLK_2600    0x0060
#define RDA_CLK_1920    0x0030
#define RDA_CLK_3840    0x0070
#define RDA_RDS_EN      0x0008
#define RDA_NEW         0x0004
#define RDA_RESET       0x0002
#define RDA_POWER       0x0001

//--------------------------------------------------------------
// Global Variables
//--------------------------------------------------------------

//--------------------------------------------------------------
#endif // __RDA5807M_H
