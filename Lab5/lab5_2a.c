 void TIMER0_COMP() org 0x026
  {
   PORTA^=0x01; // Toggle PORTA.0 every time this subroutine is called
      TCNT0=0x00;       // Since value in TCNT0 keeps on changing after timer is ON,count value is loaded
  }


void main() {
 // PORTA Set-Up
 DDRA=0x01; // Set PORTA.0 as O/P
 PORTA=0X01; // Initialize PORTA.0 to 1

//Timer 0 Set-Up
 TCCR0=0x0B;  //  as presaclar is 64 so last 3 clock bits are 011 and 4th bit 1 for wveform generation as it is in CTC mode
 TCNT0=0x00; // Since value in TCNT0 keeps on changing after timer is ON,count value is loaded
 OCR0=0x3E;    // comparing counter  62 and TCNT


//GLobal and Timer 0 Compare  Interrupt enable
  TIMSK.B1=1;  //OCIE0 Enable
  SREG.B7=1;   // Global interrupt enable

  while(1)
  {
  //do nothing
  }
            }