#include "RDA5807M.h"
//--------------------------------------------------------------
// Local Variables
//--------------------------------------------------------------
int volume;
int RDAstatus = 0;
unsigned int RDA5807M_WriteRegDef[6] ={0xC004,0x0000,0x0100,0x84D4,0x4000,0x0000};
int8_t RDA5807_WriteReg(uint8_t address,uint16_t data);

void RDA5807_ErrorHandler(){
	switch(RDAstatus){
	case -1:
		//I2C start flag failed
		break;
	case -2:
		//I2C slave address does not match
		break;
	case -3:
		//I2C data register is not empty
		break;
	case -4:
		//I2C end transmission flag, nothing transmitted
		break;
	case -5:
		break;
	}
}
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
	return RDAstatus = UB_I2C3_WriteMultiByte(RDASequential<<1,0x00,11,1);
}

int8_t RDA5807_WriteReg(uint8_t address,uint16_t data){
	I2C3_DATA[0] = data >> 8;
	I2C3_DATA[1] = data & 0xFF;
	return RDAstatus = UB_I2C3_WriteMultiByte(RDASequential<<1,address,1,0);
}

int8_t RDA5807_Init(){
	int i;
	for(i=0; i<6; i++){
		RDA5807M_WriteReg[i] = RDA5807M_WriteRegDef[i];
	}
	RDAstatus = RDA5807_Volume(StartingVolume);
	return RDAstatus = RDA5807_Frequency(DefaultFreq);
}

int8_t RDA5807_PowerOn(){
	RDA5807M_WriteReg[1] = RDA5807M_WriteReg[1] | 0x0010;
	RDA5807M_WriteReg[0] = RDA5807M_WriteReg[0] | RDA_POWER;
	RDAstatus = RDA5807_WriteAll();
	RDA5807M_WriteReg[1] = RDA5807M_WriteReg[1] & 0xFFEF;	//Disable tune after PowerOn operation
	return RDAstatus;
}

int8_t RDA5807_PowerOff(){
	RDA5807M_WriteReg[0] = RDA5807M_WriteReg[0] ^ RDA_POWER;
	return RDAstatus = RDA5807_WriteAll();
}

int8_t RDA5807_Reset(){
	RDAstatus = RDA5807_Init();
	RDAstatus = RDA5807_PowerOn();
	return RDAstatus;
}

int8_t RDA5807_Volume(uint8_t vol){
	if(vol > 15){
		vol = 15;
		return 1;			//Volume is already at 15 level
	}
	if(vol < 0){
		vol = 0;
		return 2;			//Volume is already at 0 level
	}
	RDA5807M_WriteReg[3] = (RDA5807M_WriteReg[3] & 0xFFF0)| vol;   // Set New Volume
	return RDAstatus = RDA5807_WriteAll();
}

int8_t RDA5807_BassBoost(){
    if ((RDA5807M_WriteReg[0] & 0x1000)==0){
    	RDA5807M_WriteReg[0] = RDA5807M_WriteReg[0] | RDA_BASS_ON;
    }
    else{
    	RDA5807M_WriteReg[0] = RDA5807M_WriteReg[0] & RDA_BASS_OFF;
    }
    return RDAstatus = RDA5807_WriteAll();
}

int8_t RDA5807_Mono(){
    if ((RDA5807M_WriteReg[0] & 0x2000)==0){
    	RDA5807M_WriteReg[0] = RDA5807M_WriteReg[0] | RDA_MONO_ON;
    }
    else{
    	RDA5807M_WriteReg[0] = RDA5807M_WriteReg[0] & RDA_MONO_OFF;
    }
    return RDAstatus = RDA5807_WriteAll();
}

int8_t RDA5807_Mute(){
    if ((RDA5807M_WriteReg[0] & 0x8000)==0){
    	RDA5807M_WriteReg[0] = RDA5807M_WriteReg[0] | 0x8000;
    }
    else{
    	RDA5807M_WriteReg[0] = RDA5807M_WriteReg[0] & 0x7FFF;
    }
    return RDAstatus = RDA5807_WriteAll();
}

int8_t RDA5807_Softmute(){
    if ((RDA5807M_WriteReg[2] & 0x0200)==0){
    	RDA5807M_WriteReg[2] = RDA5807M_WriteReg[2] | 0x0200;
    }
    else{
    	RDA5807M_WriteReg[2] = RDA5807M_WriteReg[2] & 0xFDFF;
    }
    return RDAstatus = RDA5807_WriteAll();
}

int8_t RDA5807_SoftBlend(){
    if ((RDA5807M_WriteReg[6] & 0x0001)==0){
    	RDA5807M_WriteReg[6] = RDA5807M_WriteReg[6] | 0x0001;
    }
    else{
    	RDA5807M_WriteReg[6] = RDA5807M_WriteReg[6] & 0xFFFE;
    }
    return RDAstatus = RDA5807_WriteAll();
}

int8_t RDA5807_SeekUp(){
	RDA5807M_WriteReg[0] = RDA5807M_WriteReg[0] | RDA_SEEK_UP;   // Set Seek Up
	RDAstatus = RDA5807_WriteAll();
	RDA5807M_WriteReg[0] = RDA5807M_WriteReg[0] & RDA_SEEK_STOP;   // Disable Seek
	return RDAstatus;
}

int8_t RDA5807_SeekDown(){
	RDA5807M_WriteReg[0] = RDA5807M_WriteReg[0] | RDA_SEEK_DOWN;   // Set Seek Down
	RDAstatus = RDA5807_WriteAll();
	RDA5807M_WriteReg[0] = RDA5807M_WriteReg[0] & RDA_SEEK_STOP;   // Disable Seek
	return RDAstatus;
}

int8_t RDA5807_Frequency(float Freq){
	int Channel;
	Channel = (Freq-StartingFreq)/0.1;
	Channel = Channel & 0x03FF;
	RDA5807M_WriteReg[1] = Channel*64 +0x10;  // Channel + TUNE-Bit + Band=00(87-108) + Space=00(100kHz)
	RDAstatus = RDA5807_WriteAll();
	RDA5807M_WriteReg[1] = RDA5807M_WriteReg[1] & RDA_TUNE_OFF;
	return RDAstatus;
}

int8_t RDA5807_RDS(){
    if ((RDA5807M_WriteReg[0] & RDA_RDS_ON)==0){
    	RDA5807M_WriteReg[0] = RDA5807M_WriteReg[0] | RDA_RDS_ON;
    }
    else{
    	RDA5807M_WriteReg[0] = RDA5807M_WriteReg[0] & RDA_RDS_OFF;
    }
    return RDAstatus = RDA5807_WriteAll();
}

int8_t RDA5807_Read(){
	UB_Led_On(LED_GREEN);
	int8_t i,x=0;
	RDAstatus = UB_I2C3_ReadMultiByte(RDASequential<<1,0x00,14,0);
	for(i=0; i<13; i=i+2){
		RDA5807M_ReadReg[x] = I2C3_DATA[i];
		RDA5807M_ReadReg[x] = RDA5807M_ReadReg[x] << 8;
		x++;
	}
	x = 0;
	for(i=1; i<14; i=i+2){
		RDA5807M_ReadReg[x] = RDA5807M_ReadReg[x] | I2C3_DATA[i];
		x++;
	}
	rdsready = RDA5807M_ReadReg[0] & 0x8000;					//if rdsready != 0 rds data are ready
	tuneok = RDA5807M_ReadReg[0] & 0x4000;						//if tuneok != 0 seek/tune completed
	nochannel = RDA5807M_ReadReg[0] & 0x2000;					//if nochannel != 0 no channel found
	rdssynchro = RDA5807M_ReadReg[0] & 0x1000;					//if rdssynchro = 1000 rds decoder syncrhonized
	stereo = RDA5807M_ReadReg[0] & 0x0400; 						//if stereo = 0 station is mono else stereo
	freq = (((RDA5807M_ReadReg[0] & 0x03FF) * 100) + 87000);	//return freq ex 102600KHz > 102.6MHz
	signal = RDA5807M_ReadReg[1] >> 10;							//return signal strength rssi
	fmready = RDA5807M_ReadReg[1] & 0x0008; 					//if fmready = 8 > fm is ready
	fmstation = RDA5807M_ReadReg[1] & 0x0100; 					//if fmstation = 100 fm station is true
	rdsblockerror = RDA5807M_ReadReg[1] & 0x000C;				//check for rds blocks errors
																//00= 0 errors,01= 1~2 errors requiring correction
																//10= 3~5 errors requiring correction
																//11= 6+ errors or error in checkword, correction not possible.
	UB_Led_Off(LED_GREEN);
	return RDAstatus;
}
