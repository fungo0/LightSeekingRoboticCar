//  Author:Frankie.Chu
//  Date:20 November, 2012
//
//  This library is free software; you can redistribute it and/or
//  modify it under the terms of the GNU Lesser General Public
//  License as published by the Free Software Foundation; either
//  version 2.1 of the License, or (at your option) any later version.
//
//  This library is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
//  Lesser General Public License for more details.
//
//  You should have received a copy of the GNU Lesser General Public
//  License along with this library; if not, write to the Free Software
//  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
//
//  Modified record:
//		Timendainum forked 11/2014
/*******************************************************************************/
#ifndef __MOTORDRIVER_H__
#define __MOTORDRIVER_H__
#include <Arduino.h>
/******Pins definitions*************/
#define MOTORSHIELD_IN1	5
#define MOTORSHIELD_IN2	4
#define MOTORSHIELD_IN3	3
#define MOTORSHIELD_IN4	2
#define SPEEDPIN_A	9 //9
#define SPEEDPIN_B	10 //10
/*
//seeed
Function
PWM				D9	D10
+				D8	D12
-				D11 D13
*/



/**************Motor ID**********************/
#define MOTORA 			0
#define MOTORB 			1

#define MOTOR_POSITION_LEFT  0
#define MOTOR_POSITION_RIGHT 1
#define MOTOR_CLOCKWISE      0
#define MOTOR_ANTICLOCKWISE  1

#define USE_DC_MOTOR		0

struct MotorStruct
{
	int8_t speed;
	uint8_t direction;
	uint8_t position;
};
/**Class for Motor Shield**/
class MotorDriver
{
	MotorStruct motorA;
	MotorStruct motorB;
public:
	void init();
	void configure(uint8_t position, uint8_t motorID);
	void setSpeed(int8_t speed, uint8_t motorID);
	void setDirection(uint8_t direction, uint8_t motorID);
	void rotate(uint8_t direction, uint8_t motor_position);
	void rotateWithID(uint8_t direction, uint8_t motorID);
	void goForward();
	void goBackward();
	void goLeft();
	void goRight();
	void stop();
	void stop(uint8_t motorID);
};
extern MotorDriver motordriver;

#endif
