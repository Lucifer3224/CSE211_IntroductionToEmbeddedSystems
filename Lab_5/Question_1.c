#include "tm4c123gh6pm.h"


void System_Init(void)
{
    SYSCTL_RCGCGPIO_R |= 0x20;
    while ((SYSCTL_PRGPIO_R & 0x20) == 0) ;
    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY;
    GPIO_PORTF_CR_R |= 0x0E;
    GPIO_PORTF_AMSEL_R &= ~0x0E;
    GPIO_PORTF_PCTL_R &= 0x0000FFF0;
    GPIO_PORTF_AFSEL_R &= 0x0E;
    GPIO_PORTF_DIR_R |= 0x0E;
    GPIO_PORTF_DEN_R |= 0x0E;
    GPIO_PORTF_DATA_R |= 0x0E;
}

void SysTick_wait(unsigned long delay)
{
    NVIC_ST_CTRL_R = 0x00;
    NVIC_ST_RELOAD_R = delay - 1;
    NVIC_ST_CURRENT_R = 0;
    NVIC_ST_CTRL_R = 0x05;
    while ((NVIC_ST_CTRL_R & 0x00010000) == 0) ;
}

void delay(unsigned long time)
{
    int i = 0;
    while (i < time)
    {
        SysTick_wait(80000); // 1msec
        i++;
    }
}

void RGB_Output(unsigned char data)
{
    GPIO_PORTF_DATA_R |= data;
}

void RGB_CLR(unsigned char data)
{
    GPIO_PORTF_DATA_R &= ~data;
}

int i = 0;
int main()
{
    System_Init();
    while (1)
    {
        RGB_Output(0x02);
        delay(1000);  // wait for a second
        RGB_CLR(0x02);
        delay(1000);
    }
}