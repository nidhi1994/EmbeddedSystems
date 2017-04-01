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

float n1,n2,n3=0.0;
            int flag=0;
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

   // ADC Single Conversion
// INPUT : PORTA.0  0-5V
// OUTPUT : PORTB  ADCH value
//          PORTB  ADCL value



void ADC() org 0x020
{
 //PORTC=ADCL; //Diplay ADCL value @ PORTC
 //PORTB=ADCH; //Diplay ADCH value @ PORTB

 n1=ADCH;
 n2=ADCL;
 n3=((((256*n1 )+ n2))*5000)/1024;
 flag=1;
ADCSRA.B6=1; // After completion of earlier conversion, start                 //new conversion
}


void main() {
char  disp[] =".";
char disp2[]="hello";
float temp;
 //Set-up PORTS for LCD
 DDRC=0xF0;  // For D3-D0
 DDRA.B2=1;  //For RS
 DDRD.B6=1;  //For Enable

DDRA.B0=0;  // Set PinA.0 as input

//DDRB=0xFF;  //ADCH output
//DDRC=0xFF;  //ADCL Output

//Initialize
//PORTB=0x00;
//PORTC=0x00;

ADMUX=0b00000001;      //Reference Voltage Vcc, Left Adjust, ADC0
ADCSRA=0b10001111;     //ADC enable,ADC interrupt enable,Presclaer 128

SREG.B7=1; // Global Interrupt enable

ADCSRA.B6=1;  //Start ADC conversion


             LCD_Initialize();
             Cursor_Position(2,1);

             LCD_Print(disp2);

  while(1)
  {
      if(flag==1)
      {
          LCD_Initialize(); //Initialize
          Cursor_Position(1,1);

          temp=(((int)n3)%10); // Calculate unit digit of number
          LCD_data(temp+48);

           LCD_Print(disp);


          temp=(((int)(n3/10u))%10u);// // Calculate tens digit
          LCD_data(temp+48);

          temp=(((int)(n3/100u))%10u); // Calculate hundreds digit
          LCD_data(temp+48);

          temp=(((int)n3)/1000u); // Calculate thousands digit
          LCD_data(temp+48);


          flag=0;
     }
     else
     break;
 }
           //      LCD_data(n3+48);
             //    delay_ms(1000);

                }