/*
 Project Description : Display 4 digit Number
*/

//#include "SevenSegment_Cathod.c" // Include function file that converts decimal
// values to 7 segment display data values

unsigned int number; // Number to be displayed
unsigned short int store[4];// Store hex values in an array
unsigned short int shift=1;

int temp,count=0;
int count_time2=125;

/*
  In multiplexing, data and selection lines are changed at very small time
  intervals. In this case 8 msec.

*/

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

 void interrupt() org 0x02    //for external interrupt INT0
 {
 number++;                                                 //count number of visitors
 }
void TIMER0_COMP() org 0x014
{
 PORTA=0x00; // PORTA cleared

 PORTA=shift; // select data selection line
 PORTC=store[count];//Assign data to PORTC i.e. seven segment

 shift=shift<<1; // left shift 'shift' till it reahes 0x80
 if(shift==0x10)
 {
 shift=1; // Initialize once 0x80 is reached
 }

 count++; // increment count till it reaches 4   for 4 seven-segment displays

 if (count==4)
 {
 count=0; // Initialize once it reaches 4

 }


}



main(void) {
DDRD.B2=0;                             //In order to give external interrupt input pin.
PORTD.B2=1;                                                                            //input pulled-up.
// PORT declaration
DDRC=0xFF;    // Configure data line port C as output
DDRA=0x0F;   // Configure selection lines @ PORTA

PORTA=0x01; //Initialize

//Timer Set-Up

// Timer 0 CTC mode, pre-scaler 256 , count: 250
TCCR0=0x0B;
OCR0=0xF9;

//Interrupt Set-Up
SREG.B7=1; // Enable Global interrupt I
TIMSK.B1=1; // Enable Timer O Comp interrupt OCEI0
GICR.B6=1;       //external interrupt INT0
MCUCR=0x03;           //rising edge of INT0 generates a request


while(1)

{

 temp=number%10u; // Calculate unit digit of number
 store[0]=SevenSegment_Cathod(temp); // Convert it to SevenSegment Common cathode

 temp=(number/10u)%10u;// // Calculate tens digit
 store[1]=SevenSegment_Cathod(temp);// Convert it to SevenSegment Common cathode

 temp=(number/100u)%10u; // Calculate hundreds digit
 store[2]=SevenSegment_Cathod(temp);// Convert it to SevenSegment Common cathode

 temp=number/1000u; // Calculate thousands digit
 store[3]=SevenSegment_Cathod(temp);// Convert it to SevenSegment Common cathode

}


}