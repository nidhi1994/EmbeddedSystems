void main() {
DDRA=0x2B;       //here we have to blink LEDs at 0,1,3,5 so they are assigned 1.
do
{
 PORTA=0x2B;   //First output is written in PORTA so LEDs turn ON.
 Delay_ms(1000);//Here is delay of 1s so LED stay ON for 1s.
 PORTA=0x00;    //Again output is written in PORTA and as it is 0 so pins are in tri-state and LEDs turn OFF.
  Delay_ms(1000);//Here is delay of 1s so LED stay OFF for 1s.
} while(1);   //Loop is complete and is repeated again and so on.
}