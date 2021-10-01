#include "Timer.h"

#include <stdio.h>
//#include "mb/sw/control.h"

#define CANFD_MODE (*((volatile unsigned int*) (0xE66C04FC)))


int main(){
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
}
