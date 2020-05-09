// Version 1.0
// 10/13/19

#include "segment_display_driver.h"

char seg_digits[] = {
    0b11111100, //0
    0b01100000, //1
    0b11011010, //2
    0b11110010, //3
    0b01100110, //4
    0b10110110, //5
    0b10111110, //6
    0b11100000, //7
    0b11111110, //8
    0b11100110, //9
    0b11101110, //A
    0b00111110, //b
    0b10011100, //C
    0b01111010, //d
    0b10011110, //E
    0b10001110, //F
    0b00000001, //.
    0b00000000, //all off
    0b11111111 //all on
};

char set_seg_value(int val)
{
    char seg_val = 0;
    if(val < 19)
    {
        seg_val = seg_digits[val];
    }
    
    return seg_val;
}