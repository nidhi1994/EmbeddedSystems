void TIMER0_COMP() org 0x026   //addresing to interrupt timer0
  {
   PORTA^=0x01; // Toggle PORTA.0 every time this subroutine is called
      TCNT0=0x00;          // Since value in TCNT0 keeps on changing after timer is ON,count value is loaded
  }
  unsigned char count;           // defining variable count
void TIMER2_COMP() org 0x006     //addresing to interrupt timer2
  {

      count++;
  }
  void main() {
 // PORTA Set-Up
 DDRA=0x01; // Set PORTA.0 as O/P
 PORTA=0X01; // Initialize PORTA.0 to 1
 // PORTB Set-Up
 DDRB=0x01; // Set PORTB.0 as O/P
 PORTB=0X01; // Initialize PORTB.0 to 1

//Timer 0 Set-Up
 TCCR0=0x0B;    //  as prescalar is 64 so last 3 clock bits are 011 and 4th bit 1 for wveform generation as it is in CTC mode
 TCNT0=0x00;          // Since value in TCNT0 keeps on changing after timer is ON,count value is loaded
 OCR0=0x3E;            // comparing counter  62 and TCNT
 
 //timer2   set-up
  TCCR2=0x0F;         //as prescalar is 1024 last 3 clock bits are set to 111 and 4th bit for waveform generation
TCNT2=0x00;              // Since value in TCNT2 keeps on changing after timer is ON,count value is loaded
 OCR2=0xFF;                     // comparing counter  255 and TCNT

  TIMSK=0x82;           //to enable first interupt 7th bit and second interrupt 1st bit
  SREG.B7=1;   // Global interrupt enable

  while(1)
  {
if(count==15)   //comparing counter with 15 becoause interrupt is called 15 times
  {
   PORTB^=0x01; // Toggle PORTB.0
   count=0;       // reset counter to 0
   }
    }
  }