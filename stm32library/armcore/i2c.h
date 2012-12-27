/*
 * i2c.h
 *
 *  Created on: 2012/11/03
 *      Author: sin
 */

#ifndef I2C_H_
#define I2C_H_

#include "armcore.h"
#include <stm32f4xx_i2c.h>

#include "armcore.h"
#include "gpio.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef enum __I2C_Status {
	NOT_READY = 0,
	READY,
	STARTING,
	ADDRESS_SENDING,
	BYTE_TRANSFERRING,
	TRANSMISSION_COMPLETED,
	
	REQUEST_SENDING,
	RESTARTING,
	RECEIVER_ADDRESS_SENDING,
	BYTE_RECEIVING,
	END_RECEIVING,
	/*
	RECEIVE_BYTE_READY,
	BEFORELAST_BYTE_RECEIVED,
	LAST_BYTE_READY,
	RECEIVE_BYTE_COMPLETED,
	RECEIVE_COMPLETED,
	*/
	FAILURE = 0x80
} I2C_Status;

typedef enum __I2C_CommMode {
	I2C_MODE_MASTER_IDLE = 0,
	I2C_MODE_MASTER_TX,
	I2C_MODE_MASTER_RX,
	I2C_MODE_SLAVE_IDLE,
	I2C_MODE_SLAVE_TX,
	I2C_MODE_SLAVE_RX
} I2C_CommMode;

#define I2C_BUFFER_SIZE 256
typedef struct __I2CContext {
	I2C_TypeDef * I2Cx;
	GPIOPin sda, scl;
	uint8_t address;
//	boolean irqmode;
	__IO I2C_CommMode mode;
	__IO uint32 status;
	__IO uint16_t position;
	__IO uint16_t limlen;
	uint8_t * buffer;
//	boolean stopMode;
} I2CContext;

extern I2CContext I2C1Buffer, I2C2Buffer, I2C3Buffer;

boolean i2c_begin(I2CContext * I2Cbuf, I2C_TypeDef * I2Cx, GPIOPin sda, GPIOPin scl, uint32_t clk); //I2C_TypeDef * I2Cx, uint32_t clk);
boolean i2c_transmit(I2CContext * I2Cbuf, uint8_t addr, uint8_t * data, uint16_t length);
boolean i2c_request(I2CContext * I2Cbuf, uint8_t addr, uint8_t * data, uint16_t len);
boolean i2c_start_send(I2CContext * I2Cbuf);
boolean i2c_receive(I2CContext * I2Cbuf, uint8_t * data, uint16_t lim);

#ifdef __cplusplus
}
#endif

#endif /* I2C_H_ */
