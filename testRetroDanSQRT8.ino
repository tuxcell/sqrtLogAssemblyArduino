// test code for logBase10bits8
// Inline version by Jose Gama 2015
// Original Assembly by
// Daniel Joseph Dorey (retroDan) 2015
// AVR ASM Introduction
// https://sites.google.com/site/avrasmintro/

#include <Arduino.h>
#include "sqrt.h"

void setup()
 {
 Serial.begin(9600);
 Serial.println("Start");
 }

void loop()
 {
 
uint8_t i, a, b;
 for (i=0;i<255;i++) 
 {
// the result is NOT ALWAYS exactly the same
   a = sqrt8(i);
b = sqrt(i);
  if (a != b)
  {
   Serial.print(i);Serial.print(" sqrt ");Serial.print(" = ");
   Serial.print(b);Serial.print("   ");Serial.println(a);
  }
 }
 Serial.println("Done");
 
 
 }
