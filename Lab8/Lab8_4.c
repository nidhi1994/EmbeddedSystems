 /*
   Program :0
   Diplay "Hello World"
 */

//LCD Connections
#include<string.h>
#define LCD_RS  PORTA.B2   // RS
#define LCD_EN  PORTD.B6   //Enable
#define LCD_D4  PORTC.B4   //Data Bit 4
#define LCD_D5  PORTC.B5   //Data Bit 5
#define LCD_D6  PORTC.B6   //Data Bit 6
#define LCD_D7  PORTC.B7   //Data Bit 7

void LCD_data(unsigned char Data)
{
PORTC=Data&0xF0; // Send Higher nibble (D7-D4)
LCD_RS=1;       // Register Select =1 (for data select register)
LCD_EN=1;      //Enable=1 for H to L pulse
delay_us(5);
LCD_EN=0;


PORTC=((Data<<4)&0xF0); // Send Lower nibble (D3-D0)
LCD_EN=1;               //Enable=1 for H to L pulse
delay_us(5);
LCD_EN=0;

delay_us(100);
}


//LCD Print
void LCD_Print(char * str)
{
 unsigned char i=0;

 // Till NULL charecter is reached, take each character
 while(*(str+i)!=0)

 {
  LCD_data(*(str+i)); // Data sent to LCD data register
  i++;
  delay_ms(10);
 }
}
//LCD Command
void lcdcommand(unsigned char command)
{
PORTC=command&0xF0; // Send Higher nibble (D7-D4)
LCD_RS=0; // Register Select =0 (for Command register)
LCD_EN=1; //Enable=1 for H to L pulse
delay_us(5);
LCD_EN=0;
delay_us(100);

PORTC=((command<<4)&0xF0);  // Send Lower nibble (D3-D0)
LCD_EN=1; //Enable=1 for H to L pulse
delay_us(5);
LCD_EN=0;

delay_us(40);
}

// Cursor Posotion
void Cursor_Position(unsigned short int x,unsigned short int y)
{
 unsigned char firstcharadd[] ={0x80,0xC0}; // First line address 0X80
                                            //Second line address 0XC0
 lcdcommand((firstcharadd[x-1]+y-1));

}

void clear()
{
  lcdcommand(0x01);
  delay_ms(2);
}

 //LCD Iniatialize
void LCD_Initialize()
{
LCD_EN=0;

lcdCommand(0x33); // Initialize LCD for 4 bit mode
lcdCommand(0x32); // Initialize LCD for 4 bit mode
lcdCommand(0x28); // Initialize LCD for 5X7 matrix mode
lcdCommand(0x0E); //Display on,cursor blinking
clear();
lcdCommand(0x06); //Shift cursor to right
lcdCommand(0x80);
}


void main() {

  char disp1[]="Welcome to esd Lab";
  char disp2[]="Incorrect";
  char disp4[]="Enter passcode again";
  unsigned char passcode_status=0;     //to check if passcode is entered
  char passcode_set[5]="1001",passcode_entered[5];                   //to set passcode as 1001

 //Set-up PORTS for LCD
 DDRC=0xF0;  // For D3-D0
 DDRA.B2=1;  //For RS
 DDRD.B6=1;  //For Enable
  DDRB=0xF0; //configure pin0 to pin3 as input.
  PORTB=0xFF;   //pull up input
   while(passcode_status==0x00)//check if passcode is entered
  {
      LCD_Initialize();
      passcode_entered[0]=PINB.B0+48;     //take the input of passcode at pin0
      LCD_data('*');                      //display * on screen
      delay_ms(300);                      //assuming next pin be pressed in 0.3 s.
      passcode_entered[1]=PINB.B1+48;     //take the input of passcode at pin1
      LCD_data('*');                      //display * on screen
      delay_ms(300);                       //assuming next pin be pressed in 0.3 s.
      passcode_entered[2]=PINB.B2+48;  //take the input of passcode at pin2
      LCD_data('*');                     //display * on screen
      delay_ms(300);                      //assuming next pin be pressed in 0.3 s.
      passcode_entered[3]=PINB.B3+48;   //take the input of passcode at pin3
      LCD_data('*');                      //display * on screen
           passcode_entered[4]=0;          //to give null value
      if(!(strcmp(passcode_set,passcode_entered)))           // comparing passcode entered and set.
      {
       passcode_status=1;                                                    //if passcode is correct then setting passcode status as 1 .
       LCD_Initialize(); //Initialize
        LCD_Print(disp1); //Diplay Text

        while(1)
        {
         lcdCommand(0x18);//rotate text
         delay_ms(500);
         }
      }
      else
      {
          LCD_Initialize(); //Initialize
          LCD_Print(disp2);
          delay_ms(3000);
          LCD_Initialize(); //Initialize
          LCD_Print(disp4);
          delay_ms(1000);

      }


  }
  while(1);

 }