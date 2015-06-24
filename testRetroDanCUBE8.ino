// test code for logBase10bits8
// Inline version by Jose Gama 2015
// Original Assembly by
// Daniel Joseph Dorey (retroDan) 2015
// AVR ASM Introduction
// https://sites.google.com/site/avrasmintro/

#include <Arduino.h>
#include "sqrt.h"
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
// the result is NOT ALWAYS exactly the same
   cube8(&a,&r,i);
   b = cbrt((double)i);
  if (a != b)
  {
   Serial.print(i);Serial.print(" cbrt ");Serial.print(" = ");
   Serial.print(b);Serial.print("   ");Serial.println(a);
  }
 }
 Serial.println("Done");
 
 
 }
