#include "IO.h"


void RGB_Init(void)
{
    SYSCTL_RCGCGPIO_R |= PF_mask; // enable clk for port F
    while ((SYSCTL_PRGPIO_R & PF_mask) == 0) ; // check for the clk delay
    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY; // break the lock of port F
    GPIO_PORTF_CR_R |= PF123_mask;     // enable making changes in leds pins (PF1,PF2&PF3)
    GPIO_PORTF_AMSEL_R &= ~PF123_mask; // disable analog mode
    GPIO_PORTF_AFSEL_R &= ~PF123_mask; // disable using alternate functions (use the pins as GPIO) 
    GPIO_PORTF_PCTL_R &= ~0x0000FFF0;  //clear the bits corresponfing to the 3 pins
    GPIO_PORTF_DEN_R |= PF123_mask;    // enable using the pins in digital mode
    GPIO_PORTF_DIR_R |= PF123_mask;    // set the bits corresponding to the pins to 1 to use them as output
    GPIO_PORTF_DATA_R &= ~PF123_mask;
}

void Switches_Init(void)
{
    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
    GPIO_PORTF_CR_R |= PF04_mask; // enable making changes in switches pins (PF0&PF4)
    GPIO_PORTF_AMSEL_R &= ~PF04_mask;
    GPIO_PORTF_AFSEL_R &= ~PF04_mask;
    GPIO_PORTF_PCTL_R &= ~0x000F000F; // clear the bits corresponfing to the 2 switches
    GPIO_PORTF_DEN_R |= PF04_mask;
    GPIO_PORTF_DIR_R &= ~PF04_mask; // set the bits corresponding to the switches to 0 to use them as input
    GPIO_PORTF_PUR_R |= PF04_mask;
}

unsigned char SW1_Input(void)
{
    char pressed1 = GPIO_PORTF_DATA_R & PF_SW1_mask;
    return pressed1;
}

unsigned char SW2_Input(void)
{
    char pressed2 = GPIO_PORTF_DATA_R & PF_SW2_mask;
    return pressed2;
}

void RED_Output(unsigned char data)
{
    GPIO_PORTF_DATA_R &= ~PF123_mask;
    GPIO_PORTF_DATA_R |= data;
}

void BLUE_Output(unsigned char data)
{
    GPIO_PORTF_DATA_R &= ~PF123_mask;
    GPIO_PORTF_DATA_R |= data;
}

void GREEN_Output(unsigned char data)
{
    GPIO_PORTF_DATA_R &= ~PF123_mask;
    GPIO_PORTF_DATA_R |= data;
}

void No_Led()
{
    GPIO_PORTF_DATA_R &= 0x00;
}

unsigned char led;
signed char button_in;
signed char button2_in;
int main()
{
    RGB_Init();
    Switches_Init();
    while (1)
    {
        button_in = SW1_Input(); // store the return value of SW1_Input
        button2_in = SW2_Input(); // store the return value of SW2_Input
        if (button_in && button2_in)
        {
            No_Led();
        }
        if (!button_in && !button2_in)
        {
            led = RED;
            RED_Output(led);
        }
        else if (!button_in && button2_in)
        {
            led = BLUE;
            BLUE_Output(led);
        }
        else if (button_in && !button2_in)
        {
            led = GREEN;
            GREEN_Output(led);
        }
    }
}
