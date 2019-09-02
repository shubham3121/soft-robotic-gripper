
// ***** 1. Pre-processor Directives Section *****
#include "TExaS.h"
#include "tm4c123gh6pm.h"
#include "Port_Init.h"
// ***** 2. Global Declarations Section *****
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
#define GPIO_PORTE_DATA_R       (*((volatile unsigned long *)0x400243FC))
#define GPIO_PORTE_DIR_R        (*((volatile unsigned long *)0x40024400))
#define GPIO_PORTE_AFSEL_R      (*((volatile unsigned long *)0x40024420))
#define GPIO_PORTE_DEN_R        (*((volatile unsigned long *)0x4002451C))
#define GPIO_PORTE_AMSEL_R      (*((volatile unsigned long *)0x40024528))
#define GPIO_PORTE_PCTL_R       (*((volatile unsigned long *)0x4002452C))
	
#define GPIO_PORTF_DATA_R       (*((volatile unsigned long *)0x400253FC))
#define GPIO_PORTF_DIR_R        (*((volatile unsigned long *)0x40025400))
#define GPIO_PORTF_AFSEL_R      (*((volatile unsigned long *)0x40025420))
#define GPIO_PORTF_PUR_R        (*((volatile unsigned long *)0x40025510))
#define GPIO_PORTF_DEN_R        (*((volatile unsigned long *)0x4002551C))
#define GPIO_PORTF_LOCK_R       (*((volatile unsigned long *)0x40025520))
#define GPIO_PORTF_CR_R         (*((volatile unsigned long *)0x40025524))
#define GPIO_PORTF_AMSEL_R      (*((volatile unsigned long *)0x40025528))
#define GPIO_PORTF_PCTL_R       (*((volatile unsigned long *)0x4002552C))
#define SYSCTL_RCGC2_R          (*((volatile unsigned long *)0x400FE108))
unsigned long in;	
// FUNCTION PROTOTYPES: Each subroutine defined

void DisableInterrupts(void); // Disable interrupts
void EnableInterrupts(void);  // Enable interrupts
void delayms(unsigned long);// Delay function
// ***** 3. Subroutines Section *****

void PortE_Init(){volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000010;
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTE_DIR_R |= 0x06;
	GPIO_PORTE_AFSEL_R &= ~0x06;
	GPIO_PORTE_AMSEL_R &= ~0x06;
	GPIO_PORTE_PCTL_R &= ~0x00000FF0;
	GPIO_PORTE_DEN_R |= 0x06;
}

void PortF_Init(){volatile unsigned long delay;
	SYSCTL_RCGC2_R |= 0x00000020;
	delay = SYSCTL_RCGC2_R;
	GPIO_PORTF_LOCK_R = 0x4C4F434B;
	GPIO_PORTF_CR_R = 0x11;
	GPIO_PORTF_DIR_R &= ~0x11;
	GPIO_PORTF_AMSEL_R &= ~0x11;
	GPIO_PORTF_AFSEL_R &= ~0x11;
	GPIO_PORTF_DEN_R |= 0x11;
	GPIO_PORTF_PCTL_R &= ~0x0000000F;
	GPIO_PORTF_PUR_R |= 0x11;
	
	
}

int main(void){ 
//**********************************************************************

//**********************************************************************
  unsigned long volatile delay;
	TExaS_Init(SW_PIN_PE0, LED_PIN_PE1);  // activate grader and set system clock to 80 MHz
	
  EnableInterrupts();           // enable interrupts for the grader
	PortE_Init();
	PortF_Init();
	while(1){

		if(GPIO_PORTF_DATA_R == 0x01){
			while(GPIO_PORTF_DATA_R == 0x01)
				GPIO_PORTE_DATA_R |= 0x02;
			GPIO_PORTE_DATA_R &= ~0x02;
			delayms(3000);
		}
		else if(GPIO_PORTF_DATA_R == 0x10){
			GPIO_PORTE_DATA_R |= 0x04;
			delayms(2000);
			GPIO_PORTE_DATA_R &= ~0x04;
			delayms(3000);
		}
		else{
			GPIO_PORTE_DATA_R &= ~0x06;
		}
  }
  
}
void delayms(unsigned long ms){
	unsigned long count;
  while(ms > 0 ) { // repeat while there are still ms to delay
    count = 16000; // number of counts to delay 1ms at 80MHz
    while (count > 0) { 
      count--;
    } // This while loop takes approximately 3 cycles
    ms--;
}
}
