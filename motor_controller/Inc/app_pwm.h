/*
 * app_pwm.h
 *
 *  Created on: May 22, 2026
 *      Author: wojci
 */

#ifndef APP_PWM_H_
#define APP_PWM_H_

void appPWMInit();
void appPWMSetCallback(void (*_callback)(void));
void appPWMSetDuty(float duty);

#endif /* APP_PWM_H_ */
