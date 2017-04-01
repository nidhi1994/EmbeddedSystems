/*Design a program that turns ON LED one by one at a port with 0.5 second of delay from Right to Left.
 One can change this direction by using Push Button R, which will shift LED from Left to Right.
 One can resume to left shift operation by pressing Push Button (L).

(Note:
* At any given instance only one LED will be ON.
*Once the 7th Pin is ON, Right Shifting will cause 0th pin of the port ON.
*Also, once the 0th Pin is ON Left Shifting will cause 7th pin of the port ON )
*/

 unsigned char i,j,flag;
 unsigned char p[8]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80}; //decalring global arrays of size 9 to blink upto 9
 unsigned char q[8]={0x80,0x40,0x20,0x10,0x08,0x04,0x02,0x01};   //decalring global arrays of size 9 to blink upto 9
void INTO_interrupt()        org 0x002    //interrupt service routine
{
for(j=i;j<8;j++)            //it will in left to right from the place (pin) where interrupt is applied
 {
               PORTA=q[j];                        //output at portA to on all leds consecutively
               delay_ms(500);                     // delay of 1 second
 }

}

void main() {
 DDRA=0xFF;           // all pins of port A are directed to output
 PORTA=0x00;          //all otuput pins of PORTA are set to 0
  DDRD.B2=0;           //external INT0 direction
 PORTD.B2=0;           //external INT0 set 0

 GICR=0x40;           //enable extrnal INT0
 MCUCR=0x02;         //INT0 with falling edge
 SREG.B7=1;       //global interrupt bit set

 while(1)
 {
 for(i=0;i<8;i++)
 {             PORTA=p[i];                        //output at portA to on all leds consecutively
               delay_ms(500);                     // delay of 1 second
 }
 }
}