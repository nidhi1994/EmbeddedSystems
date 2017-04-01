#include<string.h>

void usart_initialize()
{
 UCSRB=0x18; // Rx & Tx Enable
 UCSRC=0x86; // Data Size : 8-bit, Stop Bit:1,No parity
 UBRRL=0x33; // X= (Fosc/(16(Desired Baud Rate)))-1
            //     =(8*10^6/(16 *9600))-1
            //     =52.08-1
            //     =51 (Dec)
          //Here, URSEl=0, so Fosc is divided by 16 if it was 1 Fosc would
            //Have been diveded by 8

}


//USART Send
void usart_send(unsigned char ch)
{
  while(UCSRA.B5==0); // Wait till UDR is empty
 UDR=ch; //Write the value to be Tx
}


void main()
{
 unsigned char x;
 unsigned char str1[]="Welcome to ESD LAB!";
 int str_len1=19;
 unsigned char str2[]="Incorrect";
 int str_len2=9;
 int i=0;
 int cnt=0;
 int res=2;
 unsigned char pass[]="HELLO";
 unsigned char enter[10];
 DDRA=0xFF;
 PORTA=0x00;
 usart_initialize();
  while(1)
 {
  while(x!='\0');
   {while(UCSRA.B7==0); // Wait till Data is received
   {enter[cnt]=UDR;// Send the received data to PORTA
    CNT++;}
    res=strcmp(enter,pass);
    if(res==0)
    {
      while(1){
       usart_send(str1[i++]);  //Send data
     if (i>=str_len1)  // Till string Length
     {i=0;
     delay_ms(1000);
      }
   } }
       else
        while(1){
       usart_send(str2[i++]);  //Send data
     if (i>=str_len2)  // Till string Length
     {i=0;
    // delay_ms(1000);  
    }}
}
}
}

