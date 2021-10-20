/*********************************/
/* Author   :   Spectrum         */
/* Date     :   2 Sep 2021       */
/* Version  :   V01              */
/*********************************/

#include "Ethernet/Ethernet_interface.h"
#include "UART/SCIF.h"
#include "Timer(CMT)/CMT0.h"

int main()
{
	/*RCLK Enable*/
	CMT0_voidClockEnable();

	/*Timer Config*/
	CMT0_config Time_Config = {OneShoot,bit_16,RCLK_1};
	CMT0_voidInit(&Time_Config);

	/*UART Init*/
	SCIF_config UART_Config = {bit_8, Parity_enable, EvenParity, Stop_bit_1, PCK};
	SCIF_voidInit(&UART_Config);

/*Set Operating mode to Configuration*/
	if(Ethernet_boolChkOperatingMode(Reset))
		Ethernet_voidSetOperatingMode(Config);


/*Check Operating mode if its in Config then Initialize E-MAC*/
	if(Ethernet_boolChkOperatingMode(Config))
	{
		Ethernet_voidEMACInit();
	}

	/*Map memory to point to location of linkfix1 which the beginning
	 * of the descriptor table (Base address in Memory)*/
	Ethernet_voidSet_DESCR_Table_BaseAddress(DESCR_Linkfix1);

	/*----------Transmission Config----------*/

	u8 *TX_PTR = Ethernet_voidInitConfig();

	/*----------Expressed TX Packet----------*/


	 Ethernet_voidWriteData("Ahmed Wael Hamed");

	/*------------Descriptors----------*/

	/*set DT to linkfix
	 * DIE (Interrupt Enable clear to zero
	 * DPTR (Descriptors pointer points to second linkfix which is after the Fsingle*/
	DESCR_Linkfix1.DT = Linkfix;
	DESCR_Linkfix1.DIE = 0;
	DESCR_Linkfix1.DPTR = &(DESCR_Linkfix2);

	/*set DT to FSingle
	 * DIE (Interrupt Enable clear to zero)
	 * DS is the size of the sent data
	 * DPTR (Descriptors pointer points to second TX Packet*/
	DESCR_Data.DT = FSingle;
	DESCR_Data.DIE = 0;
	DESCR_Data.DS = 16;
	DESCR_Data.DPTR = TX_PTR;

	/*set DT to linkfix
	 * DIE (Interrupt Enable clear to zero
	 * DPTR (Descriptors pointer points to Data descriptors*/
	DESCR_Linkfix2.DT = Linkfix;
	DESCR_Linkfix2.DIE = 0;
	DESCR_Linkfix2.DPTR = &(DESCR_Data);

	/*----------Transmission Config----------*/

	/*Set Operating mode to Operation to enable Transmission*/
	Ethernet_voidSetOperatingMode(Operation);
	if(Ethernet_boolChkOperatingMode(Operation))
	{
		Ethernet_voidTransmissionEnable();
	}

	CMT0_voidSetvalue(33);
	CMT0_voidBusyWait();
	CMT0_voidStart();
	CMT0_voidOverFlowFlagWait();
	CMT0_voidClearFlag();

	while(1)
	{

	}

  return 0;
}
