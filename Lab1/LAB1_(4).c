void main() {
               unsigned char p[8]={0x00,0x01,0x02,0x03,0x04,0x05,0x06,0x07}; //decalring global arrays of size 9 to blink upto 9
               unsigned char i;          // loop counter
               DDRA=0x07;                 // 00000111 last three bits are set as output
               PORTA=0x87;                //10000111     //As first bit is input so pull-up is applied
               while(1)
               {
               if(PINA.B7==0)                   //Checking if input is given that is whether switch is ON.
               {

                                    for(i=0;i<8;i++)
                                    {
                                     PORTA=p[i];                        //output at portA to on all leds consecutively
                                     delay_ms(1000);                     // delay of 1 second
                                     }


               }
               PORTA=0x00;                           // keep all LEDS off ,if switch is turned OFF.
               }
}