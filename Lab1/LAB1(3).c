void main() {
         DDRA =0x0F; //Here we give input at 4-7 and their respective output at 0-3 so for output we need to assign 1 and for input we need to assign 0.
         PORTA=0xF0;//Here we need to apply pull-up as input as port is configured to input
         while(1)
         {
              x=PINA;//Read contents of PORTA
              x=(~x>>4)|0xF0;         //as we need the compliment of actual input in order to turn ON respictive LED(s) so we have negated and we need to shift the bits as we see
                                      //at 0-3 pins for 4-7 inputs.We need to OR with 0x0F in order to configure the output port from 0-3.
              PORTA=x;                //Assigned variable x to configure the output port.
         }
}