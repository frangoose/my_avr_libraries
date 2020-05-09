// Version 1.0
// 10/13/19

#define F_CPU 16000000UL
#include <avr/io.h>

#ifndef PWM_H_
#define PWM_H_

void PWM_init(void); // blink board LED at select freq

void TimerFrequency(uint8_t freq); // argument is frequency in number of HZ
void PWM_millis_timer(uint8_t millis); // Timer output compare match in number of millis

void PWM_increase_duty(void); // increase duty cycle
void PWM_decrease_duty(void); // decrease duty cycle


#endif /* PWM_H_ */