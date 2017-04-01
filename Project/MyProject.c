
//LCD Connections
#define LCD_RS  PORTD.B5   // RS
#define LCD_EN  PORTD.B6   //Enable
#define LCD_D4  PORTA.B4   //Data Bit 4
#define LCD_D5  PORTA.B5   //Data Bit 5
#define LCD_D6  PORTA.B6   //Data Bit 6
#define LCD_D7  PORTA.B7   //Data Bit 7

 unsigned char RFID_No[12],ch2,ch,rfid[13];
 unsigned char masterrfid[12]={'2','9','0','0','9','1','0','1','D','E','6','7'};
  int flag=0,j=0,k,rolladd,rfidadd=0;
  unsigned char rollno_key[7];
  unsigned int i=0;
unsigned char keypad[4][4] ={'A','3','2','1',
                                 'B','6','5','4',
                                 'R','9','8','7',
                                 ' ','#','0','*'};

int keypadfunc()
{
 unsigned char ch1;
 unsigned char collumn,row;


 DDRC=0xF0;
PORTC=0x0F;
do
      {
       PORTC =0x0F;
       collumn =(PINC&0x0F) ;
      }
     while(collumn!=0x0F);

     // Once the key is pressed
     do
      {
       do
       {
        PORTC =0x0F;
        delay_ms(20);

        collumn=(PINC&0x0F);
       }
       while(collumn==0x0F);

       // Debounce check
       PORTC =0x0F;
       delay_ms(20);
       collumn=(PINC&0x0F);
      }
      while(collumn==0x0F);

      while(1)
      {
        // ROW and COLLUMN CHECK

        // Check if key in first row is pressed
       PORTC=0xEF;
        delay_us(1);
        collumn=(PINC&0x0F);

        if(collumn!=0x0F)
        {
          row=0;
          break;
        }

        // Check if key in second row is pressed
        PORTC=0XDF;
        delay_us(1);
        collumn=(PINC&0x0F);

        if(collumn!=0x0F)
        {
         row=1;
         break;
        }

        // Check if key in third row is pressed
        PORTC=0xBF;
        delay_us(1);
        collumn=(PINC&0x0F);
        if(collumn!=0x0F)
        {
         row=2;
         break;
        }

        //// Key in fourth row is pressed
        PORTC=0X7F;
        delay_us(1);
        collumn=(PINC&0x0F);
        row=3;
        break;
      }


      // COLLUMN CHECK
      //Once collumn is decide,
       if(collumn==0x0E)
       {
         //PORTD=(keypad[row][0]);
          ch1=keypad[row][0];
          }
        else if(collumn==0x0D)
       {
         //PORTD=(keypad[row][1]);
         ch1=keypad[row][1];
         }
        else if(collumn==0x0B)
       {
         //PortD=(keypad[row][2]);
         ch1=keypad[row][2];
         }
       else
       {
         //PortD=(keypad[row][3]);
         ch1=keypad[row][3];
       }
       return ch1;
}

void LCD_data(unsigned char Data)
{
PORTA=Data&0xF0; // Send Higher nibble (D7-D4)
LCD_RS=1;       // Register Select =1 (for data select register)
LCD_EN=1;      //Enable=1 for H to L pulse
delay_us(5);
LCD_EN=0;


PORTA=((Data<<4)&0xF0); // Send Lower nibble (D3-D0)
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
PORTA=command&0xF0; // Send Higher nibble (D7-D4)
LCD_RS=0; // Register Select =0 (for Command register)
LCD_EN=1; //Enable=1 for H to L pulse
delay_us(5);
LCD_EN=0;
delay_us(100);

PORTA=((command<<4)&0xF0);  // Send Lower nibble (D3-D0)
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
int checkValidInput()  //Checks whether the RFID number is detected properly By xoring even n odd bits respectively and comparing result with last two bits repectively
                       //if they match then it returns 1 else returns 0.
  {
         unsigned short int i = 0;
         unsigned char RFID_No1[13];
         for(i=0;i<13;i++)
         RFID_No1[i]=RFID_No1[i];

          for(; i<13; i++)
                RFID_No1[i] = RFID_No1[i]>64 ? RFID_No1[i]-55 : RFID_No1[i]-48;


          if( ( ( (RFID_No1[0] ^ RFID_No1[2]) ^ RFID_No1[4] ) ^ RFID_No1[6] ) ^ RFID_No1[8] == RFID_No1[10]
                          && ( ( (RFID_No1[1] ^ RFID_No1[3]) ^ RFID_No1[5] ) ^ RFID_No1[7] ) ^ RFID_No1[9] == RFID_No1[11])
          {
                  for(i = 0; i<12; i++)
                        RFID_No1[i] = RFID_No1[i]>9 ? RFID_No1[i]+55 : RFID_No1[i]+48;

                  return 1;
          }

          return 0;
  }


void eep_write(unsigned int uiAddress, unsigned char ucData)
{
/* Wait for completion of previous write */
while(EECR & (1<<EEWE));
EEARH=0x00;
/* Set up address and data registers */
EEARL = uiAddress;
EEDR = ucData;
/* Write logical one to EEMWE */
EECR |= (1<<EEMWE);
/* Start eeprom write by setting EEWE */
EECR |= (1<<EEWE);
}
unsigned char eep_read(unsigned int uiAddress)
{
/* Wait for completion of previous write */
while(EECR & (1<<EEWE))
;
EEARH=0x00;
/* Set up address register */
EEARL = uiAddress;                   --
/* Start eeprom read by writing EERE */
EECR |= (1<<EERE);
/* Return data from data register */
return EEDR;
}
void enterID()
  {
    E:flag=0;
           LCD_Initialize(); //Initialize
            LCD_Print("Place Mastercard");
            Delay_ms(50);
     D:      for(i=0;i<12;i++)
                  {
                          while(UCSRA.B7==0); // Wait till Data is received
                          RFID_No[i]=UDR;
                  }
                  for(i=0;i<12;i++)
                  rfid[i]=RFID_No[i];
                  rfid[12]='\0';
                  Cursor_Position(2,1);
                  LCD_Print(rfid);
                  delay_ms(2000);

                  if(checkValidInput())
                  {
                   for(i=0;i<12;i++)
                   {
                   if(rfid[i]==masterrfid[i]) //Compares value with the master rfid already stored in array.
                   flag++;                     //increments flag every time match occurs
                   }

                   delay_ms(500);
                   if(flag==12)                //if match is equal to 12 as their are 12 bits  then MasterRFID is correct.
                   {
                   clear();
                    LCD_print("Correct");
                     delay_ms(2000);
                    }
                   else
                   {
                   clear();
                    LCD_print("Wrong");
                    delay_ms(2000);
                     goto E;

                    }
                   }
                  else
                  {
                  clear();
                  LCD_Print("Place again:");
                  delay_ms(500);
                    goto D;
                  }
                  for(i=0;i<12;i++)
                  rfid[i]='\0';


  do{
              LCD_Initialize(); //Initialize
              LCD_Print("Place ID:");
              delay_ms(50);
              for(i=0;i<12;i++)
                  {
                          while(UCSRA.B7==0); // Wait till Data is received
                          RFID_No[i]=UDR;
                  }

                  for(i=0;i<12;i++)
                  {
                  eep_write(j,RFID_No[i]);


                  j++;
                  }
                  for(i=0;i<12;i++)
                  rfid[i]=RFID_No[i];
                  
                   k=j;
                  Cursor_Position(2,1);
                  LCD_Print(rfid);

                   delay_ms(2000);
                  clear(); //Initialize
                  LCD_Print("Enter rollno:");

  A:                i=1;
  Cursor_Position(2,1);
 while(ch2!=' ')
    {
    ch2=keypadfunc();
       if(ch2=='B')     //--------------------------------------------------------------->backspace
       {

        ch2=' ';

        Cursor_position(2,i-1);
       if(i<=1)
       {
       Cursor_position(2,1);
         i=2;
       }
       LCD_data(ch2);

        i--;
        ch2=0;
        Cursor_position(2,i);

        rollno_key[i-1]=0;
        k--;
        continue;
       }
       if(ch2=='R')  //---------------------------------------------------------------------->reset
       {
        goto A;
       }

        rollno_key[i-1]=ch2;
       i++;
       LCD_data(ch2);
       if(ch2==' ')
       continue;
       eep_write(k,ch2);

       k++;
}
delay_ms(2000);
ch2=0;
j=k;
LCD_Initialize(); //Initialize
LCD_Print("Add more cards" );
Cursor_Position(2,1);
LCD_Print("Press *");
ch=keypadfunc();

}while(ch=='*');



  }

void usart_initialize()
{
 UCSRB=0x18; // Rx Enable
 UCSRC=0x86; // Data Size : 8-bit, Stop Bit:1,No parity
 UBRRL=0x33; // X= (Fosc/(16(Desired Baud Rate)))-1
            //     =(8*10^6/(16 *9600))-1
            //     =52.08-1
            //     =51 (Dec)
          //Here, URSEl=0, so Fosc is divided by 16 if it was 1 Fosc would
            //Have been diveded by 8

}

void main()
{
     unsigned char choice='0';
 DDRA=0xF0;  // For D3-D0
 DDRD.B5=1;  //For RS
 DDRD.B6=1;  //For Enable
 DDRD.B3=1;
 DDRD.B0=0;
 PORTD.B3=0;
 rollno_key[6]='\0';


 LCD_Initialize(); //Initialize

  usart_initialize();
  while(1)
  {
  X: LCD_Initialize(); //Initialize
   LCD_Print("1.Enter room");
   Cursor_Position(2,1);
   LCD_Print("2.Add cards");
   choice=keypadfunc();


   if(choice!='0')
   {
   clear();
   LCD_Data(choice);
   delay_ms(500);
   }

   if(choice=='1')
   {
   Clear();
   LCD_Print("Place card");
   rfidadd=0;
   Y:for(i=0;i<12;i++)
                  {
                          while(UCSRA.B7==0); // Wait till Data is received
                          RFID_No[i]=UDR;
                  }
                  for(i=0;i<12;i++)
                  rfid[i]=RFID_No[i];
                  rfid[12]='\0';
                  if(checkValidInput())
                  {
                                 flag=0;
                           for(i=0;i<12;i++)
                           {
                                            if(rfid[i]==masterrfid[i])
                                            flag++;
                           }
                           if(flag==12)
                           {
                           Cursor_Position(2,1);
                           LCD_Print("Valid");
                           delay_ms(1000);
                           PORTD.B3=1;
                           delay_ms(5000);
                           PORTD.B3=0;
                           goto X;
                            }
                           for(j=0;j<6;j++)
                           {
                           LCD_Initialize();
                                 flag=0;
                                           for(i=0;i<12;i++)
                                           {

                                            if(rfid[i]==eep_read(rfidadd))//reads each rfid and compares with detected rfid
                                            flag++;

                                            rfidadd++;       //counter to increment address in EEPROM where rfids are stored.
                                            }
                                            rolladd=rfidadd;
                                             if(flag==12)
                                             break;
                                            for(i=0;i<6;i++)
                                            {
                                              rolladd++;         //counter to increment address in EEPROM where rollnos are stored.
                                             }
                                             rfidadd=rolladd;

                            }

                            if(flag!=12)
                            {
                            Cursor_Position(2,1);
                            LCD_Print("Invalid");
                            delay_ms(2000);
                            goto X;

                            }
                            clear();
                            LCD_Print("Valid");
                               delay_ms(1000);
                           PORTD.B3=1;
                            Cursor_Position(2,1);
                            for(i=0;i<6;i++)
                            {
                                            LCD_data(eep_read(rolladd));
                                            rolladd++;
                            }

                           delay_ms(5000);
                        
                           PORTD.B3=0;

                     }
                     else
                     {
                      LCD_Print("Place again");
                      delay_ms(2000);
                      goto Y;
                      }

       }
       if(choice=='2')
       {
          clear();
         enterID();  //Function to add more cards
        }
        }
}