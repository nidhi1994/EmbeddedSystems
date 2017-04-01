/*Toggle PORTB.0 at 0.5Hz frequency, by triggering external interrupt pin by software.*/

void INTO_interrupt()        org 0x002           //inerrupt service routine
{
 PORTB^=0X01;                 // toggle PORTB.B0 pin
 delay_ms(1000);            // delay of 1  second
}

void main() {
     DDRB=0xFF;                  //all the pins of PORTA are directed to output
     PORTB=0x00;                    // all the output pins of PORB are set to 0
     DDRD.B2=1;               //external INTO direction
     PORTD.B2=1;               // external INT0 set 1 as it is falling edge

 GICR=0x40;              //enable external INT0
 MCUCR=0x00;                 //INT0 with low level
 SREG.B7=1;                     //g;obal interrupt bit set
 while(1)
      {
      delay_ms(1000);              // delay of 1 second
     PORTD.B2=0;                                       //external INT0 set to 0
      delay_ms(1000);              // delay of 1 second
     PORTD.B2=1;                                     //external INT0 set to 1
       }
}