// log base 2, 10, etc
// Inline version by Jose Gama 2015
// Original Assembly by
// Daniel Joseph Dorey (retroDan) 2015
// AVR ASM Introduction
// https://sites.google.com/site/avrasmintro/

void logBase2bits8(uint8_t *intResult, uint8_t *fracResult, uint8_t num8bit)
{
__asm__ __volatile__ (
//LOG BASE 2 OF A SINGLE-BYTE NUMBER
"         LDI  r20,7 \n\t" /* Initial log2 Value  */ \
"LOOPb2b8:   LSL %A2 \n\t" /*Shift Left until a one falls out*/ \
"         BRCS ENDb2b8 \n\t" \
"SKIPb2b8:   DEC r20 \n\t" \
"         BRNE LOOPb2b8 \n\t" \
"ENDb2b8:   MOV %A0,r20 \n\t" /*Store the Integer Part of Answer */ \
"        MOV %A1,%A2 \n\t" /*Store Fractional Part*/ \
: "+a" (*intResult), "+a" (*fracResult) \
: "a" (num8bit) \
: "r20" \
);
}

void logBase2bits16(uint8_t *intResult, uint8_t *fracResult, uint16_t num16bit)
{
__asm__ __volatile__ (
//LOG BASE TWO OF A SIXTEEN-BIT NUMBER
"        LDI  r20,15 \n\t" /*Initial log2 Value */ \
"LOOPb2b16:   LSL %A2 \n\t" /*Shift Left until a one falls out*/ \
"        ROL %B2 \n\t" \
"         BRCS ENDb2b16 \n\t" \
"SKIPb2b16:   DEC r20 \n\t" \
"         BRNE LOOPb2b16 \n\t" \
"ENDb2b16:   MOV %A0,r20 \n\t" /*Store the Integer Part of Answer */ \
"        MOV %A1,%B2 \n\t" /*Store Fractional Part*/ \
: "+a" (*intResult), "+a" (*fracResult) \
: "a" (num16bit) \
: "r20" \
);
}

uint16_t mult8ByE(uint8_t num8bit)
{//MULTIPLYING A SINGLE-BYTE NUMBER BY e
uint16_t intResult=0;
__asm__ __volatile__ (
"        LDI r18,87 \n\t" /*Load Est of e = 87/32*/ \
"        MUL %A1,r18 \n\t" \
"        LDI r20,5 \n\t" /*32 = 2^5*/ \
"LOOPm8e:   LSR r1 \n\t" /*Divide result by 32*/ \
"        ROR r0 \n\t" \
"        DEC r20 \n\t" \
"        BRNE LOOPm8e \n\t" \
"        MOVW %A0,r0 \n\t" /*Store Fractional Part*/ \
"        CLR r1 \n\t" \
: "=&a" (intResult) \
: "a" (num8bit) \
: "r18", "r20" \
);
return(intResult);
}

uint16_t mult16ByE(uint16_t num16bit)
{//MULTIPLYING A SIXTEEN-BIT NUMBER BY e ******** NOT OK YET
uint16_t intResult;
__asm__ __volatile__ (
"        LDI r18,0xBF \n\t" /*Load multiplier into BH:BL*/ \
"        LDI r19,0x15 \n\t" \
"        CLR r10 \n\t" /*Set Zero*/ \
"        MUL %B1,r19 \n\t" /*Multiply AH:AL by 5567*/ \
"        MOVW r22,r0 \n\t" \
"        MUL %A1,r18 \n\t" \
"        MOVW r20,r0 \n\t" \
"        MUL %B1,r18 \n\t" \
"        ADD r21,r0 \n\t" \
"        ADC r22,r1 \n\t" \
"        ADC r23,r10 \n\t" \
"        MUL r19,%A1 \n\t" \
"        ADD r21,r0 \n\t" \
"        ADC r22,r1 \n\t" \
"        ADC r23,r10 \n\t" \
"        LSR r22 \n\t" /*Ignore lower byte is division*/ \
"        ROR r21 \n\t" /*by 256 and 3x shift makes it 2048*/ \
"        LSR r22 \n\t" \
"        ROR r21 \n\t" \
"        LSR r22 \n\t" \
"        ROR r21 \n\t" \
"        MOV %A0,r21 \n\t" /*By ignoring the lower two bytes we get a division by 65536*/ \
"        MOV %B0,r22 \n\t" \
"        CLR r1 \n\t" \
: "=&r" (intResult) \
: "r" (num16bit) \
: "r10", "r18", "r19", "r20", "r21", "r22", "r23" \
);
return(intResult);
}

uint8_t mult8ByInvE(uint8_t num8bit)
{//MULTIPLYING A SINGLE-BYTE NUMBER BY 1/e
uint8_t intResult;
__asm__ __volatile__ (
"        LDI r20,47 \n\t" /*Load Est of e = 47/128*/ \
"        MUL %A1,r20 \n\t" /*Multiply Original Value by 47*/ \
"        LSR r1 \n\t" /*          ;Divide by 2*/ \
"        ROR r0 \n\t" /*          ;Shift Carry Flag to R0*/ \
"        LSR r1 \n\t" /*          ;Divide by 4 (2x2)*/ \
"        ROR r0 \n\t" /*          ;Shift Carry Flag into R0*/ \
"        LSR r1 \n\t" /*          ;Divide by 8 (2x2x2)*/ \
"        ROR r0 \n\t" /*          ;Shift Carry Flag into R0*/ \
"        LSR r1 \n\t" /*          ;Divide by 16 */ \
"        ROR r0 \n\t" /*          ;Shift Carry Flag into R0*/ \
"        LSR r1 \n\t" /*          ;Divide by 32 */ \
"        ROR r0 \n\t" /*          ;Shift Carry Flag into R0*/ \
"        LSR r1 \n\t" /*          ;Divide by 64 */ \
"        ROR r0 \n\t" /*          ;Shift Carry Flag into R0*/ \
"        LSR r1 \n\t" /*          ;Divide by 128 */ \
"        ROR r0 \n\t" /*          ;Shift Carry Flag into R0*/ \
"        MOV %A0,r0 \n\t" /*Store Answer*/ \
"        CLR r1 \n\t" \
: "=&a" (intResult) \
: "a" (num8bit) \
: "r20" \
);
   return(intResult);
}

uint16_t mult16ByInvE(uint16_t num16bit)
{//MULTIPLYING A SIXTEEN-BIT NUMBER BY 1/e
uint16_t intResult;
__asm__ __volatile__ (
"        LDI r18,0x2D \n\t" /*Load multiplier into BH:BL*/ \
"        LDI r19,0x5E \n\t" \
"        CLR r10 \n\t" /*Set Zero*/ \
"        MUL %B1,r19 \n\t" /*Multiply Original Value by 24109*/ \
"        MOVW r22,r0 \n\t" \
"        MUL %A1,r18 \n\t" \
"        MOVW r20,r0 \n\t" \
"        MUL %B1,r18 \n\t" \
"        ADD r21,r0 \n\t" \
"        ADC r22,r1 \n\t" \
"        ADC r23,r10 \n\t" \
"        MUL r19,%A1 \n\t" \
"        ADD r21,r0 \n\t" \
"        ADC r22,r1 \n\t" \
"        ADC r23,r10 \n\t" \
"        MOV %A0,r22 \n\t" /*Store Answer*/ \
"        MOV %B0,r23 \n\t" /*By ignoring the lower two bytes we get a division by 65536*/ \
"        CLR r1 \n\t" \
: "=&r" (intResult) \
: "r" (num16bit) \
: "r10", "r18", "r19", "r20", "r21", "r22", "r23" \
);
return(intResult);
}

void logEbits8(uint8_t *intResult, uint8_t *fracResult, uint8_t num8bit)
{//NATURAL LOGARITHM OF A SINGLE-BYTE NUMBER
__asm__ __volatile__ (
"        LDI  r20,7 \n\t" /*Initial log2 Value */ \
"LOOPLN8:   LSL %A2 \n\t" /*Shift Left until a one falls out*/ \
"         BRCS ENDLN8 \n\t" \
"SKIPLN8:   DEC r20 \n\t" \
"         BRNE LOOPLN8 \n\t" \
"ENDLN8:   MOV %A0,r20 \n\t" /*Store the Integer Part of Answer*/ \
"        MOV %A1,%A2 \n\t" /*Store Fractional Part*/ \
"        LDI %A2,177 \n\t" /*Multiply by 177 then*/ \
"        MUL %A1,%A2 \n\t" /*divide by 256 by ignoring*/ \
"        MOV %A1,r1 \n\t" /*lowest byte of the result*/ \
"        MUL %A0,%A2 \n\t" \
"        CLR %A0 \n\t" \
"        ADD %A1,r0 \n\t" \
"        ADC %A0,r1 \n\t" \
"        CLR r1 \n\t" \
: "+a" (*intResult), "+a" (*fracResult) \
: "a" (num8bit) \
: "r20" \
);
}

void logNbits16(uint8_t *intResult, uint8_t *fracResult, uint16_t num16bit)
{//NATURAL LOGARITHM OF A SIXTEEN-BIT NUMBER
__asm__ __volatile__ (
"        LDI  r20,15 \n\t" /*Initial log2 Value */ \
"LOOPLN16:   LSL %A2 \n\t" /*Shift Left until a one falls out*/ \
"        ROL %B2 \n\t" \
"         BRCS ENDLN16 \n\t" \
"SKIPLN16:   DEC r20 \n\t" \
"         BRNE LOOPLN16 \n\t" \
"ENDLN16:   MOV %A0,r20 \n\t" /*Store the Integer Part of Answer */ \
"        MOV %A1,r17 \n\t" /*Store Fractional Part*/ \
"        LDI %A2,0x72 \n\t" /*Multiply by 45426*/ \
"        LDI r17,0xB1 \n\t" /*Then divide by 65536 by ignoring the lowest two bytes*/ \
"        CLR r10 \n\t" \
"        MUL %A0,r17 \n\t" \
"        MOVW r6,r0 \n\t" \
"        MUL %A1,%A2 \n\t" \
"        MOVW r4,r0 \n\t" \
"        MUL %A0,%A2 \n\t" \
"        ADD r5,r0 \n\t" \
"        ADC r6,r1 \n\t" \
"        ADC r7,r10 \n\t" \
"        MUL %A1,r17 \n\t" \
"        ADD r5,r0 \n\t" \
"        ADC r6,r1 \n\t" \
"        ADC r7,r10 \n\t" \
"        MOV %A0,r7 \n\t" /*Store Answer*/ \
"        MOV %A1,r6 \n\t" /*Store Answer*/ \
"        CLR r1 \n\t" \
: "+r" (*intResult), "+r" (*fracResult) \
: "r" (num16bit) \
: "r4", "r5", "r6", "r7", "r10", "r16", "r17", "r20" \
);
}

void logBase10bits8(uint8_t *intResult, uint8_t *fracResult, uint8_t num8bit)
{//LOG BASE 10 OF A SINGLE-BYTE NUMBER
__asm__ __volatile__ (
"        LDI  r20,7 \n\t" /*Initial log2 Value */ \
"LOOPL108:   LSL %A2 \n\t" /*Shift Left until a one falls out*/ \
"         BRCS ENDL108 \n\t" \
"SKIPL108:   DEC r20 \n\t" \
"         BRNE LOOPL108 \n\t" \
"ENDL108:   MOV %A0,r20 \n\t" /*Store the Integer Part of Answer*/ \
"        MOV %A1,%A2 \n\t" /*Store Fractional Part*/ \
"        LDI %A2,77 \n\t" /*Multiply by 77 then*/ \
"        MUL %A1,%A2 \n\t" /*divide by 256 by ignoring*/ \
"        MOV %A1,r1 \n\t" /*lowest byte of the result*/ \
"        MUL %A0,%A2 \n\t" \
"        CLR %A0 \n\t" \
"        ADD %A1,r0 \n\t" \
"        ADC %A0,r1 \n\t" \
"        CLR r1 \n\t" \
: "+a" (*intResult), "+a" (*fracResult) \
: "a" (num8bit) \
: "r20" \
);
}

void logBase10bits16(uint8_t *intResult, uint8_t *fracResult, uint16_t num16bit)
{//LOG BASE 10 OF A SIXTEEN-BIT NUMBER
__asm__ __volatile__ (
"        LDI  r20,15 \n\t" /*Initial log2 Value */ \
"LOOPL1016:   LSL %A2 \n\t" /*Shift Left until a one falls out*/ \
"        ROL %B2 \n\t" \
"         BRCS ENDL1016 \n\t" \
"SKIPL1016:   DEC r20 \n\t" \
"         BRNE LOOPL1016 \n\t" \
"ENDL1016:   MOV %A0,r20 \n\t" /*Store the Integer Part of Answer */ \
"        MOV %A1,%B2 \n\t" /*Store Fractional Part*/ \
"        LDI %A2,0x10 \n\t" /*Multiply by 19728*/ \
"        LDI %B2,0x4D \n\t" /*Then divide by 65536 by ignoring the two lowest bytes*/ \
"        CLR r10 \n\t" \
"        MUL %A0,%B2 \n\t" \
"        MOVW r6,r0 \n\t" \
"        MUL %A1,%A2 \n\t" \
"        MOVW r4,r0 \n\t" \
"        MUL %A0,%A2 \n\t" \
"        ADD r5,r0 \n\t" \
"        ADC r6,r1 \n\t" \
"        ADC r7,r10 \n\t" \
"        MUL %A1,%B2 \n\t" \
"        ADD r5,r0 \n\t" \
"        ADC r6,r1 \n\t" \
"        ADC r7,r10 \n\t" \
"        MOV %A0,r7 \n\t" /*Store Answer*/ \
"        MOV %A1,r6 \n\t" /*Store Answer*/ \
"        CLR r1 \n\t" \
: "+r" (*intResult), "+r" (*fracResult) \
: "r" (num16bit) \
: "r4", "r5", "r6", "r7", "r10", "r16", "r17", "r20"  \
);
}

