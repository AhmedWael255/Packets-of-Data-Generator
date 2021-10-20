/*
 * Ethernet_private.h
 *
 *  Created on: Oct 20, 2021
 *      Author: medoa
 */

#ifndef ETHERNET_PRIVATE_H_
#define ETHERNET_PRIVATE_H_

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

#endif /* ETHERNET_ETHERNET_PRIVATE_H_ */
