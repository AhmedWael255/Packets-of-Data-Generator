/*********************************/
/* Author   :   Spectrum         */
/* Date     :   20 Oct 2021      */
/* Version  :   V01              */
/*********************************/

#include "CMT0.h"

#include "../Common/BIT_Math.h"
#include "../Common/STD_Types.h"

//#include "mb/sw/control.h"

#define CANFD_MODE (*((volatile unsigned int*) (0xE66C04FC)))


/*Enable RCLK of CMT timer*/
void CMT0_voidClockEnable(void)
{
	SET_Bit(CMCLKE, Ch0clke);
}

/*Disable RCLK of CMT timer*/
void CMT0_voidClockDisable(void)
{
	CLR_Bit(CMCLKE, Ch0clke);
}

/*Init timer by setting option:
 * Compare match mode : (One-Shoot or Free-Running)
 * Counter Size : (16bit or 32bit)
 * Adjust Prescalar: (RCLK/8 or RCLK/32 or RCLK/128 or RCLK/1)*/
void CMT0_voidInit(const CMT0_config *CMT0_ptr)
{
	CMCSR0 = ((CMCSR0 & 0xFFFFFEFF) | ((CMT0_ptr ->CompareMatchMode) << 8));
	CMCSR0 = ((CMCSR0 & 0xFFFFFDFF) | ((CMT0_ptr ->CounterSize) << 9));
	CMCSR0 = ((CMCSR0 & 0xFFFFFFF8) | ((CMT0_ptr ->Clock)));
	CLR_Bit(CMSTR0, STR0);
}

/*Timer Start*/
void CMT0_voidStart(void)
{
	SET_Bit(CMSTR0, STR0);
}

/*Insert Start timer*/
void CMT0_voidSetvalue(u32 Copy_u32Value)
{
	CMCOR0 = Copy_u32Value;
}

/*Clear Comapre Match Flag Flag*/
void CMT0_voidClearFlag(void)
{
	CLR_Bit(CMCSR0,CMF);
}

void CMT0_voidBusyWait(void)
{
	 while((CMCSR0 & (1 << WRFLG)));
}

void CMT0_voidOverFlowFlagWait(void)
{
    while((CMCSR0 & (1 << CMF)) == 0);
}

/*int main(){
  CMCLKE |= (1 << Ch0clke);
  CMSTR0 &= ~(1 << STR0);
  CMCSR0 &= ~(1 << CMM);
  CMCSR0 |= (1 << CKS0 | 1 << CKS1 | 1 << CKS2 | 1 << CMS);

  for(u16 i = 0; i < 2; i++)
  {
    CMCOR0 = 0x0021;
    while((CMCSR0 & (1 << WRFLG)));
    CMSTR0 |= (1 << STR0);
    while((CMCSR0 & (1 << CMF)) == 0);
    CMCSR0 &= ~(1 << CMF);
  }


  return 0;
}*/
