  unsigned char count;
void TIMER0_COMP0() org 0x026
  {

      count++;        //incrementing counter
  }


void main() {
 // PORTA Set-Up
 DDRA=0x01; // Set PORTA.0 as O/P

//Timer 0 Set-Up
 TCCR0=0x0D;         //as prescalar is 1024 last 3 clock bits are set to 101  and 4th bit for waveform generation

                 TCNT0=0x00;         // Since value in TCNT0 keeps on changing after timer is ON,count value is loaded
        OCR0=0xFF;                  // comparing counter with 255
        //GLobal and Timer 0 Compare  Interrupt enable
        TIMSK.B1=1;  //OCIE0 Enable
  SREG.B7=1;   // Global interrupt enable
  count=0;     // initializing counter
  PORTA=0X00; // Initialize PORTA.0 to 1

  while(1)
  {
  if(count==15)        //comparing counter with 15 becoause interrupt is called 15 times
  {
   PORTA^=0x01; // Toggle PORTA.0
   count=0;      // reset counter to 0
   }
    }
    }