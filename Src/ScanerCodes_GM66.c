#include "..\Inc\ScanerCodes_GM66.h"
#include "stdint.h"


/*******************************************************************/
//Calculate CRC
//
unsigned int crc_cal_by_bit(uint8_t* ptr, unsigned int len)
{ 
unsigned int crc = 0;
	while(len-- != 0)
	{ 
		for(uint8_t i = 0x80; i != 0; i /= 2)
		{ crc *= 2;
			if((crc&0x10000) !=0)
				crc ^= 0x11021;
			if((*ptr&i) != 0)
				crc ^= 0x1021;
		} 
		ptr++;
	} 
	return crc;
}
/*******************************************************************/
//ReadZoneBit
//Address : 0x0000~0x00FF( 2 bytes) , address to start reading zone bit
//Num : 0x00~0xFF( 1 byte) , Numbers of zone bit for Sequential read, 0x00= 256byets
uint8_t* CreateZoneBit(uint16_t Adress, uint8_t Num, uint8_t* Command)
{
		Command[0] = 0x7E;
		Command[1] = 0x0; 
		Command[2] = 0x08;
		Command[3] = 0x1; 
		Command[4] = (uint8_t)(Adress>>8); 
		Command[5] = (uint8_t)(Adress);
		Command[6] = (uint8_t)(Num);
		//unsigned int CRC = crc_cal_by_bit(&Command[0], 7);
		//Command[7] = (uint8_t)(CRC>>8);
		//Command[8] = (uint8_t)(CRC);
		Command[7] = 0xAB;
		Command[8] = 0xCD;
	return &Command[0];
}

uint8_t* ReadCode(uint8_t* Command)
{
		Command[0] = 0x7E;
		Command[1] = 0x0; 
		Command[2] = 0x08;
		Command[3] = 0x1; 
		Command[4] = 0x0; 
		Command[5] = 0x2;
		Command[6] = 0x1;
		Command[7] = 0xAB;
		Command[8] = 0xCD;
		return Command;
}





