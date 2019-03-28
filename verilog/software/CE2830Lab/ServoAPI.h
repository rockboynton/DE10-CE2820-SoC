/**
 * ServoAPI.h
 *
 *  Created on: Mar 25, 2019
 *      Authors: schillingdl, boyntonrl
 *
 * API for interfacing with the DE10-CE2820 SoC servo controllers (SERVO_X and 
 * SERVO_Y)
 */

#ifndef SERVOAPI_H_
#define SERVOAPI_H_

#include "alt_types.h"
#include "stdbool.h"
#include "delay.h"
#include "time.h"
#include "stdlib.h"

/**
* An enum declaring the two servos controlling the x and y directions.
*/
typedef enum {
	SERVO_Y = 0xFF2000A0, /**< servo controlling up and down movement */
	SERVO_X = 0xFF200090  /**< servo controlling left and right movement */
} SERVO;


/**
 * Sets the given servo to the specififed angle (-45 to 45) degrees.
 * @param servo - enum that specifies servo base address
 * @param angle - desired angle (-45 to 45) degrees
 * @return true if successful or false if angle out of range
 */
bool servo_setAngle(SERVO servo, alt_8 angle);

/**
 * Returns the servo back to the middle (0 degrees).
 * @param servo - enum that specifies servo base address
 * @return true if successful. false if unsuccessful
 */
bool servo_center(SERVO servo);

/**
 * Pans the servo from right to left at the given speed from 1 (slow) - 10 (fast)
 * @param servo - enum that specifies servo base address
 * @param speed - speed at which the servo pans. 1 (slow) - 10 (fast)
 * @param cycles - number of periods which the servo should pan for. Left to right is 
 * one cycle
 * @return true if successful
 */
bool servo_pan(SERVO servo, alt_u32 speed, float cycles);

/**
 * Sets the servo to a random position.
 * @param servo - enum that specifies servo base address
 * @return true if sucessful.
 */
bool servo_randomMovement(SERVO servo);


#endif /* SERVOAPI_H_ */
