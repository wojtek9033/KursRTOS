/*
 * app_control.h
 *
 *  Created on: May 22, 2026
 *      Author: wojci
 */

#ifndef APP_CONTROL_H_
#define APP_CONTROL_H_

void appControlInit();
void appControlSetRegulatorDirect();
void appControlSetRegulatorTarget(float target);
void appControlJoystickEnable();
void appControlJoystickDisable();
void appControlBufferEnable();
void appControlBufferDisable();

#endif /* APP_CONTROL_H_ */
