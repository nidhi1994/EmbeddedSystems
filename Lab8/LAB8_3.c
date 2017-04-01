                                    /*
   Program :0
   Diplay "Hello World"
 */

//LCD Connections
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

  char disp1[]="******PORTB*****";
  char disp2[]="****STATUS******";
  char disp3[]="7 6 5 4 3 2 1 0";
  char disp4[]=" ";
 //Set-up PORTS for LCD
 DDRC=0xF0;  // For D3-D0
 DDRA.B2=1;  //For RS
 DDRD.B6=1;  //For Enable

DDRB=0x00;//set port B as input
PORTB=0xFF; //input pulled-up

 while(1)
 {
 
 LCD_Initialize(); //Initialize
 LCD_Print(disp1); //Diplay Text
 Cursor_Position(2,1);       //set cursor at row2 and column1.
 LCD_Print(disp2); //Diplay Text
 delay_ms(1000);         //in order to toggle b/w port status and input value
 clear();
 
LCD_Initialize(); //Initialize
LCD_Print(disp3);
Cursor_Position(2,1);
 LCD_data(PINB.B7 +48);//takes input from pin7 of port B and prints it.
 LCD_print(disp4);
 LCD_data(PINB.B6 +48);//takes input from pin6 of port B and prints it.
 LCD_print(disp4);
 LCD_data(PINB.B5 +48);  //takes input from pin5 of port B and prints it.
 LCD_print(disp4);
 LCD_data(PINB.B4 +48); //takes input from pin4 of port B and prints it.
 LCD_print(disp4);
 LCD_data(PINB.B3 +48);  //takes input from pin3 of port B and prints it.
 LCD_print(disp4);
 LCD_data(PINB.B2 +48);   //takes input from pin2 of port B and prints it.
 LCD_print(disp4);
 LCD_data(PINB.B1 +48);   //takes input from pin1 of port B and prints it.
 LCD_print(disp4);
 LCD_data(PINB.B0 +48);   //takes input from pin7 of port B and prints it.
 LCD_print(disp4);
delay_ms(1000);    //in order to toggle b/w port status and input value


 }

 }