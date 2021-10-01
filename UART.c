/*
 * UART.c
 *
 *  Created on: Sep 6, 2021
 *      Author: ahmwae8n
 */
#include "UART.h"

#define CANFD_MODE (*((volatile unsigned int*) (0xE66C04FC)))


int main () {

  SCSCR &= ~(1 << TE | 1 << RE | 1 << CKE0);
  SCFCR |= (1 << TFRST | 1 << RFRST);
  SCFCR &= ~(1 << ER | 1 << DR | 1 << BRK | 1<<RDF);
  SCLSR &= ~(1 <<TO | 1 << ORER);
  SCSMR |= (1 << PE);
  SCSMR &= ~(1 << CHR | 1 << STOP | 1 << CKS1);
  SCSCR |= (1 << CKE1);

  CKS |= (1 << XIN);


  u8 x = 'A';
  while(1)
  {
      SCSCR |= (1 << TE | 1 << RE);
	  while(!(SCFSR & (1 << TDFE)));
      SCFTDR = x;
      SCFSR &= ~(1 << TDFE);
      while(!(SCFSR & (1 << TEND)));
      SCSPTR |= (1 <<SPB2IO);
      SCSPTR &= !(1 <<SPB2DT);
      SCSCR &= ~(1 << TE);
  }


  mb_stop(1);
  return 0;


}

