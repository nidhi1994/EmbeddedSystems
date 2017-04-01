
void main() {
// PORTB Set-Up
DDRB=0x08;     //as OC0 pin is on bit 7 of port B.


//Timer 0 Set-Up
 TCCR0=0x1B;  //Toggle OC0 on compare match we set COM01 as 0 and COM00 as 1 which are bits 5,4 respectively. 
              // As presaclar is 64 so last 3 clock bits are 011 and 4th bit 1 for waveform generation as it is in CTC mode
 TCNT0=0x00; // Since value in TCNT0 keeps on changing after timer is ON,count value is loaded
 OCR0=0x3E;    // comparing counter  62 and TCNT


  while(1)
  {
//do nothing
  }
            }