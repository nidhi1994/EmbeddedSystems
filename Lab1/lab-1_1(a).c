void main() {
   DDRA= 0x0F;    //It gives direction to registerA whether it is input or output.Here we have to turn on LEDs at pins 3-0 which are LSBs as its output operation so we will
                  // assign them 1.We assign zero for input but here their is no input so it does not matter if 1 or 0 is assignd to pins 4-7.
   PORTA = 0x0F;   //As pins 3-0 are output so output is written in portA register where 3-0 need to be assigned 1.
}