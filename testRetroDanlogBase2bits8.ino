// test code for logBase10bits8
// Inline version by Jose Gama 2015
// Original Assembly by
// Daniel Joseph Dorey (retroDan) 2015
// AVR ASM Introduction
// https://sites.google.com/site/avrasmintro/

#include <Arduino.h>
#include "logarithm.h"
#include <math.h>
void setup()
 {
 Serial.begin(9600);
 Serial.println("Start");
 }

void loop()
 {
 
uint8_t i, a, b,r;
 for (i=0;i<255;i++) 
 {
// the result is value +1
   logBase2bits8(&a,&r,i);
   b = log10((float)i) * 3.32;
  if (a != b)
  {
   Serial.print(i);Serial.print(" log2 ");Serial.print(" = ");
   Serial.print(b);Serial.print("   ");Serial.print(a);Serial.print(".");Serial.println(r);
  }
 }
 Serial.println("Done");
 
 
 }
