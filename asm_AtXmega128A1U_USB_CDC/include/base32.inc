/*
 * BASE32_dec.inc
 *
 *  Created: 16.09.2014 20:42:08
 *   Author: Dominik
 */ 
  
; RFC 3548 
;               Table 3: The Base 32 Alphabet
;
;        Value Encoding  Value Encoding  Value Encoding  Value Encoding
;            0 A             9 J            18 S            27 3
;            1 B            10 K            19 T            28 4
;            2 C            11 L            20 U            29 5
;            3 D            12 M            21 V            30 6
;            4 E            13 N            22 W            31 7
;            5 F            14 O            23 X
;            6 G            15 P            24 Y         (pad) =
;            7 H            16 Q            25 Z
;            8 I            17 R            26 2  
;
.ifndef base32_include
.set base32_include = 1

.CSEG
BASE32_CODE: .DB "ABCDEFGHIJKLMNOPQRSTUVWXYZ234567"

; String Pointer = Pointer to a NULL Terminated String
;
; Size OUT BUFFER = ((STRLEN / 5) * 8) + 1 
BASE32_ENC_URL: ; XH:XL = String Pointer, YH:YL = OUT BUFFER
PUSH XH
PUSH XL
PUSH YH
PUSH YL
PUSH ZH
PUSH ZL
PUSH R21
PUSH R22
PUSH R23
PUSH R24
PUSH R25	
	
	LDI ZH, HIGH(BASE32_CODE)
	LDI ZL, LOW(BASE32_CODE)

	LDI R21, 8
	LDI R22, 5
	LDI R23, 0
	CLR R25

	BASE32_ENC_URL_LOOP1:

		CPI R21, 0x00
		BRNE BASE32_ENC_URL_PADCOUNT_RESET2
			LDI R21, 8
		BASE32_ENC_URL_PADCOUNT_RESET2:

		CPI R22, 0x00
		BRNE BASE32_ENC_URL_WRITEBYTE_END
				CLR R16
				MOV R17, R25
				RCALL PGM_READ_BYTE ;ZH:ZL = Pointer Address, R16:R17 = Byte Adress
				ST Y+, R0
				DEC R21
			LDI R22, 5
			CLR R25
		BASE32_ENC_URL_WRITEBYTE_END:

		CPI R23, 0x00
		BRNE BASE32_ENC_URL_READBYTE_END
		LD R24, X+
		CPI R24, 0x00
		BRNE BASE32_ENC_URL_STRNOEND
			
			CPI R22, 5
			BREQ BASE32_ENC_URL_NOLAST
			BASE32_ENC_URL_LAST:
				LSL R25
				DEC R22		
			BRNE BASE32_ENC_URL_LAST
				CLR R16
				MOV R17, R25
				RCALL PGM_READ_BYTE ;ZH:ZL = Pointer Address, R16:R17 = Byte Adress
				ST Y+, R0
		BASE32_ENC_URL_NOLAST:
				DEC R21
		RJMP BASE32_ENC_URL_END
		BASE32_ENC_URL_STRNOEND:
		LDI R23, 8
		BASE32_ENC_URL_READBYTE_END:

		; Schift
		LSL R24
		ROL R25

		DEC R23
		DEC R22
	RJMP BASE32_ENC_URL_LOOP1
	BASE32_ENC_URL_END:

	CPI R21, 0x00
	BRLO BASE32_ENC_URL_PADD_LOOP_END
	BREQ BASE32_ENC_URL_PADD_LOOP_END
	BRMI BASE32_ENC_URL_PADD_LOOP_END
	BASE32_ENC_URL_PADD_LOOP:
		LDI R24, '='
		ST Y+, R24
		DEC R21
	BRNE BASE32_ENC_URL_PADD_LOOP
	BASE32_ENC_URL_PADD_LOOP_END:
	LDI R24, 0x00
	ST Y+, R24

POP R25
POP R24
POP R23
POP R22
POP R21
POP ZL
POP ZH
POP YL
POP YH
POP XL
POP XH
RET

; From Buffer block size must be divisible by 4
;
; OUT BUFFER SIZE must ((BUFFER FROM SIZE / 5) * 8) + 1
;
BASE32_ENC_BLOCK: ; XH:XL = Pointer FROM BUFFER, YH:YL = Pointer OUT BUFFER, R16:R17 = BUFFER FROM SIZE
PUSH XH
PUSH XL
PUSH YH
PUSH YL
PUSH ZH
PUSH ZL
PUSH R16
PUSH R17
PUSH R20
PUSH R21
PUSH R22
PUSH R23
PUSH R24
PUSH R25	
	
	LDI R20, 0x00
	LDI R21, 0x01

	CLR R0
	CLR R1

	LDI ZH, HIGH(BASE32_CODE)
	LDI ZL, LOW(BASE32_CODE)

	LDI R22, 5
	LDI R23, 0
	CLR R25

	BASE32_ENC_BLOCK_LOOP1:
		CPI R22, 0x00
		BRNE BASE32_ENC_BLOCK_WRITEBYTE_END
			PUSH R16
			PUSH R17
			PUSH R0
			PUSH R1
				CLR R16
				MOV R17, R25
				RCALL PGM_READ_BYTE ;ZH:ZL = Pointer Address, R16:R17 = Byte Adress
				ST Y+, R0
			POP R1
			POP R0
			POP R17
			POP R16
			LDI R22, 5
			CLR R25
			ADD R1, R21
			ADC R0, R20
		BASE32_ENC_BLOCK_WRITEBYTE_END:

		CPI R23, 0x00
		BRNE BASE32_ENC_BLOCK_READBYTE_END
			LD R24, X+
			LDI R23, 8

			LDI R20, 0x00
			LDI R21, 0x01

			SUB R17, R21
			SBC R16, R20
			CP  R17, R20
			CPC R16, R20
			BREQ BASE32_ENC_BLOCK_END
		BASE32_ENC_BLOCK_READBYTE_END:

		; Schift
		LSL R24
		ROL R25

		DEC R23
		DEC R22
	RJMP BASE32_ENC_BLOCK_LOOP1
	BASE32_ENC_BLOCK_END:

POP R25
POP R24
POP R23
POP R22
POP R21
POP R20
POP R17
POP R16
POP ZL
POP ZH
POP YL
POP YH
POP XL
POP XH
RET

BASE32_ENC_LAST: ; XH:XL = Pointer FROM BUFFER, YH:YL = Pointer OUT BUFFER, R16:R17 = BUFFER FROM SIZE
PUSH XH
PUSH XL
PUSH YH
PUSH YL
PUSH ZH
PUSH ZL
PUSH R16
PUSH R17
PUSH R18
PUSH R19
PUSH R21
PUSH R22
PUSH R23
PUSH R24
PUSH R25	
	
	LDI ZH, HIGH(BASE32_CODE)
	LDI ZL, LOW(BASE32_CODE)

	LDI R18, 0
	LDI R19, 1

	LDI R21, 8
	LDI R22, 5
	LDI R23, 0
	CLR R25

	BASE32_ENC_LAST_LOOP1:
		CPI R22, 0x00
		BRNE BASE32_ENC_LAST_WRITEBYTE_END
			PUSH R16
			PUSH R17
				CLR R16
				MOV R17, R25
				RCALL PGM_READ_BYTE ;ZH:ZL = Pointer Address, R16:R17 = Byte Adress
				ST Y+, R0
				DEC R21
			POP R17
			POP R16
			LDI R22, 5
			CLR R25
		BASE32_ENC_LAST_WRITEBYTE_END:

		CPI R23, 0x00
		BRNE BASE32_ENC_LAST_READBYTE_END
		LD R24, X+

		SUB R17, R19
		SBC R16, R18
		CP R17, R18
		CPC R16, R18
		;CPI R24, 0x00
		BRNE BASE32_ENC_LAST_STRNOEND
			CPI R22, 5
			BREQ BASE32_ENC_LAST_URL_NOLAST

			BASE32_ENC_LAST_LAST:
				LSL R25
				DEC R22		
			BRNE BASE32_ENC_LAST_LAST
			PUSH R16
			PUSH R17
				CLR R16
				MOV R17, R25
				RCALL PGM_READ_BYTE ;ZH:ZL = Pointer Address, R16:R17 = Byte Adress
				ST Y+, R0	
			POP R17
			POP R16
			BASE32_ENC_LAST_URL_NOLAST:
			DEC R21
		RJMP BASE32_ENC_LAST_END
		BASE32_ENC_LAST_STRNOEND:
		LDI R23, 8
		BASE32_ENC_LAST_READBYTE_END:

		CPI R21, 0x00
		BRNE BASE32_ENC_LAST_PADCOUNT_RESET
			LDI R21, 8
		BASE32_ENC_LAST_PADCOUNT_RESET:

		; Schift
		LSL R24
		ROL R25

		DEC R23
		DEC R22
	RJMP BASE32_ENC_LAST_LOOP1
	BASE32_ENC_LAST_END:

	CPI R21, 0x00
	BRLO BASE32_ENC_LAST_PADD_LOOP_END
	BREQ BASE32_ENC_LAST_PADD_LOOP_END
	BRMI BASE32_ENC_LAST_PADD_LOOP_END
	BASE32_ENC_LAST_PADD_LOOP:
		LDI R24, '='
		ST Y+, R24
		DEC R21
	BRNE BASE32_ENC_LAST_PADD_LOOP
	BASE32_ENC_LAST_PADD_LOOP_END:
	LDI R24, 0x00
	ST Y+, R24
POP R25
POP R24
POP R23
POP R22
POP R21
POP R19
POP R18
POP R17
POP R16
POP ZL
POP ZH
POP YL
POP YH
POP XL
POP XH
RET

BASE32_DEC_URL: ; XH:XL = Pointer BASE32 CODE, YH:YL = Pointer OUT STRING
PUSH XH
PUSH XL
PUSH YH
PUSH YL
PUSH ZH
PUSH ZL
PUSH R22
PUSH R23
PUSH R24
PUSH R17
PUSH R16
	LDI ZH, HIGH(BASE32_CODE)
	LDI ZL, LOW(BASE32_CODE)

	LDI R22, 0
	LDI R23, 8

	BASE32_DEC_URL_LOOP:
		
		CPI R23, 0x00
		BRNE BASE32_DEC_URL_WRITE_END
		BASE32_DEC_URL_WRITE:
			ST Y+, R24
			LDI R23, 8
		BASE32_DEC_URL_WRITE_END:
		
		CPI R22, 0x00
		BRNE BASE32_DEC_URL_READ_END
		BASE32_DEC_URL_READ:
			LD R16, X+ 
			CPI R16, 0x00
			BREQ BASE32_DEC_URL_END

			CPI R16, '='
			BREQ BASE32_DEC_URL_END

			RCALL PGM_FIND_CHAR ; (Z) Pointer PGM, R16 = CHAR to FIND, R0:R1 = CHAR POS
			TST R0
			BRMI BASE32_DEC_URL_END
			LSL R1
			LSL R1
			LSL R1
			LDI R22, 5
		BASE32_DEC_URL_READ_END:

		LSL R1
		ROL R24

		DEC R22
		DEC R23
		RJMP BASE32_DEC_URL_LOOP
	BASE32_DEC_URL_END:
		LDI R24 ,0x00
		ST Y+, R24
POP R16
POP R17
POP R24
POP R23
POP R22
POP ZL
POP ZH
POP YL
POP YH
POP XL
POP XH
RET

; (BASE32 code block size must be divisible by 5) + NULL Terminated
; (except the last block) + NULL Terminated
BASE32_DEC_BLOCK: ; XH:XL = Pointer BASE32 CODE, YH:YL = Pointer OUT STRING
PUSH XH
PUSH XL
PUSH YH
PUSH YL
PUSH ZH
PUSH ZL
PUSH R21
PUSH R22
PUSH R23
PUSH R24
PUSH R17
PUSH R16
	LDI ZH, HIGH(BASE32_CODE)
	LDI ZL, LOW(BASE32_CODE)

	LDI R22, 0
	LDI R23, 8

	CLR R0
	CLR R1

	BASE32_DEC_BLOCK_LOOP:

		CPI R23, 0x00
		BRNE BASE32_DEC_BLOCK_WRITE_END
		BASE32_DEC_BLOCK_WRITE:
			ST Y+, R24

			LDI R24, 0x01
			ADD R1, R24
			LDI R24, 0x00
			ADC R0, R24

			LDI R23, 8
		BASE32_DEC_BLOCK_WRITE_END:

		CPI R22, 0x00
		BRNE BASE32_DEC_BLOCK_READ_END
		BASE32_DEC_BLOCK_READ:
			LD R16, X+ 
			CPI R16, 0x00
			BREQ BASE32_DEC_BLOCK_END

			CPI R16, '='
			BREQ BASE32_DEC_BLOCK_FINISH
			
			PUSH R0
			PUSH R1
				RCALL PGM_FIND_CHAR ; (Z) Pointer PGM, R16 = CHAR to FIND, R0:R1 = CHAR POS
				TST R0
				BRMI BASE32_DEC_BLOCK_END
				MOV R21, R1
			POP R1
			POP R0

			LSL R21
			LSL R21
			LSL R21
			LDI R22, 5
		BASE32_DEC_BLOCK_READ_END:

		LSL R21
		ROL R24

		DEC R22
		DEC R23
		RJMP BASE32_DEC_BLOCK_LOOP
	BASE32_DEC_BLOCK_FINISH:
		LDI R24 ,0x00
	RJMP BASE32_DEC_BLOCK_END_END
	BASE32_DEC_BLOCK_END:
		ST Y+, R24
		LDI R24, 0x01
		ADD R1, R24
		LDI R24, 0x00
		ADC R0, R24
	BASE32_DEC_BLOCK_END_END:
POP R16
POP R17
POP R24
POP R23
POP R22
POP R21
POP ZL
POP ZH
POP YL
POP YH
POP XL
POP XH
RET
.endif