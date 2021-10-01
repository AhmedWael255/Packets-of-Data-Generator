/*
 * Ethernet_Recieving.c
 *
 *  Created on: Sep 8, 2021
 *      Author: ahmwae8n
 */
#include "Ethernet.h"

int main()
{

	if(ChkOperatingMode(Reset))
			SetOperatingMode(Config);

	if(ChkOperatingMode(Config)) // if its in Config. Initialize E-MAC
	{
		ECMR &= ~(1 << TRCCM | 1 << MPDE | 1 << DM);
		MAHR = 0x52540012;
		MALR = 0x00003480;
	}


}
