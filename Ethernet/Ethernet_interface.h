/*********************************/
/* Author   :   Spectrum         */
/* Date     :   2 Sep 2021       */
/* Version  :   V01              */
/*********************************/

#ifndef ETHERNET_ETHERNET_INTERFACE_H_
#define ETHERNET_ETHERNET_INTERFACE_H_


#include "../Common/STD_Types.h"

enum OperatingMode {Reset, Operation, Config} ;


/*******************************
****	Set MAC Address		****
*******************************/

#define Set_MAHR	0x52540012
#define Set_MALR	0x00003480

/*******************************************
****	Expressed TX Packet Config		****
*******************************************/

/*TX Packet Shape data to send it */
/*Frame start (1 byte)*/
#define SMD_E							0xD5

/*MAC address of source (6 bytes)*/
#define MAC_DESTINATION_ADDRESS			0x102030405060

/*MAC address of destination (6 bytes)*/
#define MAC_SOURCE_ADDRESS	 			0x205045805660

/*Type of Ethernet (2 bytes)*/
#define Ethernet_type  					0x0008

/*Frame End and CRC check (4 bytes)*/
#define FCS 							0x00000000

/***************************************
****	Initialize Descriptors		****
***************************************/

struct
{
	u32 DT  : 4,
		DIE	: 4,
		MSR	: 1,
		TSR : 1,
		TAG :10,
		DS	:12;
	u32 *DPTR;
}DESCR_Data, DESCR_Linkfix1, DESCR_Linkfix2;

#define Linkfix		9
#define FSingle		7


/***************************
****	Functions		****
***************************/

void Ethernet_voidSetOperatingMode(enum OperatingMode x);
bool Ethernet_boolChkOperatingMode(enum OperatingMode x);
void Ethernet_voidInitDescriptors();
void Ethernet_voidSetDescriptors();
void Ethernet_voidEMACInit();
void Ethernet_voidTransmissionEnable();
void Ethernet_voidSet_DESCR_Table_BaseAddress();

#endif /* ETHERNET_ETHERNET_INTERFACE_H_ */
