  void TIMER0_OVF() org 0x012    // addressing to timer0 location interrupt
  {
   PORTA^=0x01; // Toggle PORTA.0 every time this subroutine is called
   TCNT0=0x00;  // Since value in TCNT0 keeps on changing after timer is ON,count value is loaded
  }

void main() {

 // PORTA Set-Up
 DDRA=0x01; // Set PORTA.0 as O/P
 PORTA=0X01; // Initialize PORTA.0 to 1

//Timer 0 Set-Up
 TCCR0=0x01;     //  set to 1 to enable 1 clock
 TCNT0=0x00;    // Since value in TCNT0 keeps on changing after timer is ON,
                //coount value is loaded


//Global and Timer 0 Overflow  Interrupt enable
  TIMSK.B0=1;  //TOIE0 Enable
  SREG.B7=1;   // Global interrupt enable

  while(1)
  {
  //do nothing
  }
}