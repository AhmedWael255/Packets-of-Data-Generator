/*
 * Ethernet.h
 *
 *  Created on: Sep 2, 2021
 *      Author: ahmwae8n
 */

#ifndef ETHERNET_ETHERNET_H_
#define ETHERNET_ETHERNET_H_

#include <stdio.h>
//#include "mb/sw/control.h"
#include "Datatypes.h"

enum OperatingMode {Reset, Operation, Config} ;

/***************************************
****	AVB_DMAC MODE Register		****
***************************************/

#define CCC		(*((volatile unsigned int*) (0xE6800000)))
#define DBAT	(*((volatile unsigned int*) (0xE6800004)))
#define CSR		(*((volatile unsigned int*) (0xE680000C)))
#define RFLR	(*((volatile unsigned int*) (0xE6800008)))
#define RPC		(*((volatile unsigned int*) (0xE680000C)))
#define UFCV	(*((volatile unsigned int*) (0xE6800010)))


//-----CCC-----//
#define OPC0	0
#define OPC1	1

/*CSR Register*/
#define OPS0	0
#define OPS1	1
#define OPS2	2
#define OPS3	3




/***********************************
****	EMAC MODE Register		****
***********************************/

#define ECMR	(*((volatile unsigned int*) (0xE6800500)))
#define MALR	(*((volatile unsigned int*) (0xE68005C8)))
#define MAHR	(*((volatile unsigned int*) (0xE68005C0)))

//-----ECMR REG-----//
#define TRCCM	26
#define RCSC	23
#define DPAD	21
#define RZPF	20
#define	TZPF	19
#define PFR		18
#define RXF		17
#define TXF		16
#define MPDE	9
#define RE		6
#define TE		5
#define DM		1
#define PRM		0

/***************************************
****	Transmit Configurations		****
***************************************/

#define TGC		(*((volatile unsigned int*) (0xE6800300)))
#define TCCR 	(*((volatile unsigned int*) (0xE6800304)))
#define MFA		(*((volatile unsigned int*) (0xE680030C)))

//-----TCCR REG-----//
#define MFR		17
#define MFEN	16
#define TFR		9
#define TFEN	8
#define TSRQ3	3
#define TSRQ2	2
#define TSRQ1	1
#define TSRQ0	0
#define TSRQ0	0

//----TGC REG-----//
#define TBD31	21
#define TBD30	20
#define TBD21	17
#define TBD20	16
#define TBD11	13
#define TBD10	12
#define TBD01	9
#define TBD00	8
#define TQP		5
#define ECBS	4
#define TSM3	3
#define TSM2	2
#define TSM1	1
#define TSM0	0


/***************************************
****	Initialize Descriptors		****
***************************************/


struct DESCR
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

char* Set_MAC_Address(char* c);
void SetOperatingMode(enum OperatingMode x);
bool ChkOperatingMode(enum OperatingMode x);

#endif /* ETHERNET_ETHERNET_H_ */
