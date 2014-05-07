#include "RDA5807M.h"
//--------------------------------------------------------------
// Private Values
//--------------------------------------------------------------
unsigned int RDA5807M_Regdef[10] ={
                                    0xD009,  // 02 DHIZ,DMUTE,BASS, POWERUPENABLE,RDS
                                    0x26D0,  // 03
                                    0x1400,  // 04 DE ? SOFTMUTE
                                    0x84DF,  // 05 INT_MODE,SEEKTH=0110,????, Volume=15
                                    0x4000,  // 06 OPENMODE=01
                                    0x0000,  // 07 unused ?
                                    };
unsigned int RDA5807M_Reg[10];

//--------------------------------------------------------------
// Private Functions
//--------------------------------------------------------------

int RDA5807_WriteAll(){
	int i,x = 0;
	for(i=0; i<12; i=i+2){
		I2C3_DATA[i] = RDA5807M_Regdef[x] >> 8;
		x++;
	}
	x = 0;
	for(i=1; i<13; i=i+2){
		I2C3_DATA[i] = RDA5807M_Regdef[x] & 0xFF;
		x++;
	}
	status = UB_I2C3_WriteMultiByte(RDAaddress<<1,0x00,12,1);
	return status;
}

int RDA5807_WriteReg(uint8_t reg){
	I2C3_DATA[0] = RDA5807M_Regdef[reg] >> 8;
	I2C3_DATA[1] = RDA5807M_Regdef[reg] & 0xFF;
	status = UB_I2C3_WriteMultiByte(RDAaddress<<1,reg,1,0);
	return status;
}
