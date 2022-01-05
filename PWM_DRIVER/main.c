#include "STD_TYPES.h"
#include "Macros.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "PWM_interface.h"
#include "UART_interface.h"
#include "NVIC_interface.h"

void vidTestInterrupt(void);
void vidControlPWM(void);

volatile u32 u32Count = 0;
#define APP_MESSAGE_INDEX 0
#define APP_MESSAGE_DUTYCYC 1

void vidTestInterrupt(void)
{
	u32Count++;
	if (u32Count == 70000)
	{
	//GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN2);
		u32Count = 0;
	}
	else
	{
		//GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN2,STD_LOW);

	}
}
volatile	PWMConfig_t PWMConfig_0;
volatile	PWMConfig_t PWMConfig_1;

void vidControlPWM(void)
{
	static u8 u8Index = 0;
	static u8 u8ReceivedByte = 0;
	static u8 u8Bytes[2];
	u8ReceivedByte = UART0_u8GetReceivedByte();
	u8Bytes[u8Index] = u8ReceivedByte;
	u8Index++;
	if (u8Index == 2)
	{
		if (u8Bytes[APP_MESSAGE_INDEX] == 0)
		{
		GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);
		PWMConfig_0.u16CompVal = u8Bytes[APP_MESSAGE_DUTYCYC]*500;
		PWM_vidSetCompValue(PWMConfig_0.u8Module,PWMConfig_0.u8Generator,PWMConfig_0.u8Channel,PWMConfig_0.u16CompVal);
		}
		else if (u8Bytes[APP_MESSAGE_INDEX] == 1)
		{
		GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);
		PWMConfig_1.u16CompVal = u8Bytes[APP_MESSAGE_DUTYCYC]*500;
		PWM_vidSetCompValue(PWMConfig_1.u8Module,PWMConfig_1.u8Generator,PWMConfig_1.u8Channel,PWMConfig_1.u16CompVal);
		}
		u8Index = 0;
	}
}

int main(void)
{
	/*Enable clock*/
	SYSCNTRL_vidEnablePWMClock(SYSCNTRL_PWM_0);
	SYSCNTRL_vidEnableUARTClock(SYSCNTRL_UART0);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTB);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTE);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTD);

	SYSCNTRL_vidConfigPWMDiv(SYSCNTRL_PWM_DIV_ENABLED,SYSCNTRL_PWM_DIV_16);
	
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN1,GPIO_DEN_SET);
	
	/*GPIO pin configuration*/
	/*PWM0 channel 0*/
	GPIO_vidSelectAlterFunction(GPIO_PORTB,GPIO_PIN6);
	GPIO_vidSetPinDigEnable(GPIO_PORTB,GPIO_PIN6,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTB,GPIO_PIN6,0x4);
	/*PWM0 channel 1*/
	GPIO_vidSelectAlterFunction(GPIO_PORTB,GPIO_PIN7);
	GPIO_vidSetPinDigEnable(GPIO_PORTB,GPIO_PIN7,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTB,GPIO_PIN7,0x4);
	/*PWM0 channel 2*/
	GPIO_vidSelectAlterFunction(GPIO_PORTB,GPIO_PIN4);
	GPIO_vidSetPinDigEnable(GPIO_PORTB,GPIO_PIN4,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTB,GPIO_PIN4,0x4);
	/*PWM0 channel 3*/
	GPIO_vidSelectAlterFunction(GPIO_PORTB,GPIO_PIN5);
	GPIO_vidSetPinDigEnable(GPIO_PORTB,GPIO_PIN5,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTB,GPIO_PIN5,0x4);
	
	/*PWM0 channel 4*/
	GPIO_vidSelectAlterFunction(GPIO_PORTE,GPIO_PIN4);
	GPIO_vidSetPinDigEnable(GPIO_PORTE,GPIO_PIN4,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTE,GPIO_PIN4,0x4);
	
	/*PWM channel 5*/
	GPIO_vidSelectAlterFunction(GPIO_PORTE,GPIO_PIN5);
	GPIO_vidSetPinDigEnable(GPIO_PORTE,GPIO_PIN5,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTE,GPIO_PIN5,0x4);
	
	/*PWM channel 6*/
	GPIO_vidSelectAlterFunction(GPIO_PORTD,GPIO_PIN0);
	GPIO_vidSetPinDigEnable(GPIO_PORTD,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTD,GPIO_PIN0,0x4);
	/*PWM channel 7*/
	GPIO_vidSelectAlterFunction(GPIO_PORTD,GPIO_PIN0);
	GPIO_vidSetPinDigEnable(GPIO_PORTD,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTD,GPIO_PIN1,0x4);

	/*LED*/
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN2,GPIO_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN2,GPIO_DEN_SET);
	GPIO_vidSetPinValue(GPIO_PORTF,GPIO_PIN2,STD_LOW);

	
	/*PWM configuration*/
	PWMConfig_0.u8Module = PWM_MODULE_0;
	PWMConfig_0.u8Generator = PWM_GENERATOR_0;
	PWMConfig_0.u8Channel = PWM_CHANNEL_0;
	PWMConfig_0.u16Output =PWM_OUTPUTACT_COMPA_DOWN_HIGH |PWM_OUTPUTACT_LOAD_LOW;
	PWMConfig_0.u8CountDirection = PWM_COUNTDIR_DOWN;
	PWMConfig_0.u16LoadVal = 50000;
	PWMConfig_0.u16CompVal = 20000;
	
	PWMConfig_1.u8Module = PWM_MODULE_0;
	PWMConfig_1.u8Generator = PWM_GENERATOR_0;
	PWMConfig_1.u8Channel = PWM_CHANNEL_1;
	PWMConfig_1.u16Output = PWM_OUTPUTACT_COMPB_DOWN_HIGH|PWM_OUTPUTACT_LOAD_LOW;
	PWMConfig_1.u8CountDirection = PWM_COUNTDIR_DOWN;
	PWMConfig_1.u16LoadVal = 50000;
	PWMConfig_1.u16CompVal = 10000;
	
	PWMConfig_t PWMConfig_2;
	PWMConfig_2.u8Module = PWM_MODULE_0;
	PWMConfig_2.u8Generator = PWM_GENERATOR_1;
	PWMConfig_2.u8Channel = PWM_CHANNEL_2;
	PWMConfig_2.u16Output = PWM_OUTPUTACT_COMPA_DOWN_INVERT|PWM_OUTPUTACT_LOAD_HIGH;
	PWMConfig_2.u8CountDirection = PWM_COUNTDIR_DOWN;
	PWMConfig_2.u16LoadVal = 50000;
	PWMConfig_2.u16CompVal = 45000;
	
	PWMConfig_t PWMConfig_3;
	PWMConfig_3.u8Module = PWM_MODULE_0;
	PWMConfig_3.u8Generator = PWM_GENERATOR_1;
	PWMConfig_3.u8Channel = PWM_CHANNEL_3;
	PWMConfig_3.u16Output = PWM_OUTPUTACT_COMPB_DOWN_INVERT|PWM_OUTPUTACT_LOAD_HIGH;
	PWMConfig_3.u8CountDirection = PWM_COUNTDIR_DOWN;
	PWMConfig_3.u16LoadVal = 50000;
	PWMConfig_3.u16CompVal = 45000;
	
	PWMConfig_t PWMConfig_4;
	PWMConfig_4.u8Module = PWM_MODULE_0;
	PWMConfig_4.u8Generator = PWM_GENERATOR_2;
	PWMConfig_4.u8Channel = PWM_CHANNEL_4;
	PWMConfig_4.u16Output = PWM_OUTPUTACT_COMPA_DOWN_HIGH | PWM_OUTPUTACT_LOAD_LOW;
	PWMConfig_4.u8CountDirection = PWM_COUNTDIR_DOWN;
	PWMConfig_4.u16LoadVal = 50000;
	PWMConfig_4.u16CompVal = 45000;
	
	PWMConfig_t PWMConfig_5;
	PWMConfig_5.u8Module = PWM_MODULE_0;
	PWMConfig_5.u8Generator = PWM_GENERATOR_2;
	PWMConfig_5.u8Channel = PWM_CHANNEL_5;
	PWMConfig_5.u16Output = PWM_OUTPUTACT_COMPB_DOWN_HIGH | PWM_OUTPUTACT_LOAD_LOW;
	PWMConfig_5.u8CountDirection = PWM_COUNTDIR_DOWN;
	PWMConfig_5.u16LoadVal = 50000;
	PWMConfig_5.u16CompVal = 45000;
	
	PWMConfig_t PWMConfig_6;
	PWMConfig_6.u8Module = PWM_MODULE_0;
	PWMConfig_6.u8Generator = PWM_GENERATOR_2;
	PWMConfig_6.u8Channel = PWM_CHANNEL_6;
	PWMConfig_6.u16Output = PWM_OUTPUTACT_COMPB_DOWN_HIGH | PWM_OUTPUTACT_LOAD_LOW;
	PWMConfig_6.u8CountDirection = PWM_COUNTDIR_DOWN;
	PWMConfig_6.u16LoadVal = 50000;
	PWMConfig_6.u16CompVal = 45000;
	
	PWMConfig_t PWMConfig_7;
	PWMConfig_7.u8Module = PWM_MODULE_0;
	PWMConfig_7.u8Generator = PWM_GENERATOR_3;
	PWMConfig_7.u8Channel = PWM_CHANNEL_7;
	PWMConfig_7.u16Output = PWM_OUTPUTACT_COMPB_DOWN_HIGH | PWM_OUTPUTACT_LOAD_LOW;
	PWMConfig_7.u8CountDirection = PWM_COUNTDIR_DOWN;
	PWMConfig_7.u16LoadVal = 50000;
	PWMConfig_7.u16CompVal = 45000;
	
	PWM_vidDisableGenerator(PWMConfig_0.u8Module,PWMConfig_0.u8Generator);
	PWM_vidConfigCountDir(PWMConfig_0.u8Module,PWMConfig_0.u8Generator,PWMConfig_0.u8CountDirection);
	PWM_vidConfigCountDir(PWMConfig_4.u8Module,PWMConfig_4.u8Generator,PWMConfig_4.u8CountDirection);

	PWM_vidSetOutput(PWMConfig_0.u8Module,PWMConfig_0.u8Generator,PWM_BLOCK_A,PWMConfig_0.u16Output);
	PWM_vidSetOutput(PWMConfig_1.u8Module,PWMConfig_1.u8Generator,PWM_BLOCK_B,PWMConfig_1.u16Output);
	PWM_vidSetOutput(PWMConfig_2.u8Module,PWMConfig_2.u8Generator,PWM_BLOCK_A,PWMConfig_2.u16Output);
	PWM_vidSetOutput(PWMConfig_3.u8Module,PWMConfig_3.u8Generator,PWM_BLOCK_B,PWMConfig_3.u16Output);
	PWM_vidSetOutput(PWMConfig_4.u8Module,PWMConfig_4.u8Generator,PWM_BLOCK_A,PWMConfig_4.u16Output);
	PWM_vidSetOutput(PWMConfig_5.u8Module,PWMConfig_5.u8Generator,PWM_BLOCK_B,PWMConfig_5.u16Output);
	PWM_vidSetOutput(PWMConfig_6.u8Module,PWMConfig_6.u8Generator,PWM_BLOCK_A,PWMConfig_6.u16Output);
	PWM_vidSetOutput(PWMConfig_7.u8Module,PWMConfig_7.u8Generator,PWM_BLOCK_B,PWMConfig_7.u16Output);

	PWM_vidAssignLoadVal(PWMConfig_0.u8Module,PWMConfig_0.u8Generator,PWMConfig_0.u16LoadVal);
	PWM_vidAssignLoadVal(PWMConfig_2.u8Module,PWMConfig_2.u8Generator,PWMConfig_2.u16LoadVal);
	PWM_vidAssignLoadVal(PWMConfig_4.u8Module,PWMConfig_4.u8Generator,PWMConfig_4.u16LoadVal);
	PWM_vidAssignLoadVal(PWMConfig_6.u8Module,PWMConfig_6.u8Generator,PWMConfig_6.u16LoadVal);
	
	PWM_vidSetCompValue(PWMConfig_0.u8Module,PWMConfig_0.u8Generator,PWMConfig_0.u8Channel,PWMConfig_0.u16CompVal);
	PWM_vidSetCompValue(PWMConfig_1.u8Module,PWMConfig_1.u8Generator,PWMConfig_1.u8Channel,PWMConfig_1.u16CompVal);
	PWM_vidSetCompValue(PWMConfig_2.u8Module,PWMConfig_2.u8Generator,PWMConfig_2.u8Channel,PWMConfig_2.u16CompVal);
	PWM_vidSetCompValue(PWMConfig_3.u8Module,PWMConfig_3.u8Generator,PWMConfig_3.u8Channel,PWMConfig_3.u16CompVal);
	PWM_vidSetCompValue(PWMConfig_4.u8Module,PWMConfig_4.u8Generator,PWMConfig_4.u8Channel,PWMConfig_4.u16CompVal);
	PWM_vidSetCompValue(PWMConfig_5.u8Module,PWMConfig_5.u8Generator,PWMConfig_5.u8Channel,PWMConfig_5.u16CompVal);
	PWM_vidSetCompValue(PWMConfig_6.u8Module,PWMConfig_6.u8Generator,PWMConfig_6.u8Channel,PWMConfig_6.u16CompVal);
	PWM_vidSetCompValue(PWMConfig_7.u8Module,PWMConfig_7.u8Generator,PWMConfig_7.u8Channel,PWMConfig_7.u16CompVal);

	PWM_vidSelectChannel(PWMConfig_0.u8Module,PWMConfig_0.u8Channel);
	PWM_vidSelectChannel(PWMConfig_1.u8Module,PWMConfig_1.u8Channel);
	PWM_vidSelectChannel(PWMConfig_2.u8Module,PWMConfig_2.u8Channel);
	PWM_vidSelectChannel(PWMConfig_3.u8Module,PWMConfig_3.u8Channel);
	PWM_vidSelectChannel(PWMConfig_4.u8Module,PWMConfig_4.u8Channel);
	PWM_vidSelectChannel(PWMConfig_5.u8Module,PWMConfig_5.u8Channel);
	PWM_vidSelectChannel(PWMConfig_6.u8Module,PWMConfig_6.u8Channel);
	PWM_vidSelectChannel(PWMConfig_7.u8Module,PWMConfig_7.u8Channel);

	PWM_vidEnableGenerator(PWMConfig_1.u8Module,PWMConfig_1.u8Generator);
	PWM_vidEnableGenerator(PWMConfig_2.u8Module,PWMConfig_2.u8Generator);
	PWM_vidEnableGenerator(PWMConfig_4.u8Module,PWMConfig_4.u8Generator);
	PWM_vidEnableGenerator(PWMConfig_6.u8Module,PWMConfig_6.u8Generator);

	/*UART Control*/
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN0);
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN1);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN0,0x1);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN1,0x1);
	
	UARTConfig_t UART0Config;
	UART0Config.u16Integer = 8;
	UART0Config.u8Fraction = 44;
	UART0Config.u8FIFOEnabled = UART_FIFO_DISABLED;
	UART0Config.u8HighSpeedEnabled = UART_HIGHSPEED_DIV_16;
	UART0Config.u8WordLength = UART_WORDSIZE_8;
	UART0Config.u8RxTx = UART_RXTX_BOTH;
	UART0Config.u8InterruptEnabled = UART_INTERRUPT_ENABLED;
	UART0Config.ptrF = vidControlPWM;
	UART0_vidInit(&UART0Config);
	
	NVIC_vidSetInterrupt(NVIC_UART0);
	__enable_irq();
	while(1);
}