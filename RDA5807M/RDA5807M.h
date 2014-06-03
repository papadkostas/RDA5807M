//--------------------------------------------------------------
// File     : RDA5807M.h
//--------------------------------------------------------------
//--------------------------------------------------------------
#ifndef __RDA5807M_H
#define __RDA5807M_H

//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include <stdio.h>
#include "stm32_ub_led.h"
#include "stm32_ub_i2c3.h"

//--------------------------------------------------------------
// Global Functions
//--------------------------------------------------------------
void RDA5807_Dump(void);
int8_t RDA5807_Init(void);
int8_t RDA5807_Read(void);
int8_t RDA5807_Reset(void);
int8_t RDA5807_PowerOn(void);
int8_t RDA5807_PowerOff(void);
int8_t RDA5807_RDS(void);
int8_t RDA5807_Mute(void);
int8_t RDA5807_Mono(void);
int8_t RDA5807_Softmute(void);
int8_t RDA5807_SoftBlend(void);
int8_t RDA5807_BassBoost(void);
int8_t RDA5807_Volume(uint8_t volume);
int8_t RDA5807_SeekUp(void);
int8_t RDA5807_SeekDown(void);
int8_t RDA5807_Frequency(float Freq);
int RDA5807_Channel(void);

//--------------------------------------------------------------
// Definitions
//--------------------------------------------------------------
#define RDASequential 	0x10
#define RDARandom  		0x11

#define StartingFreq 	87.000
#define EndingFreq 		108.00
#define DefaultFreq		87.000
#define StartingVolume 	0x4

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
//
int rdsready;
int tuneok;
int nochannel;
int rdssynchro;
int stereo;
int freq;
int signal;
int fmready;
int fmstation;
int rdsblockerror;
unsigned int RDA5807M_WriteReg[8],RDA5807M_ReadReg[7],RDA5807M_RDS[32];

//--------------------------------------------------------------
#endif // __RDA5807M_H
