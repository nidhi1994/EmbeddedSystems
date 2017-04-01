/*
Expected Time Period       ON time         OFF time        Actual Time Period
 1/(8Mhz/64)*256*2=4.4ms    3.6ms           0.8ms           4.4ms

*/
void main() {
// PORTB Set-Up
DDRB=0x08;      //as OC0 pin is on bit 7.


//Timer 0 Set-Up
 TCCR0=0x73;    //      As we want phase correct PWM mode and  inverting mode so COM01 and COM00 will be 1 on bits 5 ,4 .
                // As we want  phase correct PWM mode so WGM01 and WGM00 would be 0 and 1 respectively  on bits 3,6 respectively.
                //Here prescalar is specified as 64 so 0,1,2 bits will be 0,1,1 respectively.
 TCNT0=0x00;        // Since value in TCNT0 keeps on changing after timer is ON,count value is loaded
 OCR0=0x33;           //We want duty cycle of 80% in inverting mode so by using formula (256-OCR)/256*100=80 we get value of OCR0 as 51.2 and its hex value as 33.


  while(1)
  {
  //do nothing
  }
}