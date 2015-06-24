# sqrtLogAssemblyArduino
square root, cube root and logarithm fixed-point algorithms in Assembly 

Inline version by Jose Gama 2015
Original Assembly by Daniel Joseph Dorey (retroDan)

sqrt8 Square root, input uint8_t, output uint8_t
sqrt16 Square root, input uint16_t, output (result, remainder) uint16_t
sqrt32 Square root, input uint32_t, output (result, remainder) uint16_t
cube8 cube root, input uint8_t, output (result, remainder) uint8_t
cube16 cube root, input uint16_t, output (result, remainder) uint16_t

logBase2bits8 logarithm base 2, input uint8_t, output (integer result, fractional result) uint8_t
logBase2bits16 logarithm base 2, input uint16_t, output (integer result, fractional result) uint16_t

mult8ByE multiply by e, input uint8_t, output uint8_t
mult16ByE multiply by e (not finished yet), input uint16_t, output uint16_t
mult8ByInvE multiply by 1/e, input uint8_t, output uint8_t
mult16ByInvE multiply by 1/e, input uint16_t, output uint16_t
logEbits8 natural logarithm, input uint8_t, output (integer result, fractional result) uint8_t
logNbits16 natural logarithm, input uint16_t, output (integer result, fractional result) uint16_t
logBase10bits8 logarithm base 10, input uint8_t, output (integer result, fractional result) uint8_t
logBase10bits16 logarithm base 10, input uint16_t, output (integer result, fractional result) uint16_t


Reference:

Daniel Joseph Dorey (retroDan), 2015
AVR ASM Introduction
https://sites.google.com/site/avrasmintro/
