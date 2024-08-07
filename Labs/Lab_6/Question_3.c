#include "tm4c123gh6pm.h"
#include <stdint.h>
#define LED_RED (1U << 1)
#define LED_GREEN (1U << 3)
#define CLOCK 16000000


int seconds = 0;
void SystemInit(void)
{
    SYSCTL_RCGCGPIO_R |= 0x20; // PortF clock enable
    while ((SYSCTL_PRGPIO_R & 0x20) == 0) ;   // Delay
    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY; // Unlock PortF Commit register
    GPIO_PORTF_CR_R = 0x1F;
    GPIO_PORTF_AMSEL_R = 0x00;      // Disable analog function
    GPIO_PORTF_PCTL_R = 0x00000000; // GPIO clear bit PCTL
    GPIO_PORTF_AFSEL_R = 0x00;      // No alternate function
    GPIO_PORTF_DIR_R = 0x0E;        // PF321 output
    GPIO_PORTF_DEN_R = 0x1F;        // Enable digital pins PF4-PFO
    GPIO_PORTF_PUR_R = 0x11;
    GPIO_PORTF_IS_R = ~0x11;
    GPIO_PORTF_IBE_R = ~0x11;
    GPIO_PORTF_IEV_R = ~0x11;
    GPIO_PORTF_IM_R = 0x11;
    NVIC_PRI7_R |= 0x00400000;
    NVIC_EN0_R |= 0x40000000;
}

void GPIOF_Handler()
{
    if (GPIO_PORTF_MIS_R & 0x01)
    {
        GPIO_PORTF_DATA_R &= ~LED_RED;
        GPIO_PORTF_ICR_R |= 0x01;
        NVIC_ST_CTRL_R = 0x7;
    }
    else if (GPIO_PORTF_MIS_R & 0x10)
    {
        GPIO_PORTF_DATA_R |= LED_RED;
        GPIO_PORTF_ICR_R |= 0x10;
        NVIC_ST_CTRL_R = 0x6;
    }
}

void SysTick_Handler()
{
    seconds++;
    GPIO_PORTF_DATA_R ^= LED_GREEN;
}

int main()
{
    SystemInit();
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_RELOAD_R = CLOCK - 1;
    NVIC_ST_CTRL_R = 0x7;
    __enable_irq();
    while (1) {}
}
