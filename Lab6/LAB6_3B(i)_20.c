/*
Expected Time Period             ON time         OFF time        Actual Time Period
 1/(8Mhz/8)*256*2= 0.512        0.10ms          0.42ms          0.52ms

*/
void main() {
// PORTB Set-Up
DDRB=0x08;        //as OC0 pin is on bit 7.


//Timer 0 Set-Up
 TCCR0=0x62;    //  As we want phase correct PWM mode and  non-inverting mode so COM01 and COM00 will be 1 and 0 respectively  on bits 5 ,4 .
                //As we want  phase correct PWM mode so WGM01 and WGM00 would be 0 and 1 respectively  on bits 3,6 respectively.
                //Here prescalar is specified as 8 so 0,1,2 bits will be 0,1,0 respectively.
 TCNT0=0x00;   // Since value in TCNT0 keeps on changing after timer is ON,count value is loaded
 OCR0=0x32;     //We want duty cycle of 20% in non-inverting mode so by using formula (OCR+1)/256*100=20 we get value of OCR0 as 50.2 and its hex value as 32.


  while(1)
  {
  //do nothing
  }
            }