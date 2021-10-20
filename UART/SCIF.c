/*********************************/
/* Author   :   Spectrum         */
/* Date     :   20 Oct 2021      */
/* Version  :   V01              */
/*********************************/

#include "SCIF.h"
#include "../Common/BIT_Math.h"
#include "../Common/STD_Types.h"

#define CANFD_MODE (*((volatile unsigned int*) (0xE66C04FC)))

void SCIF_voidInit(const SCIF_config * SCIF_ptr)
{
	SCSCR0 &= ~(1 << TE | 1 << RE);
	SCFCR0 |= (1 << TFRST | 1 << RFRST);
	SCFSR0 &= ~(1 << ER | 1 << DR | 1 << BRK | 1<<RDF);

	SCSMR0 = ((SCIF_ptr ->charLen) << 6 | (SCIF_ptr ->parityEnable) << 5 |
			  (SCIF_ptr ->parityMode) << 4  | (SCIF_ptr ->stopLen) << 3 | (SCIF_ptr ->Clock));
}

void SCIF_voidSetBitRate(u8 Copy_u8Value)
{
#if CommunicationMode == Async
	/*Commented*/
#endif
}

void SCIF_voidReady(void)
{
	 SCFCR0 &= ~(1 << TFRST | 1 << RFRST);
	 SCSCR0 |= (1 << TE | 1 << RE);
}

void SCIF_voidSendData(u8 Copy_u8Data)
{
	SCFTDR0 = Copy_u8Data;
}

void SCIF_voidClearFlags(void)
{
	CLR_Bit(SCFSR0,TDFE);
	CLR_Bit(SCFSR0,TEND);
}

void SCIF_voidBreakOutput(void)
{
    SCSPTR0 |= (1 <<SPB2IO);
    SCSPTR0 &= !(1 <<SPB2DT);
    SCSCR0 &= ~(1 << TE);
}

/*int main () {

  SCSCR0 &= ~(1 << TE | 1 << RE | 1 << CKE0);
  SCFCR0 |= (1 << TFRST | 1 << RFRST);
  SCFSR0 &= ~(1 << ER | 1 << DR | 1 << BRK | 1<<RDF);
  SCLSR0 &= ~(1 <<TO | 1 << ORER);
  SCSMR0 |= (1 << PE);
  SCSMR0 &= ~(1 << CHR | 1 << STOP | 1 << CKS1);
  SCSCR0 |= (1 << CKE1);

  CKS0 |= (1 << XIN);


  u8 x = 'A';
  while(1)
  {
      SCSCR0 |= (1 << TE | 1 << RE);
	  while(!(SCFSR0 & (1 << TDFE)));
      SCFTDR0 = x;
      SCFSR0 &= ~(1 << TDFE);
      while(!(SCFSR0 & (1 << TEND)));
      SCSPTR0 |= (1 <<SPB2IO);
      SCSPTR0 &= !(1 <<SPB2DT);
      SCSCR0 &= ~(1 << TE);
  }


  mb_stop(1);
  return 0;


}*/

