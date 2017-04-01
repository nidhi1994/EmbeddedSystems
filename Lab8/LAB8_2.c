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
unsigned int number;
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
  void interrupt() org 0x002
 {
 number++; //to count number of people
 }
              unsigned int temp;

              unsigned int disp[4];
void main() {


  char disp1[]="welcome to iet";
  char disp2[]="count:";
 char  disp3[5];
    char disp4[]="DEAN NEEDS a BREAK ! please come tomorrow";

 number=0000;

 //Set-up PORTS for LCD
 DDRC=0xF0;  // For D3-D0
 DDRA.B2=1;  //For RS
 DDRD.B6=1;  //For Enable
 
 DDRD.B2=0;//directed to input
 PORTD.B2=1;    //input pulled up


 //Interrupt Set-Up
 GICR.B6=1;
 MCUCR=0x03;

 SREG.B7=1; // Enable Global interrupt I

 LCD_Initialize(); //Initialize
 LCD_Print(disp1); //Diplay Text
 Cursor_Position(2,1);     //set cursor at 2 row and 1 column
    LCD_Print(disp2); //Diplay Text
      number= 9998;

 while(1)
 {
  if(number<9999)
  {

  temp=(number%10); // Calculate unit digit of number
  disp3[3]=temp+48;

  temp=((number/10u)%10u);// // Calculate tens digit
  disp3[2]=temp+48;

  temp=((number/100u)%10u); // Calculate hundreds digit
  disp3[1]=temp+48;

 temp=(number/1000u); // Calculate thousands digit
 disp3[0]=temp+48;

 disp3[4]=0;
 Cursor_Position(2,7);  //set cursor at row 2  and column 1 to display count value

 LCD_Print(disp3);
   }
   else
   break;
 }
 LCD_Initialize(); //Initialize
                            LCD_Print(disp4); //Diplay Text

     while(1)
             {         lcdCommand(0x18);//rotate text from left to right
                           delay_ms(1000);
                           }

 }
 
 
