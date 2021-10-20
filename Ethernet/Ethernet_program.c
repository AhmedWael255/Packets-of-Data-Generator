/*********************************/
/* Author   :   Spectrum         */
/* Date     :   2 Sep 2021       */
/* Version  :   V01              */
/*********************************/

#include "Ethernet_interface.h"
#include "Ethernet_private.h"

bool Ethernet_boolChkOperatingMode(enum OperatingMode x)
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

void Ethernet_voidSetOperatingMode(enum OperatingMode x)
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

void Ethernet_voidEMACInit(){
	/*Enable TRCCM to clear counter register before setting the MAC Address
	 * MPDE to enable Magic packet detection
	 * DM to make module full-duplex*/
	ECMR |= (1 << TRCCM | 1 << MPDE | 1 << DM);

	/*Set MAC Address in MAHR and MALR*/
	MAHR = Set_MAHR;
	MALR = Set_MALR;
}

void Ethernet_voidTransmissionEnable(void)
{
	/*ECMR to enable Transmission and
	 * TCCR to Enable Start Queue of 0*/
	ECMR |= (1 << TE);
	TCCR |= (1 << TSRQ0);
}

u8* Ethernet_voidWriteData(u8 *DATA)
{
	u8 TX[65];
	/*Align all the TX packet to make all the above variables' address consecutive*/
		u16 i, x = 0;
		u64 MAC_DA = MAC_DESTINATION_ADDRESS;
		u64 MAC_SA = MAC_SOURCE_ADDRESS;

		TX[0] = SMD_E;

		/*Copying memory address of TX[1] to MAC_DA to make its address below Frame Start (SMD_E)*/
		memcpy(&(TX[1]), &MAC_DA, sizeof(MAC_DA));

		for(i = 1; i < 7; i++){
			TX[i] = MAC_DA >> x;
			x += 8;
		}
		x = 0;

		for(i = 7; i < 13; i++){
			TX[i] = MAC_SA >> x;
			x += 8;
		}
		x = 0;

		for(i = 13; i < 15; i++){
			TX[i] = Ethernet_type >> x;
			x += 8;
		}
		x = 0;

		for(i = 15; i < 62; i++){
			TX[i] = DATA[x];
			x++;
		}
		x = 0;

		for(i = 62; i < 65; i++){
			TX[i] = FCS >> x;
			x += 8;
		}
		return TX;
}

void Ethernet_voidInitConfig(void)
{
	/* TGC Config*/
	/*Enable ECBS(Enable Credit Based Shaping) to transmit data in queues*/
	TGC |=(1 << ECBS);

	/*TCCR Config*/
	/*Enable TFR to releases oldest entry in the same time-stamp
	 * and enable TFEN to store time =-stamp information for descriptors*/
	TCCR |= (1 << TFR | 1 << TFEN);
	TCCR &= ~(1 << TSRQ0);
}

void Ethernet_voidSet_DESCR_Table_BaseAddress(u64 Copy_u64BaseAddress)
{
	DBAT = &Copy_u64BaseAddress;
}
