/**
  * @file communication.c
  * @author Wei
  * @date 24/9/16
  * @brief  Wireless communication from the Commander to the Robot.
  *
  * Provides communication about wheel position and movement between the robot
  * commander and the robot.
  *
  */

#include    <p18f452.h>
#include    "communication.h"

/**
 *  @struct communication
 *  @brief  Provide wheel position and movement direction to robot.
 *  @param  encoderPositionR
 *  @param  encoderPositionL
 *  @param  movementDirection
 */
struct communication {
  int encoderPositionR;
  int encoderPositionL;
  int movementDirection;
};

/**
 *  @file   communication.c
 *  @brief  Wirless communication between the robot and robot commander
 *
 *  @todo   Replace return type void to struct. 
 */
 void communication(int pidInput, int pidGains, int chirpstrength)
 {

 }

// struct communication func(){
//     struct commincation result;
//     result.encoderPositionR = 3;
//     result.encoderPositionL = 4;
//     return result;
//   }
// }
