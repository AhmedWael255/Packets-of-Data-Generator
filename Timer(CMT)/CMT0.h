/*********************************/
/* Author   :   Spectrum         */
/* Date     :   20 Oct 2021      */
/* Version  :   V01              */
/*********************************/

#ifndef CMT0_H_
#define CMT0_H_

#include "../Common/STD_Types.h"

/*CLK Enable Register*/
#define CMCLKE		*((volatile unsigned char* const) 0xE60F1000)

/*Compare Match TImer Start Register 0*/
#define CMSTR0 		*((volatile unsigned char* const) 0xE60F0500)

/*Compare Match TImer Control/Status Register 0*/
#define CMCSR0 		*((volatile unsigned char* const) 0xE60F0510)

/*Compare Match TImer Counter Register 0*/
#define CMCNT0 		*((volatile unsigned char* const) 0xE60F0514)

/*Compare Match TImer Constant Register 0*/
#define CMCOR0 		*((volatile unsigned char* const) 0xE60F0518)

/*CMCLKE PINS*/
#define Ch0clke		5
#define Ch1clke		6

/*CMSTR0 PINS*/
#define STR0		0

/*CMCSR0 PINS*/
#define DBGIV		3
#define CMR0		4
#define CMR1		5
#define CMM			8
#define CMS			9
#define WRFLG		13
#define OVF			14
#define CMF			15

#define MilliSec_1	0x0021

typedef enum
{
	RCLK_8 = 4, RCLK_32, RCLK_128, RCLK_1
}CLK;

typedef enum
{
	OneShoot , Freerunning
}CompareMatch;

typedef enum
{
	bit_32 , bit_16
}CntSize;

typedef struct
{
	CompareMatch CompareMatchMode;
	CntSize CounterSize;
	CLK Clock;

}CMT0_config;

void CMT0_voidClockEnable(void);
void CMT0_voidClockDisable(void);
void CMT0_voidInit(const CMT0_config *CMT0_ptr);
void CMT0_voidStart(void);
void CMT0_voidSetvalue(u32 Copy_u32Value);
void CMT0_voidClearFlag(void);
void CMT0_voidBusyWait(void);
void CMT0_voidOverFlowFlagWait(void);


#endif /* TIMER_CMT__CMT0_H_ */
