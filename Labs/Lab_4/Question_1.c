#include "tm4c123gh6pm.h"
#include <string.h>
#include <stdio.h>
#define CR 0x0D


void UART_Init(void)
{
    SYSCTL_RCGCUART_R |= 0x0001;
    SYSCTL_RCGCGPIO_R |= 0x0001;
    UART0_CTL_R &= ~0x0001;
    UART0_IBRD_R = 0x68;
    UART0_FBRD_R = 0xB;
    UART0_LCRH_R |= 0x0070;
    UART0_CTL_R &= 0x0301;
    GPIO_PORTA_AFSEL_R |= 0x03;
    GPIO_PORTA_PCTL_R = (GPIO_PORTA_PCTL_R & 0xFFFFFF00) + 0x00000011;
    GPIO_PORTA_DEN_R |= 0x03;
    GPIO_PORTA_AMSEL_R &= ~0x03;
}

void RGB_Init(void)
{
    SYSCTL_RCGCGPIO_R |= 0x20; // enable clk for port F
    while ((SYSCTL_PRGPIO_R & 0x20) == 0) ;  // check for the clk delay
    GPIO_PORTF_LOCK_R = GPIO_LOCK_KEY; // break the lock of port F
    GPIO_PORTF_CR_R |= 0x0E;           // enable making changes in leds pins (PF1,PF2&PF3)
    GPIO_PORTF_AMSEL_R &= ~0x0E;       // disable analog mode
    GPIO_PORTF_AFSEL_R &= ~0x0E;       // disable using alternate functions (use the pins as GPIO)
    GPIO_PORTF_PCTL_R &= ~0x0000FFF0;  // clear the bits corresponfing to the 3 pins
    GPIO_PORTF_DEN_R |= 0x0E;          // enable using the pins in digital mode
    GPIO_PORTF_DIR_R |= 0x0E;          // set the bits corresponding to the pins to 1 to use them as output
    GPIO_PORTF_DATA_R &= ~0x0E;        // initialize the leds to be off
}

char UART_INchar(void)
{
    while ((UART0_FR_R & 0x0010) != 0);
    return (char)(UART0_DR_R & 0x00FF);
}

void UART_OUTchar(unsigned char data)
{
    while ((UART0_FR_R & 0x0020) != 0);
    UART0_DR_R = data;
}

void getCommand(char *command, int len)
{
    char ch;
    int i;
    for (i = 0; i < len; i++)
    {
        ch = UART_INchar();
        if (ch != CR)
        {
            command[i] = ch;
            UART_OUTchar(command[i]);
        }
        else if (ch == CR || i == len)
            break;
    }
}

void UART_OutString(char *pt)
{
    while (*pt)
    {
        UART_OUTchar(*pt);
        pt++;
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

int main()
{
    const int len = 9;
    char command[len] = {0};
    RGB_Init();
    UART_Init();

    while (1)
    {
        UART_OutString("Enter a character: ");
        getCommand(command, len);

        if (strcmp(command, "RedOn") == 0)
        {
            RGB_Output(0x02);
            memset(command, 0, len);
        }
        else if (strcmp(command, "RedOff") == 0)
        {
            RGB_CLR(0x02);
            memset(command, 0, len);
        }
        else if (strcmp(command, "GreenOn") == 0)
        {
            RGB_Output(0x08);
            memset(command, 0, len);
        }
        else if (strcmp(command, "GreenOff") == 0)
        {
            RGB_CLR(0x08);
            memset(command, 0, len);
        }
        else if (strcmp(command, "BlueOn") == 0)
        {
            RGB_Output(0x04);
            memset(command, 0, len);
        }
        else if (strcmp(command, "BlueOff") == 0)
        {
            RGB_CLR(0x04);
            memset(command, 0, len);
        }
        else
        {
            RGB_CLR(0x0E);
            memset(command, 0, len);
        }
        UART_OutString("\n");
    }
}
