//--------------------------------------------------------------
// File     : stm32_ub_l3gd20.c
// Datum    : 07.11.2013
// Version  : 1.0
// Autor    : UB
// EMail    : mc-4u(@)t-online.de
// Web      : www.mikrocontroller-4u.de
// CPU      : STM32F429
// IDE      : CooCox CoIDE 1.7.4
// GCC      : 4.7 2012q4
// Module   : GPIO, STM32_UB_SPI5
// Funktion : 3-Achs-Drehraten-Sensor [Gyro] (Chip=L3GD20)
//
// Hinweis  : Der Sensor benutzt die CPU-Pins : 
//              PC1 = SPI_CS
//              PF7 = SPI_CLK
//              PF8 = SPI_MISO
//              PF9 = SPI_MOSI
//
// SPI-Settings :  SPI-Mode = SPI_MODE_0_MSB, FRQ-Max = 10MHz
//                 SPI5 [CLK=PF7, MOSI=PF9, MISO=PF8]
//                 Chip-Select an PC1
//--------------------------------------------------------------


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32_ub_l3gd20.h"



//--------------------------------------------------------------
// interne Funktionen
//--------------------------------------------------------------
void P_L3GD20_InitIO(void);
void P_L3GD20_CS(BitAction wert);
void P_L3GD20_InitChip(L3GD20_SCALE_t scale);
void P_L3GD20_WriteReg(uint8_t adr, uint8_t wert);
uint8_t P_L3GD20_ReadReg(uint8_t adr);
void P_L3GD20_Delay(volatile uint32_t nCount);




//--------------------------------------------------------------
// Init vom L3GD20
// scale : [SCALE_250, SCALE_500, SCALE_2000]
// Return_wert :
//  -> ERROR   , wenn Initialisierung fehlgeschlagen
//  -> SUCCESS , wenn Initialisierung ok war
//--------------------------------------------------------------
ErrorStatus UB_L3GD20_Init(L3GD20_SCALE_t scale)
{
  ErrorStatus ret_wert=ERROR;
  uint8_t wert;

  // Init aller Variabeln
  L3GD20.x_achse=0;
  L3GD20.y_achse=0;
  L3GD20.z_achse=0; 
  L3GD20_RAW.faktor=1.0;
  L3GD20_RAW.x_achse=0;
  L3GD20_RAW.y_achse=0;
  L3GD20_RAW.z_achse=0;

  // init aller IO-Pins
  P_L3GD20_InitIO();
  // init vom SPI-BUS
  ret_wert=UB_SPI5_Init(SPI_MODE_0_MSB);
  if(ret_wert==SUCCESS) {
    // auslesen vom Identifier
    wert=P_L3GD20_ReadReg(L3GD20_ADR_ID);
    if(wert!=L3GD20_ID) {
      // empfangene ID ist falsch
      ret_wert=ERROR;
    }
    else {
      // ID ist richtig
      // L3GD20 initialisieren
      P_L3GD20_InitChip(scale);
    }
  }

  return(ret_wert);
}


//--------------------------------------------------------------
// Auslesen vom L3GD20 und fuellen der Struktur "L3GD20"
// (die Funktion muss zyklisch aufgerufen werden) 
//   L3GD20.x_achse => Drehrate der X-Achse
//   L3GD20.y_achse => Drehrate der Y-Achse
//   L3GD20.z_achse => Drehrate der Z-Achse
//--------------------------------------------------------------
void UB_L3GD20_Read(void)
{
  uint8_t wert_lo, wert_hi;
  int16_t raw_wert;
  float f;

  // X-Achse auslesen
  wert_lo=P_L3GD20_ReadReg(L3GD20_ADR_X_LO);
  wert_hi=P_L3GD20_ReadReg(L3GD20_ADR_X_HI);
  raw_wert=(int16_t)((wert_hi<<8)|(wert_lo));
  L3GD20_RAW.x_achse=raw_wert;
  // umrechnen
  f=(float)(raw_wert)/L3GD20_RAW.faktor;
  L3GD20.x_achse=(int16_t)(f);

  // Y-Achse auslesen
  wert_lo=P_L3GD20_ReadReg(L3GD20_ADR_Y_LO);
  wert_hi=P_L3GD20_ReadReg(L3GD20_ADR_Y_HI);
  raw_wert=(int16_t)((wert_hi<<8)|(wert_lo));
  L3GD20_RAW.y_achse=raw_wert;
  // umrechnen
  f=(float)(raw_wert)/L3GD20_RAW.faktor;
  L3GD20.y_achse=(int16_t)(f);

  // Z-Achse auslesen
  wert_lo=P_L3GD20_ReadReg(L3GD20_ADR_Z_LO);
  wert_hi=P_L3GD20_ReadReg(L3GD20_ADR_Z_HI);
  raw_wert=(int16_t)((wert_hi<<8)|(wert_lo));
  L3GD20_RAW.z_achse=raw_wert;
  // umrechnen
  f=(float)(raw_wert)/L3GD20_RAW.faktor;
  L3GD20.z_achse=(int16_t)(f);
}


//--------------------------------------------------------------
// interne Funktion
// Init aller IO-Pins fuer den L3GD20
//--------------------------------------------------------------
void P_L3GD20_InitIO(void)
{	
  GPIO_InitTypeDef       GPIO_InitStructure;

  // ChipSelect-Pin
  RCC_AHB1PeriphClockCmd(L3GD20_CS_GPIO_CLK, ENABLE);
	  
  GPIO_InitStructure.GPIO_Pin = L3GD20_CS_PIN;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(L3GD20_CS_GPIO_PORT, &GPIO_InitStructure);	

  P_L3GD20_CS(Bit_SET);
}


//--------------------------------------------------------------
// interne Funktion
// ChipSelect-Pin schalten
// wert [Bit_SET, Bit_RESET]
//--------------------------------------------------------------
void P_L3GD20_CS(BitAction wert)
{
  if (wert == Bit_RESET) {
    L3GD20_CS_GPIO_PORT->BSRRH = L3GD20_CS_PIN;
  }
  else {
    L3GD20_CS_GPIO_PORT->BSRRL = L3GD20_CS_PIN;
  }
}


//--------------------------------------------------------------
// interne Funktion
// init vom L3GD20
// scale : [SCALE_250, SCALE_500, SCALE_2000]
//--------------------------------------------------------------
void P_L3GD20_InitChip(L3GD20_SCALE_t scale)
{

  // L3GD20 einschalten
  P_L3GD20_WriteReg(L3GD20_ADR_REG1, L3GD20_PWR_ON);

  // Aufloesung einstellen
  if(scale==SCALE_250) {
    P_L3GD20_WriteReg(L3GD20_ADR_REG4, L3GD20_SCALE_250);
    L3GD20_RAW.faktor=L3GD20_250_FAKTOR;
  }
  else if(scale==SCALE_500) {
    P_L3GD20_WriteReg(L3GD20_ADR_REG4, L3GD20_SCALE_500);
    L3GD20_RAW.faktor=L3GD20_500_FAKTOR;
  }
  else {
    P_L3GD20_WriteReg(L3GD20_ADR_REG4, L3GD20_SCALE_2000);
    L3GD20_RAW.faktor=L3GD20_2000_FAKTOR;
  }

  // Filter einstellen
  P_L3GD20_WriteReg(L3GD20_ADR_REG2, L3GD20_FILTER);

  // Filter enable
  P_L3GD20_WriteReg(L3GD20_ADR_REG5, L3GD20_FILTER_ON);
}


//--------------------------------------------------------------
// interne Funktion
// Daten per SPI an L3GD20 senden
//--------------------------------------------------------------
void P_L3GD20_WriteReg(uint8_t adr, uint8_t wert)
{
  // ChipSelect auf Lo
  P_L3GD20_CS(Bit_RESET);

  // Adresse senden (zum schreiben)
  UB_SPI5_SendByte(adr);

  // Wert senden
  UB_SPI5_SendByte(wert);

  // kleine Pause
  P_L3GD20_Delay(L3GD20_SPI_PAUSE);
 
  // ChipSelect auf Hi
  P_L3GD20_CS(Bit_SET);
}


//--------------------------------------------------------------
// interne Funktion
// Daten per SPI von L3GD20 auslesen
//--------------------------------------------------------------
uint8_t P_L3GD20_ReadReg(uint8_t adr)
{
  uint8_t ret_wert=0;

  // ChipSelect auf Lo
  P_L3GD20_CS(Bit_RESET);

  // Adresse senden (zum lesen)
  adr|=0x80;
  UB_SPI5_SendByte(adr);

  // Wert auslesen
  ret_wert=UB_SPI5_SendByte(0x55);

  // kleine Pause
  P_L3GD20_Delay(L3GD20_SPI_PAUSE);
 
  // ChipSelect auf Hi
  P_L3GD20_CS(Bit_SET);

  return(ret_wert);
}


//--------------------------------------------------------------
// interne Funktion
// kleine Pause
//-------------------------------------------------------------- 
void P_L3GD20_Delay(volatile uint32_t nCount)
{
  volatile uint32_t index = 0;

  for(index = nCount; index != 0; index--);
}
