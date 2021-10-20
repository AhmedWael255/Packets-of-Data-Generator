/*********************************/
/* Author   :   Spectrum         */
/* Date     :   20 Oct 2021      */
/* Version  :   V01              */
/*********************************/

#ifndef UART_SCIF_H_
#define UART_SCIF_H_

#include "../Common/STD_Types.h"

#define SCIF0_BASE_ADDRESS	0xE6E6000
/*Serial Mode Register*/
#define SCSMR0		*((volatile u8* const) SCIF0_BASE_ADDRESS + 0x00)

/*Bit Rate Register*/
#define SCBRR0		*((volatile u8* const) SCIF0_BASE_ADDRESS + 0x04)

/*Serial Control Register*/
#define SCSCR0		*((volatile u8* const) SCIF0_BASE_ADDRESS + 0x08)

/*Transmit FIFO Data Register*/
#define SCFTDR0		*((volatile u8* const) SCIF0_BASE_ADDRESS + 0x0C)

/*Serial Status Register*/
#define SCFSR0		*((volatile u8* const) SCIF0_BASE_ADDRESS + 0x10)

/*Receive FIFO data register*/
#define SCFRDR0		*((volatile u8* const) SCIF0_BASE_ADDRESS + 0x14)

/*FIFO control register*/
#define SCFCR0		*((volatile u8* const) SCIF0_BASE_ADDRESS + 0x18)

/*FIFO data count register*/
#define SCFDR0		*((volatile u8* const) SCIF0_BASE_ADDRESS + 0x1C)

/*Serial port register*/
#define SCSPTR0		*((volatile u8* const) SCIF0_BASE_ADDRESS + 0x20)

/*Line status register*/
#define SCLSR0		*((volatile u8* const) SCIF0_BASE_ADDRESS + 0x24)

/*Frequency division register*/
#define DL0			*((volatile u8* const) SCIF0_BASE_ADDRESS + 0x30)

/*Clock Select register*/
#define CKS0		*((volatile u8* const) SCIF0_BASE_ADDRESS + 0x34)

/*SCSMR PINS*/
#define STOP		3
#define OE			4
#define PE			5
#define CHR			6
#define CA			7

/*SCSCR PINS*/
#define TOIE		2
#define REIE		3
#define RE			4
#define TE			5
#define RIE			6
#define TIE			7
#define TEIE		11

/*SCFCR PINS*/
#define RFRST		1
#define TFRST		2

/*SCFSR PINS*/
#define DR			0
#define RDF			1
#define PER			2
#define FER			3
#define BRK			4
#define TDFE		5
#define TEND		6
#define ER			7

/*SCLSR PINS*/
#define ORER		0
#define TO			2

/*SCPTR PINS*/
#define SPB2DT		0
#define SPB2IO		1


typedef enum
{
	PCK, PCK_4, PCK_16, PCK_64
}Bit_Rate_CLK;

typedef enum
{
	Async,sync
}CommMode;

typedef enum
{
	Parity_disable, Parity_enable
}Parityenable;

typedef enum
{
	bit_8,bit_7
}CharLength;

typedef enum
{
	EvenParity,OddParity
}ParityMode;

typedef enum
{
	Stop_bit_1, Stop_bit_2
}Stoplength;

typedef struct
{
	CharLength charLen;
	Parityenable parityEnable;
	ParityMode parityMode;
	Stoplength stopLen;
	Bit_Rate_CLK Clock;
}SCIF_config;


/*Serial Transfer format */
#define CommunicationMode    Async

void SCIF_voidInit(const SCIF_config * SCIF_ptr);
void SCIF_voidSetBitRate(u8 Copy_u8Value);







#endif /* UART_SCIF_H_ */
