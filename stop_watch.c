#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>

#define VALUE_OF_COMPARE_REG_TIMER1 1000
#define NO_OF_COMPARE_MATCH_PER_SECOND_TIMER1 15
#define MAX_SECONDS 60
#define MAX_MINUTES 60
#define MAX_HOURS 100

/*----------------------------------------Global variables------------------------------------------------*/
unsigned char sec=0;                        /*controlling seconds*/
unsigned char min=0;                       /*controlling minutes*/
unsigned char hour=0;                     /*controlling hours*/
unsigned char g_tick=0;                  /*check number of compare match per second*/
unsigned char count_down=0;             /*check if button is pressed to enable count down */
unsigned char pause=0;                 /*check if stop watch is paused or not*/
/* Flags to track the status of button presses for adjusting hours, minutes, and seconds*/
unsigned char flag_hour_increment=0;
unsigned char flag_hour_decrement=0;
unsigned char flag_min_increment=0;
unsigned char flag_min_decrement=0;
unsigned char flag_sec_increment=0;
unsigned char flag_sec_decrement=0;

/*------------------------------------functions prototype------------------------------------------------ */
void pin_configration(void);
void TIMER1_compare_init(void);
void stop_watch_count_up(void);
void stop_watch_count_down(void);
void seven_segment_display(unsigned char  digit_control_pin , unsigned char digit_display);
void seven_segment_control(void);
void interrupt0_enable(void);
void interrupt1_enable(void);
void interrupt2_enable(void);
void Adjust_time(void);

/*-------------------------------------------main function------------------------------------------------ */
int main()
{
	SREG |=(1<<7);                  /*enable external interrupt*/

	unsigned char flag_PB7=0;

	pin_configration();
	TIMER1_compare_init();
	interrupt0_enable();
	interrupt1_enable();
	interrupt2_enable();
	while(1)
	{
		 seven_segment_control();               /*to display stop watch*/

		 if( !(PINB & (1<<PB7)) )              /*check if button on pin PB7 is pressed*/
		 {
			if(0==flag_PB7)
			{
			    PORTD &=~(1<<PD4);
			    PORTD |=(1<<PD5);
				count_down=1;            /* Set count_down to 1, indicating count down mode is enabled */
				flag_PB7=1;             /* Set flag_PB7 to 1 to indicate the button is pressed */
			}
			else
				flag_PB7=0;
		 }
		 else
		 {
			 PORTD &=~(1<<PD5);
			 PORTD |=(1<<PD4);
			 count_down=0;    /* If the button is not pressed, set count_down to 0, indicating normal mode */
		 }

		 if(pause)
		 {
			 Adjust_time();
		 }
	}
}



/*------------------------------------function to configure pins-------------------------------------------*/
void pin_configration(void)
{
    DDRB=0x00;                    /*make all port b in input direction*/
	PORTB=0XFF;                  /*enable internal resistance for port b*/

	/*pins of 7-segment*/
/*-------------------------*/
	DDRC |=0X0F;                   /* "0F=0000 1111" SET 1st 4 pins in port c to output direction*/
	PORTC &=0XF0;                 /*at 1st clear 1st 4 pins in port c*/

	DDRA |=0X3F;                /* "3f=0011 1111" set 1st 6 pin in port a to output directions*/
/*-------------------------*/
	DDRD |=0X31;
	PORTD |=(1<<PD4);                /*at 1st set led of counting up on "default mode" */
	PORTD &=~(1<<PD0) &~(1<<PD5);   /*at 1st set buzzer and led of counting down off*/
}

/*-------------------------------function to enable timer1 compare mode------------------------------------*/
void TIMER1_compare_init(void)
{
	TCNT1 = 0;                                                /*set initial value of counter to zero*/
	TCCR1A |=(1<<FOC1A);                                     /* non PWM mode*/
	TCCR1B |=(1<<WGM12) |(1<<CS12) |(1<<CS10);              /* choose Prescaler=1024 and Compare mode*/
	OCR1A=VALUE_OF_COMPARE_REG_TIMER1;                     /*set compare value to 1000*/
	TIMSK |= (1<<OCIE1A);                                 /* Compare mode timer1 Interrupt Enable */
}
/*-------------------------interrupt timer1 compare mode "Interrupt Service Routine"-----------------------*/
ISR(TIMER1_COMPA_vect) {
	g_tick++;

	if (g_tick == NO_OF_COMPARE_MATCH_PER_SECOND_TIMER1) /*check if 1second passed*/
	{
		if (count_down)   /*if count down=1*/
		{
			stop_watch_count_down();   /*count down stop watch*/
		}
		else    /*if count down=0 "default mode" */
		{
			 stop_watch_count_up();   /*count up stop watch*/
		}

		g_tick = 0;
	}

}

/*---------------------------------function to make stop watch count up------------------------------------*/
void stop_watch_count_up (void)
{
	PORTD &=~(1<<PD0);         /*if buzzer is set turn it of while count up mode*/

	sec++;

	if (MAX_SECONDS== sec)
	{
		sec = 0;
		min++;
	}
	if (MAX_MINUTES == min)
	{
		min = 0;
		hour++;
	}
	if ( MAX_HOURS == hour)
	{
		sec = 0;
		min = 0;
		hour = 0;
	}
}

/*---------------------------------function to make stop watch count down----------------------------------*/
void  stop_watch_count_down(void)
{
	PORTD &=~(1<<PD4);        /*set led of count up off*/
	PORTD |=(1<<PD5);        /*set led of count down on*/

	if (sec > 0)
	{
		sec--;
	}
	else if (sec == 0 && min > 0)
	{
		min--;
		sec = 59;
	}
	else if (sec == 0 && min == 0 && hour > 0)
	{
		hour--;
		min = 59;
		sec = 59;
	}
	else
	   /* If no time is left to count down,buzzer turned on*/
		PORTD |=(1<<PD0);
}

/*------------------------------function to display number on 7_segment------------------------------------*/
void seven_segment_display(unsigned char  digit_control_pin, unsigned char digit_display)
{
    PORTA &=0xC0;                                        /* "C0=1100 0000" disable 1st 6 pins in port a*/
    PORTA |= (1 << digit_control_pin);                  /*enable the selected 7-segment digit*/
    PORTC = (PORTC & 0xF0) | (digit_display & 0x0F);   /*display digit on 7-segment*/
}
/*-----------------------------------function to control 7_segment-----------------------------------------*/
void seven_segment_control(void)
{
    /* Display each digit sequentially*/
    seven_segment_display(PA5, sec % 10);           /* Display seconds units*/
    _delay_ms(2);
    seven_segment_display(PA4, sec / 10);          /* Display seconds tens*/
    _delay_ms(2);
    seven_segment_display(PA3, min % 10);         /*Display minutes units*/
    _delay_ms(2);
    seven_segment_display(PA2, min / 10);        /* Display minutes tens*/
    _delay_ms(2);
    seven_segment_display(PA1, hour % 10);      /* Display hours units*/
    _delay_ms(2);
    seven_segment_display(PA0, hour / 10);     /* Display hours tens*/
    _delay_ms(2);
}

/*---------------------------------function to enable external interrupt0----------------------------------*/
void interrupt0_enable(void)
{
	MCUCR |=(1<<ISC01);                /*enable interrupt with falling edge*/
	GICR |=(1<<INT0);                 /*enable external interrupt0*/
}
/*--------------------------------interrupt 0 "Interrupt Service Routine"----------------------------------*/
ISR(INT0_vect) /*to reset stop watch*/
{
	DDRD &=~(1<<PD2);                           /*make pin2 in port d in input direction*/
	PORTD |=(1<<PD2);                          /*enable internal resistance*/

	TCNT1=0;                                  /*set timer to start counting from 0 again*/

	/*reset seconds and minutes, hours */
	sec=0;
	min=0;
	hour=0;
}

/*---------------------------------function to enable external interrupt1----------------------------------*/
void interrupt1_enable(void)
{
	MCUCR |=(1<<ISC11) |(ISC10) ;       /*enable interrupt with rising edge*/
	GICR |=(1<<INT1);                  /*enable external interrupt1*/
}
/*--------------------------------interrupt 1 "Interrupt Service Routine"----------------------------------*/
ISR(INT1_vect)/*to pause stop watch*/
{
	DDRD &=~(1<<PD3);                              /*make pin3 in port d in input direction*/
	TCCR1B &=~(1<<CS12) &~(1<<CS11) &~(1<<CS10);  /*stop clock source of timer 1 (Timer/Counter stopped).*/
	pause=1;
}

/*---------------------------------function to enable external interrupt2----------------------------------*/
void interrupt2_enable(void)
{
	MCUCSR &=~(1<<ISC2);                    /*enable interrupt with falling edge*/
	GICR |=(1<<INT2);                      /*enable external interrupt2*/
}
/*--------------------------------interrupt 2 "Interrupt Service Routine"----------------------------------*/
ISR(INT2_vect)/*to resume stop watch*/
{
	DDRB |=(1<<PB2);                         /*make pin2 in port B in input direction*/
	PORTB |=(1<<PB2);                       /*enable internal resistance*/
    TCCR1B |=(1<<CS12) |(1<<CS10);         /*enable again clock source with prescaler=1024*/
    pause=0;
}

/*---------------------------------------function to Adjust time-------------------------------------------*/
void Adjust_time(void)
{

	if( !(PINB & (1<<PB0)) )
	{
		if(flag_hour_decrement==0)
		{
			if(hour>0)
			{
				hour--;
			}
			flag_hour_decrement=1;
		}
	}
	else
		flag_hour_decrement=0;


	if( !(PINB & (1<<PB1)) )
	{
		if(flag_hour_increment==0)
		{
			hour++;
			if( MAX_HOURS==hour)
			{
				hour=0;
				min=0;
				sec=0;
			}
			flag_hour_increment=1;
		}
	}
	else
		flag_hour_increment=0;


	if( !(PINB & (1<<PB3)) )
	{
		if(flag_min_decrement==0)
		{
			if(min>0)
			{
				min--;
			}
			flag_min_decrement=1;
		}
	}
	else
		flag_min_decrement=0;


	if( !(PINB & (1<<PB4)) )
	{
		if(flag_min_increment==0)
		{
			min++;
			if(MAX_MINUTES==min)
			{
				min=0;
				hour++;
			}
			flag_min_increment=1;
		}
	}
	else
		flag_min_increment=0;


	if( !(PINB & (1<<PB5)) )
		{
			if(flag_sec_decrement==0)
			{
				if(sec>0)
				{
					sec--;
				}
				flag_sec_decrement=1;
			}
		}
	else
		flag_sec_decrement=0;


	if( !(PINB & (1<<PB6)) )
		{
			if(flag_sec_increment==0)
			{
				sec++;
				if(MAX_SECONDS==sec)
				{
					sec=0;
					min++;
				}
				flag_sec_increment=1;
			}
		}
	else
		flag_sec_increment=0;


}
