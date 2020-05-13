#include <math.h> 

//shifting out pins
const int dataPin = 2;
const int latchPin = 3; 
const int clockPin = 4;

//shifting in pins
const int final_data = 5; // summation from the cirucit
const int latch = 6; // latch 1
const int clk = 7;
const int reset_fpga = 8;
const int fpga_start_signal = 10;

//shifting OUT pins final

const int datapin_o = 11;
const int latchpin_o = 12;
const int clockpin_o = 13;

void setup() {
  // put your setup code here, to run once:
  
  //shifting out pins
  pinMode(dataPin, OUTPUT);
  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  
  //shifting in pins
  pinMode(final_data, INPUT);
  pinMode(latch, OUTPUT);
  pinMode(reset_fpga, INPUT);
  pinMode(clk, OUTPUT);
  pinMode(fpga_start_signal, OUTPUT);

  //shifting out final pins
  pinMode(datapin_o, OUTPUT);
  pinMode(latchpin_o, OUTPUT);
  pinMode(clockpin_o, OUTPUT);

  //sending input
  Serial.begin(9600);

}

void loop() {
  // Input contains B3 B2 B1 B0 A3 A2 A1 A0 with no carry bit.
  byte testinput = B00000000; //lsb
  byte testinput1 = B00000000;
  byte testinput2 = B00000000;
  byte testinput3 = B00001000; //msb
  //shifting data serially to the circuit
  shifter(testinput);
  shifter(testinput1);
  shifter(testinput2);
  shifter(testinput3);
  digitalWrite(latchPin, HIGH); // update output

  //parallel shifting in arduino
  digitalWrite(clk, HIGH);
  digitalWrite(latch, LOW);
  digitalWrite(latch, HIGH);
  digitalWrite(fpga_start_signal, HIGH);
  byte output_1 = readdata();
  byte output_2 = readdata();
  output_2 = flipByte(output_2);
  output_1 = flipByte(output_1);
  int combined = output_2 << 8 | output_1;
//  Serial.println(combined,DEC);
//  int combined1 = abs(combined);
//  Serial.println(combined1, DEC);
//  digitalWrite(fpga_start_signal, LOW);
//  Serial.print(output_2, BIN);
//  Serial.print(output_1, DEC);

  //breaking the digits:
  byte ones = (combined)%10;
//  Serial.println(ones, DEC);
  byte tens = (combined/10)%10;
//  Serial.println(tens, DEC);
  byte hundred = (combined/100)%10;
  byte thousand = (combined/1000)%10;
//  Serial.print(thousand);
  byte tthousand = (combined/10000)%10;
//  Serial.print(tthousand, DEC);
  //converting to bcd
  byte s_one = sevensegmentencoder(ones);
//  Serial.print(s_one, BIN);
  byte s_ten = sevensegmentencoder(tens);
  byte s_hd = sevensegmentencoder(hundred);
  byte s_th = sevensegmentencoder(thousand);
  byte s_tth = sevensegmentencoder(tthousand);
//  Serial.print(s_tth, BIN);

  //shifting output data out serially
   shifter_out(s_tth);
    shifter_out(s_th);
      shifter_out(s_hd);
        shifter_out(s_ten);
    shifter_out(s_one);

  //SW sending
  Serial.println(combined);

 

  digitalWrite(latchpin_o, HIGH);

byte readdata(){
  // enabling parallel input for PISO

  byte output_data = shiftIn(final_data, clk, LSBFIRST); 
  return output_data;
}



void shifter(byte eightBits) {

  digitalWrite(latchPin, LOW);  // prepare shift register for data
  shiftOut(dataPin, clockPin, MSBFIRST, eightBits); // send data

}

void shifter_out(byte eightBits) {

  digitalWrite(latchpin_o, LOW);  // prepare shift register for data
  shiftOut(datapin_o, clockpin_o, MSBFIRST, eightBits); // send data

}

byte flipByte(byte c){
  char r=0;
  for(byte i = 0; i < 8; i++){
    r <<= 1;
    r |= c & 1;
    c >>= 1;
  }
  return r;
}

byte sevensegmentencoder(int someNumber) {
  switch (someNumber) {
    case 0:
      return B00000011;
      break;
    case 1:
      return B10011110;
      break;
    case 2:
      return B00100100 ;
      break;
    case 3:
      return B00001100 ;
      break;
    case 4:
      return B10011000 ;
      break;
    case 5:
      return B01001000 ;
      break;
    case 6:
      return B01000000;
      break;
    case 7:
      return B00011110;
      break;
    case 8:
      return B00000000 ;
      break;
    case 9:
      return B00001000 ;
      break;

  
    case -1:
      return B10011110;
      break;
    case -2:
      return B00100100 ;
      break;
    case -3:
      return B00001100 ;
      break;
    case -4:
      return B10011000 ;
      break;
    case -5:
      return B01001000 ;
      break;
    case -6:
      return B01000000;
      break;
    case -7:
      return B00011110;
      break;
    case -8:
      return B00000000 ;
      break;
    case -9:
      return B00001000 ;
      break;
    default:
      return B10010010; // Error condition, displays three vertical bars
      break;   
  }
}
