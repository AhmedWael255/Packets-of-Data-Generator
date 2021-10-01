/*
 * EthernetFns.c
 *
 *  Created on: Sep 6, 2021
 *      Author: medoa
 */
#include "Ethernet.h"

bool ChkOperatingMode(enum OperatingMode x)
{
	switch(x)
	{
	case Reset:
		if(CSR & (1 << OPS0))
			return 1;
		break;

	case Operation:
		if(CSR & (1 << OPS2))
			return 1;
		break;

	case Config:
		if(CSR & (1 << OPS1))
			return 1;
		break;
	default:
		return 0;
	}
	return 0;
}

void SetOperatingMode(enum OperatingMode x)
{
	switch(x)
		{
		case Reset:
			CCC &= ~(1 << OPC0 | 1 << OPC1);
			break;

		case Operation:
			CCC &= ~(1 << OPC0);
			CCC |= (1 << OPC1);
			break;

		case Config:
			CCC &= ~(1 << OPC1);
			CCC |= (1 << OPC0);
			break;
		}
}

char* Set_MAC_Address(char* c)
{
	u8 *bin;
	bool flag = 0;
	size_t length = strlen(c);
	for(size_t i = 0; i < length; i++)
	{
		if(c[i] == ':')
			continue;

		switch(c[i])
		{
		case '0':
			*bin += 0000;
			break;
		case '1':
			*bin += 0001;
			break;
		case '2':
			*bin += 0010;
			break;
		case '3':
			*bin += 0011;
			break;
		case '4':
			*bin += 0100;
			break;
		case '5':
			*bin += 0101;
			break;
		case '6':
			*bin += 0110;
			break;
		case '7':
			*bin += 0111;
			break;
		case '8':
			*bin += 1000;
			break;
		case '9':
			*bin += 1001;
			break;
		case 'A':
			*bin += 1010;
			break;
		case 'B':
			*bin += 1011;
			break;
		case 'C':
			*bin += 1100;
			break;
		case 'D':
			*bin += 1101;
			break;
		case 'E':
			*bin += 1110;
			break;
		case 'F':
			*bin += 1111;
			break;
		default:
			printf("Wrong Input");
		}
	}
	return *bin;
}
