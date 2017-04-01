/*Blink LED at 1st pin of PORTB at 0.25Hz.  When an external interrupt 
occurs at 1st pin of PORTD, it blinks LED at 1st  pin 
of  PORTA for 2 times (@ 1Hz). After completion of this operation,
 it resumes to its normal task of blinking 1st  pin of  PORTB.*/
void INTO_interrupt()        org 0x002          //interrupt service routine
{
unsigned char i;          //initializing counter
for(i=0;i<2;i++)                                //loop for blinking two times
{
 PORTA ^= 0x01;               //toggle PORTA.B0 pin
 delay_ms(500);                //delay of half second
}
}

void main()
{
 DDRA=0x01;          //PORTA.B0 direction set for output
 PORTA=0x00;           //PORTA.B0 bit intially set to 0.
  
 DDRB=0x01;    //PORTB.B0 direction set for output
 PORTB=0x01; //PORTB.B0 bit intially set to 1.

 DDRD.B2=0;         //external INT0 direction
 PORTD.B2=0;         //external INT0 set1
     //interrupt register
 GICR=0x40;           //enable external INT0
 MCUCR=0x02;         //INTO with falling edge
 SREG.B7=1;             //global interrupt bit set

 while(1)
 {
 PORTB^=0x01;        //toggle PORTB.B0 pin
 delay_ms(2000);     // 2second delay
 }
 }