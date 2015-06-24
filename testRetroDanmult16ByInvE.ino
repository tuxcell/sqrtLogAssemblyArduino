// test code for logBase10bits8
// Inline version by Jose Gama 2015
// Original Assembly by
// Daniel Joseph Dorey (retroDan) 2015
// AVR ASM Introduction
// https://sites.google.com/site/avrasmintro/

#include <Arduino.h>
#include "logarithm.h"

void setup()
 {
 Serial.begin(9600);
 Serial.println("Start");
 }

void loop()
 {
 
uint16_t i, a, b;
 for (i=0;i<65535;i++) 
 {
// the result for some numbers is value+1
   a = mult16ByInvE(i);
   b = i/2.7172;
  if (a != b)
  {
   Serial.print(i);Serial.print(" /e ");Serial.print(" = ");
   Serial.print(b);Serial.print("   ");Serial.println(a);
  }
 }
 Serial.println("Done");
 
 
 }
