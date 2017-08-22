/*
 * driver_bq2425x.h
 *
 *  Created on: 18 рту. 2017 у.
 *      Author: user
 */

#ifndef INC_BQ2425X_H_
#define INC_BQ2425X_H_
/* -------------------DEFINE Section ----------------- */

#include <stdint.h>

/* Registers*/
#define BQ2425X_REG_1	0x00
#define BQ2425X_REG_2	0x01
#define BQ2425X_REG_3	0x02
#define BQ2425X_REG_4	0x03
#define BQ2425X_REG_5	0x04
#define BQ2425X_REG_6	0x05
#define BQ2425X_REG_7	0x06

/*Device address*/
#define BQ2425x_ADDR	0x6A

/* --------------------------------------------------- */

/* -------------------Types  Section ----------------- */

typedef struct {
	uint8_t wdFault;
	uint8_t wdEn;
	uint8_t stat;
	uint8_t fault;
} reg_1_state_t;

typedef struct {
	uint8_t reset;
	uint8_t iInLimit;
	uint8_t enStat;
	uint8_t enTerm;
	uint8_t CE;
	uint8_t hzMode;
} reg_2_state_t;

typedef struct {
	uint8_t vBatReg;
	uint8_t usbDet;
} reg_3_state_t;

typedef struct {
	uint8_t iCHG;
	uint8_t iTerm;
} reg_4_state_t;

typedef struct {
	uint8_t loopStatus;
	uint8_t lowChg;
	uint8_t dpdmEn;
	uint8_t ceStatus;
	uint8_t vInDPM;
} reg_5_state_t;

typedef struct {
	uint8_t x2TmrEn;
	uint8_t tmr;
	uint8_t sysOff;
	uint8_t tsEn;
	uint8_t tsStat;
} reg_6_state_t;

typedef struct {
	uint8_t vOvp;
	uint8_t	clrVdr;
	uint8_t forceBatDet;
	uint8_t forcePtm;
} reg_7_state_t;

typedef struct {
	void (*WriteReg)(uint8_t addr, uint8_t reg_offset, uint8_t data);
	uint8_t (*ReadReg)(uint8_t addr, uint8_t reg_offset);
	reg_1_state_t reg_1_state;
	reg_2_state_t reg_2_state;
	reg_3_state_t reg_3_state;
	reg_4_state_t reg_4_state;
	reg_5_state_t reg_5_state;
	reg_6_state_t reg_6_state;
	reg_7_state_t reg_7_state;
} bq2425x_t;

/* --------------------------------------------------- */

/* -------------------Prototypes Section-------------- */

void BQ2425x_GetAllStates(bq2425x_t * bq2425x);
void BQ2425x_ParseReg1(bq2425x_t * bq2425x, uint8_t regval);
void BQ2425x_ParseReg2(bq2425x_t * bq2425x, uint8_t regval);
void BQ2425x_ParseReg3(bq2425x_t * bq2425x, uint8_t regval);
void BQ2425x_ParseReg4(bq2425x_t * bq2425x, uint8_t regval);
void BQ2425x_ParseReg5(bq2425x_t * bq2425x, uint8_t regval);
void BQ2425x_ParseReg6(bq2425x_t * bq2425x, uint8_t regval);
void BQ2425x_ParseReg7(bq2425x_t * bq2425x, uint8_t regval);

/* --------------------------------------------------- */

#endif /* INC_BQ2425X_H_ */
