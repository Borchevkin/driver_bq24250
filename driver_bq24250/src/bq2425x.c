/*
 * bq2425x.c
 *
 *  Created on: 18 àâã. 2017 ã.
 *      Author: user
 */

#include "bq2425x.h"

void BQ2425x_GetAllStates(bq2425x_t * bq2425x)
{
	uint8_t buffer;
	buffer = bq2425x->ReadReg(BQ2425x_ADDR, BQ2425X_REG_1);
	BQ2425x_ParseReg1(bq2425x, buffer);
	BQ2425x_ParseReg2(bq2425x, buffer);
	BQ2425x_ParseReg3(bq2425x, buffer);
	BQ2425x_ParseReg4(bq2425x, buffer);
	BQ2425x_ParseReg5(bq2425x, buffer);
	BQ2425x_ParseReg6(bq2425x, buffer);
	BQ2425x_ParseReg7(bq2425x, buffer);
}

void BQ2425x_ParseReg1(bq2425x_t * bq2425x, uint8_t regval) //Parsing values from register 1
{
	bq2425x->reg_1_state.fault 		= (regval & 0x0F);
	bq2425x->reg_1_state.stat 		= (regval & 0x30) >> 4;
	bq2425x->reg_1_state.wdEn 		= (regval & 0x40) >> 6;
	bq2425x->reg_1_state.wdFault 		= (regval & 0x80) >> 7;
}

void BQ2425x_ParseReg2(bq2425x_t * bq2425x, uint8_t regval) //Parsing values from register 2
{
	bq2425x->reg_2_state.hzMode 		= (regval & 0x01);
	bq2425x->reg_2_state.CE 		= (regval & 0x02) >> 1;
	bq2425x->reg_2_state.enTerm		= (regval & 0x04) >> 2;
	bq2425x->reg_2_state.enStat		= (regval & 0x08) >> 3;
	bq2425x->reg_2_state.iInLimit 		= (regval & 0x70) >> 4;
	bq2425x->reg_2_state.reset		= (regval & 0x80) >> 7;
}

void BQ2425x_ParseReg3(bq2425x_t * bq2425x, uint8_t regval) //Parsing values from register 3
{
	bq2425x->reg_3_state.usbDet		= (regval & 0x03);
	bq2425x->reg_3_state.vBatReg		= (regval & 0xFC) >> 2;
}

void BQ2425x_ParseReg4(bq2425x_t * bq2425x, uint8_t regval) //Parsing values from register 4
{
	bq2425x->reg_4_state.iTerm		= (regval & 0x07);
	bq2425x->reg_4_state.iCHG		= (regval & 0xF8) >> 3;
}

void BQ2425x_ParseReg5(bq2425x_t * bq2425x, uint8_t regval) //Parsing values from register 5
{
	bq2425x->reg_5_state.vInDPM		= (regval & 0x07);
	bq2425x->reg_5_state.ceStatus		= (regval & 0x08) >> 3;
	bq2425x->reg_5_state.dpdmEn		= (regval & 0x10) >> 4;
	bq2425x->reg_5_state.lowChg		= (regval & 0x20) >> 5;
	bq2425x->reg_5_state.loopStatus		= (regval & 0xC0) >> 6;
}

void BQ2425x_ParseReg6(bq2425x_t * bq2425x, uint8_t regval) //Parsing values from register 6
{
	bq2425x->reg_6_state.tsStat		= (regval & 0x07);
	bq2425x->reg_6_state.tsEn		= (regval & 0x08) >> 3;
	bq2425x->reg_6_state.sysOff		= (regval & 0x10) >> 4;
	bq2425x->reg_6_state.tmr		= (regval & 0x60) >> 5;
	bq2425x->reg_6_state.x2TmrEn		= (regval & 0x80) >> 7;
}

void BQ2425x_ParseReg7(bq2425x_t * bq2425x, uint8_t regval) //Parsing values from register 7
{
	bq2425x->reg_7_state.forcePtm	 	 = (regval & 0x04) >> 2;
	bq2425x->reg_7_state.forceBatDet 	 = (regval & 0x08) >> 3;
	bq2425x->reg_7_state.clrVdr		 = (regval & 0x10) >> 4;
	bq2425x->reg_7_state.vOvp		 = (regval & 0xE0) >> 5;
}
