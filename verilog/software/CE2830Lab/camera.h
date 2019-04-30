/*
 * camera.h
 *
 *  Created on: Apr 29, 2019
 *      Author: boyntonrl
 */

#ifndef CAMERA_H_
#define CAMERA_H_

#include "alt_types.h"

#define CAM_BASE 0xFF2000C0

#define BLUE_GAIN_REG = 0x01
#define BLUE_GAIN_DEFAULT_VAL = 0x80;

typedef struct {
    alt_u32 TFR_CMD;            // Transfer command FIFO
    alt_u32 RX_DATA;            // Receive data FIFO
    alt_u32 CTRL;               // Control register
    alt_u32 ISER;               // Interrupt status enable register
    alt_u32 ISR;                // Interrupt status register
    alt_u32 STATUS;             // Status register
    alt_u32 TFR_CMD_FIFO_LVL;   // TFR_CMD FIFO level register
    alt_u32 RX_DATA_FIFO_LVL;   // RX_DATA FIFO level register
    alt_u32 SCL_LOW;            // SCL low count register
    alt_u32 SCL_HIGH;           // SCL high count register
    alt_u32 SDA_HOLD;           // SDA hold count register
} CAMERA;

/**
 * Configure and enable peripheral
 */
void cam_init();

/**
 * Sets a camera register to the provided value
 */
void cam_setReg(alt_u32* cmd);

/**
 * Gets the current register value from the camera
 */
alt_u32 cam_getReg();

/**
 * Writes data to the camera address though i2c.
 */
void cam_write_data(int addr, int data);

/**
 * Reads data from the camera at the supplied address
 * through the i2c.
 */
alt_u8 cam_read_data(int addr);



#endif /* CAMERA_H_ */
