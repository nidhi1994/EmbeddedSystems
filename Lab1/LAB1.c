void main() {
 while (1)
 {
DDRD = 0xAA;       //here at 1,3,5,7 LEDs need to glow so they need to be assigned 1 which is 10101010
 PORTD= 0xAA;      //Here output has to be written at PORTA in pins 1,3,5,7.
 }

}