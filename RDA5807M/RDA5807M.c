#include "RDA5807M.h"
//--------------------------------------------------------------
// Local Variables
//--------------------------------------------------------------
int8_t status;
unsigned int RDA5807M_WriteRegDef[6] ={
                                    	0xD009,  // 02 DHIZ,DMUTE,BASS, POWERUPENABLE,RDS
                                    	0x26D0,  // 03
                                    	0x1400,  // 04 DE ? SOFTMUTE
                                    	0x84DF,  // 05 INT_MODE,SEEKTH=0110,????, Volume=15
                                    	0x4000,  // 06 OPENMODE=01
                                    	0x0000  // 07 unused ?
                                    	};
unsigned int RDA5807M_WriteReg[6],RDA5807M_ReadReg[6];

int8_t RDA5807_WriteAll(){
	int i,x = 0;
	for(i=0; i<12; i=i+2){
		I2C3_DATA[i] = RDA5807M_WriteReg[x] >> 8;
		x++;
	}
	x = 0;
	for(i=1; i<13; i=i+2){
		I2C3_DATA[i] = RDA5807M_WriteReg[x] & 0xFF;
		x++;
	}
	status = UB_I2C3_WriteMultiByte(RDAaddress<<1,0x00,11,1);
	return status;
}

int8_t RDA5807_WriteReg(uint8_t address,uint16_t data){
	I2C3_DATA[0] = data >> 8;
	I2C3_DATA[1] = data & 0xFF;
	status = UB_I2C3_WriteMultiByte(RDAaddress<<1,address,1,0);
	return status;
}

int8_t RDA5807_Init(){
	int i;
	for(i=0; i<6; i++){
		RDA5807M_WriteReg[i] = RDA5807M_WriteRegDef[i];
	}
	status = RDA5807_WriteAll();
	return status;
}

int8_t RDA5807_PowerToogle(){
	RDA5807M_WriteReg[2] = RDA5807M_WriteReg[1] | 0x10;
	RDA5807M_WriteReg[0] = RDA5807M_WriteReg[0] ^ 0x01;
	status = RDA5807_WriteReg(0x01,RDA5807M_WriteReg[0]);
	status = RDA5807_WriteReg(0x02,RDA5807M_WriteReg[2]);
	RDA5807M_WriteReg[0] = RDA5807M_WriteReg[1] & 0xEF;
	return status;
}
