
/*
 * Ethernet.c
 *
 *  Created on: Sep 2, 2021
 *      Author: ahmwae8n
 */
#include "Ethernet.h"

int main()
{
/*Set Operating mode to Configuration*/
	if(ChkOperatingMode(Reset))
		SetOperatingMode(Config);


/*Check Operating mode if its in Config then Initialize E-MAC*/
	if(ChkOperatingMode(Config))
	{
		/*Enable TRCCM to clear counter register before setting the MAC Address
		 * MPDE to enable Magic packet detection
		 * DM to make module full-duplex*/
		ECMR &= ~(1 << TRCCM | 1 << MPDE | 1 << DM);

		/*Set MAC Address in MAHR and MALR*/
		MAHR = 0x52540012;
		MALR = 0x00003480;
	}

	/*Map memory to point to location of linkfix1 which the beginning
	 * of the descriptor table (Base address in Memory)*/
	DBAT = &DESCR_Linkfix1;

	/*----------Transmission Config----------*/

	/* TGC Config*/
	/*Enable ECBS(Enable Credit Based Shaping) to transmit data in queues*/
	TGC |=(1 << ECBS);

	/*TCCR Config*/
	/*Enable TFR to releases oldest entry in the same time-stamp
	 * and enable TFEN to store time =-stamp information for descriptors*/
	TCCR |= (1 << TFR | 1 << TFEN);
	TCCR &= ~(1 << TSRQ0);

	//----------Expressed TX Packet----------//

	/*TX Packet Shape data to send it */
	/*Frame start (1 byte)*/
	u8  SMD_E = 0xD5;

	/*MAC address of source (6 bytes)*/
	u64 MAC_DA = 0x102030405060;

	/*MAC address of destination (6 bytes)*/
	u64 MAC_SA = 0x205045805660;

	/*Type of Ethernet (2 bytes)*/
	u16 Ethernet_type = 0x0008;

	/*Data sent which is 47 bytes*/
	u8 DATA[46] = "Ahmed Wael Hamed";

	/*Frame End and CRC check (4 bytes)*/
	u32 FCS = 0x00000000;



	/*****************************************/

	/*Align all the TX packet to make all the above variables' address consecutive*/

	u8 TX[65];
	u16 i, x = 0;

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
	x = 0;


	/*------------Descriptors----------*/

	/*set DT to linkfix
	 * DIE (Interrupt Enable clear to zero
	 * DPTR (Descriptors pointer points to second linkfix which is after the Fsingle*/
	DESCR_Linkfix1.DT = Linkfix;
	DESCR_Linkfix1.DIE = 0;
	DESCR_Linkfix1.DPTR = &(DESCR_Linkfix2);

	/*set DT to FSingle
	 * DIE (Interrupt Enable clear to zero)
	 * DS is thhe size of the sent data
	 * DPTR (Descriptors pointer points to second TX Packet*/
	DESCR_Data.DT = FSingle;
	DESCR_Data.DIE = 0;
	DESCR_Data.DS = 16;
	DESCR_Data.DPTR = TX;

	/*set DT to linkfix
	 * DIE (Interrupt Enable clear to zero
	 * DPTR (Descriptors pointer points to Data descriptors*/
	DESCR_Linkfix2.DT = Linkfix;
	DESCR_Linkfix2.DIE = 0;
	DESCR_Linkfix2.DPTR = &(DESCR_Data);

	/*----------Transmission Config----------*/

	/*Set Operating mode to Operatino to enable Transmission*/
	SetOperatingMode(Operation);
	if(ChkOperatingMode(Operation))
	{
		/*ECMR to enable Transmission and
		 * TCCR to Enable Start Queue of 0*/
		ECMR |= (1 << TE);
		TCCR |= (1 << TSRQ0);
	}



  return 0;
}
