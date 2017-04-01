//ques: input frequncy x hz output frequency x/3hz

void TIMER0_COMP() org 0x026   //addresing to interrupt timer0
  {
  TCNT2=0x00;               //initializing timer2 as 0
  }
void main() {
// PORTB Set-Up
DDRB=0x08;                //setting 3rd bit as output and 0th bit as input

 SREG.B7=1;                     //global interrupt bit set
   TCCR2=0x00;               // setting timer2 as timer
//Timer 0 Set-Up
 TCCR0=0x1F;                      //setting in CTC mode and setting as rising edge
 TCNT0=0x00;              //initializing counter of timer0 as 00
 OCR0=0x01;             //setting compare match value as 01 which will generate an interrupt when compare mvalue is true
 //timer2 setup
  TCCR2=0x18;          // settiing in  CTC mode and toggle waveform
 x=TCNT2;                  //            storing timer2 value in variable x
  OCR2=x/2;                        //setting compare match value as half of the x to divide doubled time period

  while(1)
  {
  //do nothing
  }
            }