// square root and cube root
// Inline version by Jose Gama 2015
// Original Assembly by
// Daniel Joseph Dorey (retroDan) 2015
// AVR ASM Introduction
// https://sites.google.com/site/avrasmintro/

//SQUARE-ROOT OF A SINGLE-BYTE NUMBER
uint8_t sqrt8(uint8_t num8bit)
{
uint8_t result;
__asm__ __volatile__ (
"	clr	%A0 \n\t" /*clear result */ \
"	clr	r18\n\t" /*clear temp */ \
"LOOP8:  SUB %A1,r18 \n\t" /*Subtract B from Square*/ \
"   BRCS DONE8 \n\t" /*If bigger than square we are done*/ \
"  INC %A0 \n\t" /*Increment the answer*/ \
"  SUBI r18,-2 \n\t" /*Increment B by two*/ \
"   RJMP LOOP8 \n\t" \
"DONE8: DEC %A0 \n\t" \
: "=&a" (result) \
: "a" (num8bit) \
: "r18" \
);
return result;
}

//SQUARE-ROOT OF A 16-BIT NUMBER
void sqrt16(uint16_t *result, uint16_t *remainder, uint16_t num16bit)
{
__asm__ __volatile__ (
"        CLR   %A1 \n\t" /*Initialize Remainder to zero */ \
"        CLR   %B1 \n\t" \
"        CLR   %A0 \n\t" /*Initialize Root to zero */ \
"        CLR   %B0 \n\t" \
"        LDI   r20,8 \n\t" /*Set Loop Counter to eight */ \
"LOOP16:  \n\t" \
"        LSL   %A0 \n\t" /*Multiply Root by two */ \
"        ROL   %B0 \n\t" \
"        LSL   %A2 \n\t" /*Shift two high-bits of Square */ \
"        ROL   %B2 \n\t" /*into Remainder*/ \
"        ROL   %A1 \n\t" \
"        ROL   %B1 \n\t" \
"        LSL   %A2 \n\t" /*Shift second high bit of Sqaure*/ \
"        ROL   %B2 \n\t" /*into Remainder*/ \
"        ROL   %A1 \n\t" \
"        ROL   %B1 \n\t" \
"        CP    %A0,%A1 \n\t" /*Compare Root to Remainder */ \
"        CPC   %B0,%B1 \n\t" /*        */ \
"        BRCC SKIP16 \n\t" /*If Remainder less or equal than Root*/ \
"        INC   %A0 \n\t" /*Increment Root */ \
"        SUB   %A1,%A0 \n\t" /*Subtract Root from Remainder */ \
"        SBC   %B1,%B0 \n\t" \
"        INC   %A0 \n\t" /*Increment Root */ \
"SKIP16:  \n\t" \
"        DEC   r20 \n\t" /*Decrement Loop Counter */ \
"        BRNE LOOP16 \n\t" /*Check if all bits processed */ \
"        LSR   %B0 \n\t" /*Divide Root by two */ \
"        ROR   %A0 \n\t" \
: "+a" (*result), "+a" (*remainder) \
: "a" (num16bit) \
: "r20" \
);
}

//SQUARE-ROOT OF A 32-BIT NUMBER
void sqrt32(uint32_t *result, uint32_t *remainder, uint32_t num32bit)
{
__asm__ __volatile__ (
"        CLR   %A1 \n\t" /*Initialize Remainder to zero */ \
"        CLR   %B1 \n\t" \
"        CLR   %C1 \n\t" \
"        CLR   %D1 \n\t" \
"        CLR   %A0 \n\t" /*Initialize Root to zero */ \
"        CLR   %B0 \n\t" \
"        CLR   %C0 \n\t" \
"        CLR   %D0 \n\t" \
"        LDI   r20,16 \n\t" /*Set Loop Counter to sixteen */ \
"LOOP32:        LSL   %A0 \n\t" /*Multiply Root by two */ \
"        ROL   %B0 \n\t" \
"        ROL   %C0 \n\t" \
"        ROL   %D0 \n\t" \
"        LSL   %A2 \n\t" /*Shift two high-bits of Square */ \
"        ROL   %B2 \n\t" /*into Remainder*/ \
"        ROL   %C2 \n\t" \
"        ROL   %D2 \n\t" \
"        ROL   %A1 \n\t" \
"        ROL   %B1 \n\t" \
"        ROL   %C1 \n\t" \
"        ROL   %C1 \n\t" \
"        LSL   %A2 \n\t" /*Shift second high bit of Square*/ \
"        ROL   %B2 \n\t" /*into Remainder*/ \
"        ROL   %C2 \n\t" \
"        ROL   %D2 \n\t" \
"        ROL   %A1 \n\t" \
"        ROL   %B1 \n\t" \
"        ROL   %C1 \n\t" \
"        ROL   %D1 \n\t" \
"        CP    %A0,%A1 \n\t" /*Compare Root to Remainder */ \
"        CPC   %B0,%B1 \n\t" \
"        CPC   %C0,%C1 \n\t" \
"        CPC   %D0,%D1 \n\t" \
"         BRCC SKIP32 \n\t" /*If Remainder less or equal than Root*/ \
"        INC   %A0 \n\t" /*Increment Root */ \
"        SUB   %A1,%A0 \n\t" /*Subtract Root from Remainder */ \
"        SBC   %B1,%B0 \n\t" \
"        SBC   %C1,%C0 \n\t" \
"        SBC   %D1,%D0 \n\t" \
"        INC   %A0 \n\t" /*Increment Root */ \
"SKIP32:        DEC   r20 \n\t" /*Decrement Loop Counter */ \
"         BRNE LOOP32 \n\t" /*Check if all bits processed */ \
"        LSR   %D0 \n\t" /*Divide Root by two */ \
"        ROR   %C0 \n\t" \
"        ROR   %B0 \n\t" \
"        ROR   %A0 \n\t" \
: "+r" (*result), "+r" (*remainder) \
: "a" (num32bit) \
: "r20" \
);
}

//CUBE ROOT OF A SINGLE-BYTE NUMBER
void cube8(uint8_t *result, uint8_t *remainder, uint8_t num8bit)
{
__asm__ __volatile__ (
"        CLR r20 \n\t" /*Start Loop Counter at Zero*/ \
"LOOPCB8: MUL r20,r20 \n\t" /*R0 = C^3*/ \
"        MUL r20,r0 \n\t" \
"        CP %A2,r0 \n\t" /*Check if gone too far*/ \
"        BRCS FINICB8 \n\t" /*If so then Finish*/ \
"        MOV %A1,%A2 \n\t" /*Calculate remainder*/ \
"        SUB %A1,r0 \n\t" \
"        INC r20 \n\t" /*Increment Loop Counter*/ \
"        CPI r20,7 \n\t" /*Check if Done*/ \
"        BRNE LOOPCB8 \n\t" /*Go back*/ \
"FINICB8: MOV %A0,r20 \n\t" /*answer = Counter - 1*/ \
"        DEC %A0 \n\t" \
: "+r" (*result), "+r" (*remainder) \
: "r" (num8bit) \
: "r20" \
);
}

//CUBE ROOT OF A 16-BIT NUMBER
void cube16(uint8_t *result, uint16_t *remainder, uint16_t num16bit)
{
__asm__ __volatile__ (
"        CLR %A1 \n\t" /*Clear Remainder*/ \
"        CLR %B1 \n\t" \
"        CLR r11 \n\t" /*Set One*/ \
"        INC r11 \n\t" \
"        CLR r12 \n\t" /*Start Low Estimate at Zero*/ \
"        LDI r18,42 \n\t" /*Start High Estimate at Forty-Two*/ \
"        MOV r13,r18 \n\t" \
"LOOPCB16:   MOV r14,r12 \n\t" /*AVG = (LowEst+HighEst+1)/2*/ \
"        ADD r14,r13 \n\t" \
"        ADC r14,r11 \n\t" \
"        LSR r14 \n\t" \
"        MOV r18,r14 \n\t" /*Calculate AVG^3*/ \
"        RCALL CUBECB16 \n\t" \
"        CP  r4,%A2 \n\t" /*Compare AVG^3 to Original CUBE*/ \
"        CPC r5,%B2 \n\t" \
"        CPC r6,__zero_reg__ \n\t" \
"        BRNE SKIP1CB16 \n\t" /*Check if AVG^3 = Original CUBE*/ \
"        MOV r12,r14 \n\t" /*AVG^3 = CUBE so Low-Est = AVG (Finished)*/ \
"        RJMP END2CB16 \n\t" \
"SKIP1CB16:   BRCC ISHIGHCB16 \n\t" \
"        MOV r12,r14 \n\t" /*AVG^3 < CUBE so Low-Est = AVG*/ \
"        RJMP SKIP2CB16 \n\t" \
"ISHIGHCB16: MOV r13,r14 \n\t" /*AVG^3 > CUBE so High-Est = AVG*/ \
"SKIP2CB16:  MOV r18,r13 \n\t" /*B = HighEst - LowEst*/ \
"        SUB r18,r12 \n\t" \
"        BREQ ENDCB16 \n\t" /*LowEst = HighEst so we are Finished*/ \
"        CPI r18,1 \n\t" \
"         BRNE LOOPCB16 \n\t" /*If HighEst-LowEst > 1 then try again*/ \
"ENDCB16:   MOV r18,r12 \n\t" /*Calculate Remainder*/ \
"        RCALL CUBECB16 \n\t" /*Remainder = Cube - LowEst^3*/ \
"        MOVW %A1,%A2 \n\t" \
"        SUB %A1,r4 \n\t" \
"        SBC %B1,r5 \n\t" \
"END2CB16:  MOV %A0,r12 \n\t" /*Store Result = LowEst*/ \
"    RJMP DONECB16 \n\t" \
"CUBECB16:    MUL r18,r18 \n\t" /*Calc B*B*/ \
"        MOVW r8, R0 \n\t" \
"        MUL r8,r18 \n\t" /*Calc B*B*B*/ \
"        MOVW r4, R0 \n\t" \
"        MUL r9,r18 \n\t" \
"        ADD r5,R0 \n\t" \
"        CLR r6 \n\t" \
"        ADC r6,R1 \n\t" \
"        RET \n\t" \
"DONECB16: \n\t" \
: "+r" (*result), "+r" (*remainder) \
: "r" (num16bit) \
: "r4", "r5", "r6", "r8", "r9", "r11", "r12", "r13", "r14" \
);
}