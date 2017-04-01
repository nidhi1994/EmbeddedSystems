//#include "SevenSegment_Cathod.c"

unsigned short int number;

unsigned short int SevenSegment_Cathod(unsigned short int value) //A function for selecting a particular seven segment number in the form of hex code .
{
switch(value)
{
case 0: return 0xBF;
case 1: return 0x06;
case 2: return 0x5B;
case 3: return 0x4F;
case 4: return 0x66;
case 5: return 0x6D;
case 6: return 0x7D;
case 7: return 0x07;
case 8: return 0xFF;
case 9: return 0x6F;
case 10: return 0x77;
case 11: return 0x7F;
case 12: return 0x39;
case 13: return 0x3F;
case 14: return 0x79;
case 15: return 0x71;
}

}
      unsigned char count;
void TIMER0_COMP0() org 0x014
  {

      count++;        //incrementing counter
  }

       unsigned short int i;
        //    unsigned short int SevenSegment_Cathod(unsigned short int val);
main(void)
{
        DDRC=0xFF;        // Configure data line port C as output
        DDRA=0x0F;        // Configure selection lines of lower nibble of PORTA
                          //   as OUTPUT
        PORTA=0x01;       // Since display is required only at 1st SevenSegment
        number=0;         //Initialize number
        
        TCCR0=0x05;         //as prescalar is 1024 last 3 clock bits are set to 101 and 4th bit for waveform generation
        SREG.B7=1;   // Global interrupt enable
  count=0;     // initializing counter
        //GLobal and Timer 0 Compare  Interrupt enable
        TIMSK.B1=1;  //OCIE0 Enable
              TCNT0=0x00;//initialize with 0.
        
    while(1)
    {


       PORTC=SevenSegment_Cathod(number);    //call 7-segment display function

   if(count==30)        //comparing counter with 30 becoause interrupt is called 30 times in order to generate 1 second of delay.
   {
    count=0;  
     number++;    // reset counter to 0
    }
    //}

// }
 if(number==16)
 {
  number=0;                //in this case once number reaches F it has to roll back so given 0 to number.
  }
    }
}