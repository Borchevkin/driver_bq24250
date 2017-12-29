#include "em_device.h"
#include "em_chip.h"
#include "InitDevice.h"
#include "em_gpio.h"
#include "em_cmu.h"
#include "em_i2c.h"
#include "bq2425x.h"


#define DEBUG_BREAK		__asm__("BKPT #0");

#define ADXL345_ADDRESS 0x6A << 1
#define ADXL345_DEVICE_ID_REG 0x00

volatile uint32_t msTicks = 0;

typedef struct {
	uint8_t wdFault;
	uint8_t wdEn;
	uint8_t stat;
	uint8_t fault;
} reg1state_t;

void DelayMs(uint32_t delayTicks)
{
	uint32_t curTicks;

	curTicks = msTicks;
	while ((msTicks - curTicks)< delayTicks);
}

void SysTick_Handler(void)
{
	msTicks++;
}

void I2CTransfer(uint16_t deviceAddr, uint8_t cmdArray[], uint8_t dataArray[], uint16_t cmdLen, uint16_t dataLen, uint16_t flag)
{
	I2C_TransferSeq_TypeDef i2cTransfer; // transfer structure

	I2C_TransferReturn_TypeDef result;	//transfer return enum

	i2cTransfer.addr		= deviceAddr;
	i2cTransfer.flags		= flag;
	i2cTransfer.buf[0].data	= cmdArray;
	i2cTransfer.buf[0].len	= cmdLen;

	i2cTransfer.buf[1].data	= dataArray;
	i2cTransfer.buf[1].len	= dataLen;

	result = I2C_TransferInit(I2C1, &i2cTransfer);

	while (result != i2cTransferDone)
	{
		if (result != i2cTransferInProgress)
		{
			DEBUG_BREAK;
		}
		result = I2C_Transfer(I2C1);	// continue an initiated I2C transfer
	}
}

uint8_t i2cReadRegister(uint8_t addr,uint8_t regOffset)
{
	uint8_t cmdArray[1];
	uint8_t dataArray[1];

	cmdArray[0] = regOffset;
	I2CTransfer(addr << 1, cmdArray, dataArray, 1, 1, I2C_FLAG_WRITE_READ);
	return dataArray[0];
}



int main(void)
{
	CHIP_Init();	// chip errata

	enter_DefaultMode_from_RESET();

	SysTick_Config(CMU_ClockFreqGet(cmuClock_CORE) / 1000);

	DelayMs(100);

	//I2C_Init_TypeDef i2cInit = I2C_INIT_DEFAULT;	//I2C initialization structure
	//I2C_Init(I2C1, &i2cInit);		// Initialize I2C

	//initialize BQ2425x
	bq2425x_t bq2425x;
	bq2425x.ReadReg = i2cReadRegister;



	while (1)
	{


		BQ2425x_GetAllStates(&bq2425x);


		GPIO_PinOutSet(LED0_PORT, LED0_PIN);	//set LED0 to 1
		DelayMs(1000);							//delay
		GPIO_PinOutClear(LED0_PORT, LED0_PIN);	//set LED0 to 0
		DelayMs(1000);							//delay
	}


}
