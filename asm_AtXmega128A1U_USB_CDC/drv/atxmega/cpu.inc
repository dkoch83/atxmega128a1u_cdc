;/*
;* cpu.inc
;*
;*  Created: 22.02.2015 19:13:48
;*   Author: Dominik
;*/ 

.IFNDEF GPIO_GPIOR0
	.equ GPIO_GPIOR0 = 0		; General Purpose IO Register 0
.ENDIF
.IFNDEF GPIO_GPIOR1
	.equ GPIO_GPIOR1 = 1		; General Purpose IO Register 1
.ENDIF
.IFNDEF GPIO_GPIOR2
	.equ GPIO_GPIOR2 = 2		; General Purpose IO Register 2
.ENDIF
.IFNDEF GPIO_GPIOR3
	.equ GPIO_GPIOR3 = 3		; General Purpose IO Register 3
.ENDIF
.IFNDEF GPIO_GPIOR4
	.equ GPIO_GPIOR4 = 4		; General Purpose IO Register 4
.ENDIF
.IFNDEF GPIO_GPIOR5
	.equ GPIO_GPIOR5 = 5		; General Purpose IO Register 5
.ENDIF
.IFNDEF GPIO_GPIOR6
	.equ GPIO_GPIOR6 = 6		; General Purpose IO Register 6
.ENDIF
.IFNDEF GPIO_GPIOR7
	.equ GPIO_GPIOR7 = 7		; General Purpose IO Register 7
.ENDIF
.IFNDEF GPIO_GPIOR8
	.equ GPIO_GPIOR8 = 8		; General Purpose IO Register 8
.ENDIF
.IFNDEF GPIO_GPIOR9
	.equ GPIO_GPIOR9 = 9		; General Purpose IO Register 9
.ENDIF
.IFNDEF GPIO_GPIORA
	.equ GPIO_GPIORA = 10		; General Purpose IO Register 10
.ENDIF
.IFNDEF GPIO_GPIORB
	.equ GPIO_GPIORB = 11		; General Purpose IO Register 11
.ENDIF
.IFNDEF GPIO_GPIORC
	.equ GPIO_GPIORC = 12		; General Purpose IO Register 12
.ENDIF
.IFNDEF GPIO_GPIORD
	.equ GPIO_GPIORD = 13		; General Purpose IO Register 13
.ENDIF
.IFNDEF GPIO_GPIORE
	.equ GPIO_GPIORE = 14		; General Purpose IO Register 14
.ENDIF
.IFNDEF GPIO_GPIORF
	.equ GPIO_GPIORF = 15		; General Purpose IO Register 15
.ENDIF

.IFNDEF CPU_BASE
	.equ CPU_BASE = 0x0030
.ENDIF

.IFNDEF RST_BASE
	.equ RST_BASE = 0x0078
.ENDIF


.MACRO CPU_SOFT_RESET
	LDI R16, 0xD8
	STS (CPU_BASE+0x04), R16

	LDI R16, 0x01
	STS (RST_BASE+0x01), R16
.ENDMACRO

.MACRO CPU_CCP_SPM
	LDI R16, 0x9D
	STS (CPU_BASE+0x04), R16
.ENDMACRO

.MACRO CPU_CCP_IOREG
	LDI R16, 0xD8
	STS (CPU_BASE+0x04), R16
.ENDMACRO