void INTO_interrupt()        org 0x002
{
 PORTA ^= 0x01;
 
}

void main()
{
 DDRA=0x01;
 PORTA=0x01;
 
 DDRB=0x01;
 PORTB=0x01;
 
 DDRD.B2=0;
 PORTD.B2=0;
 
 GICR=0x40;
 MCUCR=0x02;
 SREG.B7=1;
 
 while(1)
 {
 PORTB^=0x01;
 delay_ms(2000);
 }
 }