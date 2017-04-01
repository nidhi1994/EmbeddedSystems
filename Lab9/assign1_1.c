//Tx data to PC
void usart_initialize()
{
 UCSRB=0x08; //Tx Enable
UCSRC=0x86; // Data Size : 8-bit, Stop Bit:1,No parity
 UBRRL=0x33; // X= (Fosc/(16(Desired Baud Rate)))-1
            //     =(8*10^6/(16 *9600))-1
            //     =52.08-1
            //     =51 (Dec)
          //Here, URSEl=0, so Fosc is divided by 16 if it was 1                     //Fosc would Have been divided by 8
}


//USART Send
void usart_send(unsigned char ch)
{
  while(UCSRA.B5==0); // Wait till UDR is empty
 UDR=ch; //Write the value to be Tx
}

void main()
{
 unsigned char str[]="Hello World";
 int str_len=12;
 int i=0;
 usart_initialize();

 while(1)
 {
  usart_send(str[i++]);  //Send data
  if (i>=str_len)  // Till string Length
    {i=0;
    delay_ms(1000);
  }
    }
}