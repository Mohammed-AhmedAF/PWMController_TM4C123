#include "STD_TYPES.h"
#include "Macros.h"
#include "GPIO_interface.h"
#include "SYSCNTRL_interface.h"
#include "TIMERS_interface.h"
#include "SysTick_interface.h"
#include "NVIC_interface.h"
#include "UART_interface.h"
#include "TM4C123.h"                    // Device header

static volatile u8 u8CountA = 0;
volatile u8 u8ReceivedByte = 0;
static TIMERConfig_t timer0BConfig;
static void vidBlink(void); 
void vidControlPWM(void);
void vidReceiveCommands(void);

static void vidBlink(void)
{
	u8CountA++;
	if (u8CountA == 25)
	{
		GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);
		u8CountA = 0;
		
	}
}

void vidControlPWM(void)
{
	GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);
	if (GPIO_u8GetInterruptStatus(GPIO_PORTF,GPIO_PIN0) == STD_HIGH)
	{
		timer0BConfig.u32MatchValue = 25000;
		TIMERS_vidInit(&timer0BConfig);
		GPIO_vidClearInterrupt(GPIO_PORTF,GPIO_PIN0);
	}
	else
	{
	timer0BConfig.u32MatchValue = 10000;
  TIMERS_vidInit(&timer0BConfig);
	GPIO_vidClearInterrupt(GPIO_PORTF,GPIO_PIN4);
	}
}

void vidReceiveCommands(void)
{
	static u32 u32Match = 0;
	static u8 u8Index = 0;
	static u8 u8Bytes[2];
	u8ReceivedByte = UART0_u8GetReceivedByte();
	u8Bytes[u8Index] = u8ReceivedByte;
	u8Index++;
	if (u8Index == 2)
	{
					u32Match = u8Bytes[1]*500;
					timer0BConfig.u32MatchValue = u32Match;
					TIMERS_vidInit(&timer0BConfig);
					GPIO_vidTogglePin(GPIO_PORTF,GPIO_PIN1);
					u8Index = 0;

	}

}

int main(void)
{
	/*Enabling clock for peripherals*/
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTF);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTB);
	SYSCNTRL_vidEnableGPIOClock(SYSCNTRL_GPIO_PORTA);
	SYSCNTRL_vidEnableUARTClock(SYSCNTRL_UART0);
	SYSCNTRL_vidEnableTimerClock(SYSCNTRL_TIMER_2);

	/*GPIO pin configuration*/
	GPIO_vidSetPinDirection(GPIO_PORTF,GPIO_PIN1,GPIO_DIR_OUTPUT);
	GPIO_vidSetPinDigEnable(GPIO_PORTF,GPIO_PIN1,GPIO_DEN_SET);

	/*External interrupt GPIO pin (F0)) configuration*/
	GPIO_vidUnlock(GPIO_PORTF);
	GPIO_vidCommit(GPIO_PORTF,GPIO_PIN0);
	GPIOConfig_t strctGPIOF0Config;
	strctGPIOF0Config.u8DigEnable = GPIO_DEN_SET;
	strctGPIOF0Config.u8Direction = GPIO_DIR_INPUT;
	strctGPIOF0Config.u8Port = GPIO_PORTF;
	strctGPIOF0Config.u8Pin = GPIO_PIN0;
	GPIO_vidConfigurePin(&strctGPIOF0Config);
	
	ExtInterruptConfig_t strctExtInterrupt;
	strctExtInterrupt.ptrFunc = vidControlPWM;
	strctExtInterrupt.u8BothEdges = GPIO_INTERRUPT_EVENTCONTROLLED;
	strctExtInterrupt.u8InterruptSense = GPIO_SENSE_EDGE;
	strctExtInterrupt.u8InterruptEvent = GPIO_EVENT_FALLINGEDGE;
	strctExtInterrupt.u8PullResistance = GPIO_PUR_ENABLED;
	GPIO_vidConfigInterrupt(GPIO_PORTF,GPIO_PIN0,&strctExtInterrupt);
	
	/*External interrupt GPIO pin (F4) configuration*/
	GPIO_vidUnlock(GPIO_PORTF);
	GPIO_vidCommit(GPIO_PORTF,GPIO_PIN4);
	GPIOConfig_t strctGPIOF4Config;
	strctGPIOF4Config.u8DigEnable = GPIO_DEN_SET;
	strctGPIOF4Config.u8Direction = GPIO_DIR_INPUT;
	strctGPIOF4Config.u8Pin = GPIO_PIN4;
	strctGPIOF4Config.u8Port = GPIO_PORTF;
	GPIO_vidConfigurePin(&strctGPIOF4Config);
	
	ExtInterruptConfig_t strctExtIntrptF4Config;
	strctExtIntrptF4Config.ptrFunc = vidControlPWM;	
	strctExtIntrptF4Config.u8BothEdges = GPIO_INTERRUPT_EVENTCONTROLLED;
	strctExtIntrptF4Config.u8InterruptSense = GPIO_SENSE_EDGE;
	strctExtIntrptF4Config.u8InterruptEvent = GPIO_EVENT_FALLINGEDGE;
	strctExtIntrptF4Config.u8PullResistance = GPIO_PUR_ENABLED;
	GPIO_vidConfigInterrupt(GPIO_PORTF,GPIO_PIN4,&strctExtIntrptF4Config);

	/*PWM pin configuration*/
	GPIO_vidSelectAlterFunction(GPIO_PORTB,GPIO_PIN1);
	GPIO_vidSetPinDigEnable(GPIO_PORTB,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTB,GPIO_PIN1,0x7);
	
	/*Timer configuration*/
	timer0BConfig.ptrFunc = vidBlink;
	timer0BConfig.u8TimerID = TIMERS_TIMER_2;
	timer0BConfig.u8TimerBlock = TIMERS_BLOCK_B;
	timer0BConfig.u16ReloadValue = 50000;
	timer0BConfig.u32MatchValue = 10000;
	timer0BConfig.u16PrescalerValue = 0;
	timer0BConfig.u8Config = TIMERS_CONFIG_1632_16BIT;
	timer0BConfig.u8PWM = TIMERS_PWM_ENABLED;
	timer0BConfig.u8InterruptMask = TIMERS_INTERRUPT_TIMEOUT;
	timer0BConfig.u8PWMInverted = TIMERS_PWM_INVERTED;
	timer0BConfig.u8TimerMode = TIMERS_MODE_PERIODIC;
	timer0BConfig.u8TimerCountDir = TIMERS_COUNTDIR_UP;
	TIMERS_vidInit(&timer0BConfig);

	/*UART0 pin configuration*/
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN0);
	GPIO_vidSelectAlterFunction(GPIO_PORTA,GPIO_PIN1);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN0,GPIO_DEN_SET);
	GPIO_vidSetPinDigEnable(GPIO_PORTA,GPIO_PIN1,GPIO_DEN_SET);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN0,0x1);
	GPIO_vidConfigPortControl(GPIO_PORTA,GPIO_PIN1,0x1);

	/*UART0 configuration*/
	UARTConfig_t strctUART0Config;
	strctUART0Config.u8ClockSource = UART_CLOCKSOURCE_RC;
	strctUART0Config.u8FIFOEnabled = UART_FIFO_DISABLED;
	strctUART0Config.u16Integer = 104;
	strctUART0Config.u8Fraction = 11;
	strctUART0Config.u8HighSpeedEnabled = UART_HIGHSPEED_DIV16;
	strctUART0Config.u8RxTx = UART_RXTX_BOTH;
	strctUART0Config.u8WordLength = UART_WORDSIZE_8;
	strctUART0Config.u8InterruptEnabled = UART_INTERRUPT_ENABLED;
	strctUART0Config.ptrF = vidReceiveCommands;
	UART0_vidInit(&strctUART0Config);

	/*NVIC configuration*/
	NVIC_vidSetInterrupt(NVIC_TIMER2B);
	NVIC_vidSetInterrupt(NVIC_GPIOF);
	NVIC_vidSetInterrupt(NVIC_UART0);
	
	/*Enable global interrupt*/
	__enable_irq();
	
	while(1);
}