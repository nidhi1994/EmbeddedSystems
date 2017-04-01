/*Write a program that counts and display the number of visitors at IET through 8-bit LED display. 
The doorkeeper presses the push button every time a new visitor enters and the count value is displayed at the dean's office in 8-bit LED display.

*/
void INTO_interrupt()        org 0x002 //inerrupt service routine
{
 PORTA=PORTA+0x01;           //adding 1 bit to port A when interrupt occurs

}

void main() {
     DDRA=0xFF;     //all the pins of PORTA are directed to output
     PORTA=0x00;     //  all output pins of PORTA are set to 0
      DDRD.B2=0;   //external INT0 direction
 PORTD.B2=0;        //external INT0 set 1

 GICR=0x40;  //enable external INT0
 MCUCR=0x02;       // INT0 with falling edge
 SREG.B7=1;              //global interrupt bit set

}