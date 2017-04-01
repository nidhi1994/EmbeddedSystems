  /*forgot to include in lab6.zip*/
void main() {
// PORTB Set-Up
DDRB=0x08;//as OC0 pin is on bit 7.


//Timer 0 Set-Up
 TCCR0=0x1F;      //Set OC0 on compare match we set COM01 as 1 and COM00 as 1 which are bits 5,4 respectively.
              // As presaclar is 64 so last 3 clock bits are 011 and 4th bit 1 for waveform generation as it is in CTC mode
              //We will give input at T0 pin which is bit 0 of PORT B,so it will be given 0.
 TCNT0=0x00;   // Since value in TCNT0 keeps on changing after timer is ON,count value is loaded
 OCR0=0x04;       //As we want a waveform of  frequency  X/10Hz  suppose input waveform is 1kHz then period would be 1 ms . The output waveform should be 0.1kHz whose period
                   // would be 10ms. In 1 ms waveform there would be 5 rising edges upto 10th ms .So the counter should go from 0 to four in input waveform then rise.So each time
                   //TCNT value is compared with 4.

  while(1)
  {
  //do nothing
  }
            }