#include "tm4c123gh6pm.h"
#define PF123_mask 0x0E
#define PF04_mask 0x11
#define PF_mask 0x20


void init_portA()
{
    SYSCTL_RCGCGPIO_R |= 0x01; // PORT A clock enable
    while ((SYSCTL_PRGPIO_R & 0x01) == 0) ; // make sure that clock of port A is enabled
    GPIO_PORTA_LOCK_R = GPIO_LOCK_KEY;
    GPIO_PORTA_CR_R |= 0x0F;          // allow changes to pins 0,1 for port A
    GPIO_PORTA_AMSEL_R &= ~0x0F;      // disable anlog
    GPIO_PORTA_AFSEL_R &= ~0x0F;      // alternating function off
    GPIO_PORTA_PCTL_R &= ~0xFFFFFFFF; // pin0(RX),1(TX)
    GPIO_PORTA_DIR_R |= 0x0F;         // enable pin0-3 output
    GPIO_PORTA_DEN_R |= 0x0F;         // enable pin0,1 to be digital
    GPIO_PORTA_DATA_R = 5;            // make all pins off
}

void PORTF_Init()
{
    SYSCTL_RCGCGPIO_R |= PF_mask; // PORT f clock enable
    while ((SYSCTL_PRGPIO_R & PF_mask) == 0) ; // ensure that clock of port f is enabled
    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
    GPIO_PORTF_CR_R |= PF123_mask;     // allow changes to pins 1,2,3 for port f
    GPIO_PORTF_AMSEL_R &= ~PF123_mask; // disable anlog
    GPIO_PORTF_AFSEL_R &= ~PF123_mask; // alternating function off
    GPIO_PORTF_PCTL_R &= ~0x0000FFF0;  // pin1,2,3 are cleared
    GPIO_PORTF_DIR_R |= PF123_mask;    // enable pins 1,2,3 to be output
    GPIO_PORTF_DEN_R |= PF123_mask;    // enable pins 1,2,3 to be digital
    GPIO_PORTF_DATA_R = 0x00;          // make leds off
}

void SW_Init()
{
    GPIO_PORTF_CR_R |= PF04_mask;     // allow changes to pf 4,0
    GPIO_PORTF_AMSEL_R &= ~PF04_mask; // disable analog
    GPIO_PORTF_DEN_R |= PF04_mask;    // make pins 4,0 digital
    GPIO_PORTF_DIR_R &= ~PF04_mask;   // make pins 4,0 inputs
    GPIO_PORTF_DATA_R &= ~PF04_mask;  // make switch off
    GPIO_PORTF_AFSEL_R &= ~PF04_mask; // disable alternate functions
    GPIO_PORTF_PCTL_R &= ~0x000F000F; // clear pctl for 4,0
    GPIO_PORTF_PUR_R |= PF04_mask;    // initialize pur for pins 4,0
}

void GPIOF_Handler()
{
    if (GPIO_PORTF_MIS_R & 0x10)
    {
        switch (GPIO_PORTA_DATA_R)
        {
        case 5:
        {
            GPIO_PORTA_DATA_R = 6;
            break;
        }
        case 6:
        {
            GPIO_PORTA_DATA_R = 10;
            break;
        }
        case 10:
        {
            GPIO_PORTA_DATA_R = 9;
            break;
        }
        case 9:
        {
            GPIO_PORTA_DATA_R = 5;
            break;
        }
        default:
        {
            GPIO_PORTA_DATA_R = 5;
            break;
        }
        }
        GPIO_PORTF_ICR_R |= 0x10;
    }
}

int main()
{
    init_portA();
    PORTF_Init();
    SW_Init();
    GPIO_PORTF_IS_R = ~0x11;
    GPIO_PORTF_IBE_R = ~0x11;
    GPIO_PORTF_IEV_R = ~0x11;
    GPIO_PORTF_IM_R = 0x11;
    NVIC_EN0_R |= (1 << 30);
    __enable_irq();
    while (1) {}
}