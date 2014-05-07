//--------------------------------------------------------------
// File     : stm32_ub_l3gd20.h
//--------------------------------------------------------------

//--------------------------------------------------------------
#ifndef __STM32F4_UB_L3GD20_H
#define __STM32F4_UB_L3GD20_H


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h" 
#include "stm32_ub_spi5.h" 



// Auflösung
typedef enum {
  SCALE_250 = 0,  // 250
  SCALE_500,      // 500
  SCALE_2000      // 2000
}L3GD20_SCALE_t;



// L3GD20-Drehraten-Daten
typedef struct {
  int16_t x_achse; // Drehrate der X-Achse
  int16_t y_achse; // Drehrate der Y-Achse
  int16_t z_achse; // Drehrate der Z-Achse
}L3GD20_t;
L3GD20_t L3GD20; 



// L3GD20-Roh-Daten
typedef struct {
  float faktor;      // Auflösungsfaktor
  int16_t x_achse;   // Rohdaten der X-Achse
  int16_t y_achse;   // Rohdaten der Y-Achse
  int16_t z_achse;   // Rohdaten der Z-Achse
}L3GD20_RAW_t;
L3GD20_RAW_t L3GD20_RAW;



//--------------------------------------------------------------
// SPI Chip-Select-Pin
//--------------------------------------------------------------
#define L3GD20_CS_PIN             GPIO_Pin_1
#define L3GD20_CS_GPIO_PORT       GPIOC
#define L3GD20_CS_GPIO_CLK        RCC_AHB1Periph_GPIOC


//--------------------------------------------------------------
// L3GD20 Defines
//-------------------------------------------------------------- 
#define  L3GD20_ID           0xD4   // ID vom L3GD20 IC
#define  L3GD20_PWR_ON       0x3F   // L3GD20 On
#define  L3GD20_SCALE_250    0x00   // Auflösung 250
#define  L3GD20_SCALE_500    0x10   // Auflösung 500
#define  L3GD20_SCALE_2000   0x20   // Auflösung 2000
#define  L3GD20_FILTER       0x00   // Filter Einstellung
#define  L3GD20_FILTER_ON    0x10   // Filter On

#define  L3GD20_SPI_PAUSE      10   // kleine Pause bei SPI

#define  L3GD20_250_FAKTOR    114.285  // 8.75mdps pro Digit
#define  L3GD20_500_FAKTOR    57.1429  // 17.5mdps pro Digit
#define  L3GD20_2000_FAKTOR   14.285   // 70mdps pro Digit


//--------------------------------------------------------------
// Register Adressen
//--------------------------------------------------------------
#define L3GD20_ADR_ID             0x0F
#define L3GD20_ADR_REG1           0x20
#define L3GD20_ADR_REG2           0x21
#define L3GD20_ADR_REG4           0x23
#define L3GD20_ADR_REG5           0x24
#define L3GD20_ADR_X_LO           0x28
#define L3GD20_ADR_X_HI           0x29
#define L3GD20_ADR_Y_LO           0x2A
#define L3GD20_ADR_Y_HI           0x2B
#define L3GD20_ADR_Z_LO           0x2C
#define L3GD20_ADR_Z_HI           0x2D


//--------------------------------------------------------------
// Globale Funktionen
//--------------------------------------------------------------
ErrorStatus UB_L3GD20_Init(L3GD20_SCALE_t scale);
void UB_L3GD20_Read(void);




//--------------------------------------------------------------
#endif // __STM32F4_UB_L3GD20_H
