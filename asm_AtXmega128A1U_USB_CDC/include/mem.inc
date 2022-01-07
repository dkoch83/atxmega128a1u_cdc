;/*
;* mem.inc
;*
;*  Created: 07.10.2014 19:14:15
;*   Author: Dominik
;*/ 

.ifndef mem_include
.set mem_include = 1

MSET: ; XH:XL = POINTER , R16 = VALUE, R17 = SIZE
PUSH XH
PUSH XL
PUSH R16
PUSH R17
	MSET_LOOP:
		ST X+, R16
		DEC R17
	BRNE MSET_LOOP
POP R17
POP R16
POP XL
POP XH
RET

MCOPY: ; XH:XL = FROM; YH:YL = TO; R16 = FROM START; R17 = COUNT
PUSH XH
PUSH XL
PUSH YH
PUSH YL
PUSH R0
PUSH R1
PUSH R18
	CLR R0
	MOV R1, R17
	ADD XL, R16
	ADC XH, R0
	MCOPY_LOOP:
		LD R18, X+
		ST Y+, R18
		DEC R1
	BRNE MCOPY_LOOP
POP R18
POP R1	
POP R0
POP YL
POP YH
POP XL
POP XH
RET

CP_BITS: ; XH:XL = FROM, YH:YL = TO, R16 = FROM_BIT_POS_msb, R17 = TO_BIT_POS_lsb, R18 = FROM_SIZE_IN_BYTES, R19 = TO_SIZE_IN_BYTES
PUSH XH
PUSH XL
PUSH YH
PUSH YL
PUSH R16
PUSH R17
PUSH R18
PUSH R19
PUSH R20
PUSH R21
PUSH R0
PUSH R1
PUSH R3
PUSH R4

	CP_BITS_LOOP:	
		CLR R20

		PUSH XH
		PUSH XL
		PUSH YH
		PUSH YL
		PUSH R16
		PUSH R17
		PUSH R18
		PUSH R19

			LDI R17, 8
			CALL UDIV8 ; R16 = Dividend, R17 = Divisor
	
			SUB R18, R0
			DEC R18

			ADD XL, R18
			ADC XH, R20
			LD R21, X
			
			ADD YL, R19
			ADC YH, R20

			LDI R20, 1
			INC R1
			CP_BITS_SHIFT1:
				ROR R21

				BRCS CP_BITS_SET_T1
				BRCC CP_BITS_CLR_T1

				RJMP CP_BITS_SET_T1_END
				CP_BITS_SET_T1:
					SET
				CP_BITS_SET_T1_END:

				RJMP CP_BITS_CLR_T1_END
				CP_BITS_CLR_T1:
					CLT
				CP_BITS_CLR_T1_END:

				DEC R1
			BRNE CP_BITS_SHIFT1
;----------------------------------------------------
			CP_BITS_SHIFT2:
				BRTS CP_BITS_SET_C2
				BRTC CP_BITS_CLR_C2

				RJMP CP_BITS_SET_C2_END
				CP_BITS_SET_C2:
					SEC
				CP_BITS_SET_C2_END:

				RJMP CP_BITS_CLR_C2_END
				CP_BITS_CLR_C2:
					CLC
				CP_BITS_CLR_C2_END:

				LD R21, -Y
				ROL R21
				ST Y, R21

				BRCS CP_BITS_SET_T2
				BRCC CP_BITS_CLR_T2

				RJMP CP_BITS_SET_T2_END
				CP_BITS_SET_T2:
					SET
				CP_BITS_SET_T2_END:

				RJMP CP_BITS_CLR_T2_END
				CP_BITS_CLR_T2:
					CLT
				CP_BITS_CLR_T2_END:

				DEC R19
			BRNE CP_BITS_SHIFT2
		POP R19
		POP R18
		POP R17
		POP R16
		POP YL
		POP YH
		POP XL
		POP XH

		DEC R16
		CP R16, R17
	BRGE CP_BITS_LOOP
POP R3
POP R2
POP R1
POP R0
POP R21
POP R20
POP R19
POP R18
POP R17
POP R16
POP YL
POP YH
POP XL
POP XH
RET

.endif