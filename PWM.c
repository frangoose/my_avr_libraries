// Version 1.0
// 10/13/19

#include "PWM.h"

void PWM_init(void) // blink board LED at select freq
{
    TCCR1B |= (1 << CS11) | (1 << WGM12); // Timer Counter Control Register enables timer, setting CS10 sets prescalar to 1, Setting Wave Generator mode to Clear Timer on Compare mode
    TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B); // Interrupt Mask Register, setting Output Compare Interrupt
    //OCR1A = (F_CPU / (freq * 2 * 256) - 1);
    //OCR1B = (F_CPU / (freq * 4 * 256) - 1);
    OCR1A = (32000); // set output compare register to match at select frequency
    OCR1B = (4000); // set output compare register to match at select frequency
    // Proportion of OCR1A to OCR1B is the PWM duty cycle
}

void PWM_millis_timer(uint8_t millis)
{
    TCCR0A |= (1 << WGM01); // sets to Clear Timer on Compare (CTC) mode
    TCCR0B |= (1 << CS02) | (1 << CS00); // Sets prescalar to 1024
    
    OCR0A = millis*7.8125-1; // for 16MHz clk
    TIMSK0 = (1 << OCIE0A);
}

void PWM_increase_duty(void){
    uint16_t period = OCR1A;
    uint16_t duty = OCR1B;

    if(duty < period)
    {
        duty++;
    }
    else
    {
        duty = 0;
    }
    OCR1B = duty;
}

void PWM_decrease_duty(void){
    uint16_t period = OCR1A;
    uint16_t duty = OCR1B;

    if(duty > 0)
    {
        duty--;
    }
    else
    {
        duty = period;
    }
    OCR1B = duty;
}

void TimerFrequency(uint8_t freq) // blink board LED at select freq
{
    TCCR1B |= (1 << CS12) | (1 << WGM12); // Timer Counter Control Register enables timer, setting CS12 sets prescalar to 256, Setting Wave Generator mode to Clear Timer on Compare mode
    TIMSK1 |= (1 << OCIE1A); // Interrupt Mask Register, setting Output Compare Interrupt

    OCR1A = (F_CPU / (freq * 2 * 256) - 1); // set output compare register to match at select frequency
}