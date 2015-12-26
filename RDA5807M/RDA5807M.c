#include "RDA5807M.h"
#include <string.h>
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
	return RDAstatus = UB_I2C3_WriteMultiByte(RDARandom<<1,address,2,0);
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

int8_t RDA5807_RDSinit(){
  strcpy(StationName, "--------");
  strcpy(PSName, "        ");
  strcpy(PSName1, "        ");
  strcpy(PSName2, "        ");
  memset(RDStext, '\0', sizeof(RDStext));
  memset(RDStextbuffer, '\0', sizeof(RDStextbuffer));
  lastTextIDX = 0;
  mins=0;
  sprintf(CTtime, "CT --:--");
  return RDAstatus;
}

int8_t RDA5807_Read(){  // Read all RDA5807 registers
	UB_Led_On(LED_GREEN);
	int8_t i;
	RDAstatus = UB_I2C3_ReadMultiByte(RDASequential<<1,0x00,14,0);
	for(i=0; i<6; i++){
		RDA5807M_ReadReg[i] = ((I2C3_DATA[i *2] << 8) | I2C3_DATA [(i*2) +1] );
	}

	block1 = RDA5807M_ReadReg[2];  //RDS Text data blocks
	block2 = RDA5807M_ReadReg[3];
	block3 = RDA5807M_ReadReg[4];
	block4 = RDA5807M_ReadReg[5];

	rdsready = RDA5807M_ReadReg[0] & 0x8000;			//if rdsready != 0 rds data are ready
	tuneok = RDA5807M_ReadReg[0] & 0x4000;				//if tuneok != 0 seek/tune completed
	nochannel = RDA5807M_ReadReg[0] & 0x2000;			//if nochannel != 0 no channel found
	rdssynchro = RDA5807M_ReadReg[0] & 0x1000;			//if rdssynchro = 1000 rds decoder syncrhonized
	stereo = RDA5807M_ReadReg[0] & 0x0400; 				//if stereo = 0 station is mono else stereo
	freq = (((RDA5807M_ReadReg[0] & 0x03FF) * 100) + 87000);	//return freq ex 102600KHz > 102.6MHz
	signal = RDA5807M_ReadReg[1] >> 10;					//return signal strength rssi
	fmready = RDA5807M_ReadReg[1] & 0x0008; 			//if fmready = 8 > fm is ready
	fmstation = RDA5807M_ReadReg[1] & 0x0100; 			//if fmstation = 100 fm station is true
	rdsblockerror = RDA5807M_ReadReg[1] & 0x000C;		//check for rds blocks errors
														//00= 0 errors,01= 1~2 errors requiring correction
														//10= 3~5 errors requiring correction
														//11= 6+ errors or error in checkword, correction not possible.

	if (rdssynchro != 0x1000){  // RDS not synchronised or tuning changed, reset all the RDS info.
		RDA5807_RDSinit();
	}
	// analyzing Block 2
	rdsGroupType = 0x0A | ((block2 & 0xF000) >> 8) | ((block2 & 0x0800) >> 11);
	rdsTP = (block2 & 0x0400);
	rdsPTY = (block2 & 0x0400);
	    switch (rdsGroupType) {
	        case 0x0A:
	        case 0x0B:
	        // The data received is part of the Service Station Name
	        idx = 2 * (block2 & 0x0003);
	        // new data is 2 chars from block 4
	        c1 = block4 >> 8;
	        c2 = block4 & 0x00FF;
	        // check that the data was received successfully twice
	        // before sending the station name
	        if ((PSName1[idx] == c1) && (PSName1[idx + 1] == c2)) {
	            // retrieve the text a second time: store to _PSName2
	            PSName2[idx] = c1;
	            PSName2[idx + 1] = c2;
	            PSName2[8] = '\0';
	            if (strcmp(PSName1, PSName2) == 0) {
	                // populate station name
	            	int8_t n=0;
	                for(i=0;i<(8);i++){ // remove non-printable error ASCCi characters
	                    if(PSName2[i] > 31 && PSName2[i] < 127){
	                        StationName[n] = PSName2[i];
	                        n++;
	                    }
	                }
	            }
	        }
	        if ((PSName1[idx] != c1) || (PSName1[idx + 1] != c2)) {
	            PSName1[idx] = c1;
	            PSName1[idx + 1] = c2;
	            PSName1[8] = '\0';
	        }
	    break;

	    case 0x2A:
// RDS text
	    textAB = (block2 & 0x0010);
	    idx = 4 * (block2 & 0x000F);
	    if (idx < lastTextIDX) {
	      // The existing text might be complete because the index is starting at the beginning again.
	      // Populate RDS text array.
	    	int8_t n=0;
	        for(i=0;i<strlen(RDStextbuffer);i++){
	            if(RDStextbuffer[i] > 31 && RDStextbuffer[i] < 127){    // remove non printable error characters
	                RDStext[n] = RDStextbuffer[i];
	                n++;
	            }
	        }
	      }
	    lastTextIDX = idx;
	    if (textAB != lasttextAB) {
	      // when this bit is toggled text data has changed, the whole buffer should be cleared.
	      lasttextAB = textAB;
	      if(signal>35){  // clear buffer if higher signal level to prevent spurious text blanking with error characters.
	    	  memset(RDStextbuffer, 0, sizeof(RDStextbuffer));
	      	  memset(RDStext, '\0', sizeof(RDStext));
	      }
	    }
	    if(rdsblockerror < 4){ // limit RDS data errors as we have no correction code
	        // new data is 2 chars from block 3
	    	RDStextbuffer[idx] = (block3 >> 8);     idx++;
	    	RDStextbuffer[idx] = (block3 & 0x00FF); idx++;
	        // new data is 2 chars from block 4
	    	RDStextbuffer[idx] = (block4 >> 8); idx++;
	    	RDStextbuffer[idx] = (block4 & 0x00FF); idx++;
	    }
	    break;

	  case 0x4A:
// Clock time and date
	    if(rdsblockerror <3){ // limit RDS data errors as we have no correction code
	        offset = (block4) & 0x3F; // 6 bits
	        mins = (block4 >> 6) & 0x3F; // 6 bits
	        mins += 60 * (((block3 & 0x0001) << 4) | ((block4 >> 12) & 0x0F));
	    }
	    // adjust offset
	    if (offset & 0x20) {
	      mins -= 30 * (offset & 0x1F);
	    }
	    else {
	      mins += 30 * (offset & 0x1F);
	    }

	    if(mins>0 && mins<1500){
	    	sprintf(CTtime, "CT %2d:%02d",(mins/60),(mins%60));  // CT time formatted string
	    }

	    break;

	  case 0x6A:
	    // IH
	    break;

	  case 0x8A:
	    // TMC
	    break;

	  case 0xAA:
	    // TMC
	    break;

	  case 0xCA:
	    // TMC
	    break;

	  case 0xEA:
	    // IH
	    break;

	  default:

	    break;
	  }

	UB_Led_Off(LED_GREEN);
	return RDAstatus;
}
