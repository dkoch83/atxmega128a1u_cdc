;/*
; * xmega128A1U_USB_CDC.asm
; *
; *  Created: 07.03.2016 19:30:12
; *   Author: Dominik Koch
; */ 

.include "./include/std.inc"

.SET F_MCU	 = 32000000
.SET AVRMCU	 = ATXMEGA

.CSEG
.ORG 0x000 
;0x000 RESET
JMP RESET
.ORG 0x002
;0x002 OSCF_INT_ivect 	Crystal Oscillator Failure Interrupt vector (NMI)
JMP OSCF_ivect				;PLL and external oscillator failure interrupt vector (NMI)
.ORG 0x004
;0x004 PORTC_INT_base 	Port C Interrupt base
JMP PORTC_INT0_ivect			;Port interrupt vector 0 offset
JMP PORTC_INT1_ivect			;Port interrupt vector 1 offset
.ORG 0x008
;0x008 PORTR_INT_base 	Port R Interrupt base
JMP PORTR_INT0_ivect			;Port interrupt vector 0 offset
JMP PORTR_INT1_ivect			;Port interrupt vector 1 offset
.ORG 0x00C
;0x00C DMA_INT_base 	DMA Controller Interrupt base
JMP DMA_CH0_ivect			;DMA controller channel 0 interrupt vector
JMP DMA_CH1_ivect			;DMA controller channel 1 interrupt vector
JMP DMA_CH2_ivect			;DMA controller channel 2 interrupt vector
JMP DMA_CH3_ivect			;DMA controller channel 3 interrupt vector
.ORG 0x014
;0x014 RTC32_INT_base 	32-bit Real Time Counter Interrupt base
JMP RTC32_OVF_ivect				;Real-time counter overflow interrupt vector
JMP RTC32_COMP_ivect				;Real-time counter compare match interrupt vector
.ORG 0x018
;0x018 TWIC_INT_base 	Two-Wire Interface on Port C Interrupt base
JMP TWIC_SLAVE_ivect			;TWI slave interrupt vector
JMP TWIC_MASTER_ivect		;TWI master interrupt vector
.ORG 0x01C
;0x01C TCC0_INT_base 	Timer/Counter 0 on port C Interrupt base
JMP TCC0_OVF_ivect			;Timer/counter overflow/underflow interrupt vector offset
JMP TCC0_ERR_ivect			;Timer/counter error interrupt vector offset
JMP TCC0_CCA_ivect			;Timer/counter compare or capture channel A interrupt vector offset
JMP TCC0_CCB_ivect			;Timer/counter compare or capture channel B interrupt vector offset
JMP TCC0_CCC_ivect			;Timer/counter compare or capture channel C interrupt vector offset
JMP TCC0_CCD_ivect			;Timer/counter compare or capture channel D interrupt vector offset
.ORG 0x028
;0x028 TCC1_INT_base 	Timer/Counter 1 on port C Interrupt base
JMP TCC1_OVF_ivect			;Timer/counter overflow/underflow interrupt vector offset
JMP TCC1_ERR_ivect			;Timer/counter error interrupt vector offset
JMP TCC1_CCA_ivect			;Timer/counter compare or capture channel A interrupt vector offset
JMP TCC1_CCB_ivect			;Timer/counter compare or capture channel B interrupt vector offset
.ORG 0x030
;0x030 SPIC_INT_ivect 	SPI on port C Interrupt vector
JMP SPIC_ivect				;SPI interrupt vector
;0x032 USARTC0_INT_base USART 0 on port C Interrupt base
JMP USARTC0_RXC_ivect		;USART receive complete interrupt vector
JMP USARTC0_DRE_ivect		;USART data register empty interrupt vector
JMP USARTC0_TXC_ivect		;USART transmit complete interrupt vector
.ORG 0x038
;0x038 USARTC1_INT_base USART 1 on port C Interrupt base
JMP USARTC1_RXC_ivect		;USART receive complete interrupt vector
JMP USARTC1_DRE_ivect		;USART data register empty interrupt vector
JMP USARTC1_TXC_ivect		;USART transmit complete interrupt vector
.ORG 0x03E
;0x03E AES_INT_ivect 	AES Interrupt vector
JMP AES_ivect				;AES interrupt vector
.ORG 0x040
;0x040 NVM_INT_base 	Non-Volatile Memory Interrupt base
JMP EE_ivect					;Nonvolatile memory EEPROM interrupt vector
JMP SPM_ivect				;Nonvolatile memory SPM interrupt vector
.ORG 0x044
;0x044 PORTB_INT_base 	Port B Interrupt base
JMP PORTB_INT0_ivect			;Port interrupt vector 0 offset
JMP PORTB_INT1_ivect			;Port interrupt vector 1 offset
.ORG 0x048
;0x048 ACB_INT_base		Analog Comparator on Port B Interrupt base
JMP ACB_COMP0_ivect			;Analog comparator 0 interrupt vector
JMP ACB_COMP1_ivect			;Analog comparator 1 interrupt vector
JMP ACB_WINDOW_ivect			;Analog comparator window interrupt vector
.ORG 0x04E
;0x04E ADCB_INT_base 	Analog to Digital Converter on Port B Interrupt base
JMP ADCB_CH0				;Analog-to-digital converter channel 0 interrupt vector
JMP ADCB_CH1				;Analog-to-digital converter channel 1 interrupt vector
JMP ADCB_CH2				;Analog-to-digital converter channel 2 interrupt vector
JMP ADCB_CH3				;Analog-to-digital converter channel 3 interrupt vector
.ORG 0x056
;0x056 PORTE_INT_base 	Port E Interrupt base
JMP PORTE_INT0_ivect			;Port interrupt vector 0 offset
JMP PORTE_INT1_ivect			;Port interrupt vector 1 offset
.ORG 0x05A
;0x05A TWIE_INT_base 	Two-Wire Interface on Port E Interrupt base
JMP TWIE_SLAVE_ivect			;TWI slave interrupt vector
JMP TWIE_MASTER_ivect		;TWI master interrupt vector
.ORG 0x05E
;0x05E TCE0_INT_base 	Timer/Counter 0 on port E Interrupt base
JMP TCE0_OVF_ivect			;Timer/counter overflow/underflow interrupt vector offset
JMP TCE0_ERR_ivect			;Timer/counter error interrupt vector offset
JMP TCE0_CCA_ivect			;Timer/counter compare or capture channel A interrupt vector offset
JMP TCE0_CCB_ivect			;Timer/counter compare or capture channel B interrupt vector offset
JMP TCE0_CCC_ivect			;Timer/counter compare or capture channel C interrupt vector offset
JMP TCE0_CCD_ivect			;Timer/counter compare or capture channel D interrupt vector offset
.ORG 0x06A
;0x06A TCE1_INT_base 	Timer/Counter 1 on port E Interrupt base
JMP TCE1_OVF_ivect			;Timer/counter overflow/underflow interrupt vector offset
JMP TCE1_ERR_ivect			;Timer/counter error interrupt vector offset
JMP TCE1_CCA_ivect			;Timer/counter compare or capture channel A interrupt vector offset
JMP TCE1_CCB_ivect			;Timer/counter compare or capture channel B interrupt vector offset
.ORG 0x072
;0x072 SPIE_INT_ivect 		SPI on port E interrupt vector
JMP SPIE_ivect 				;SPI interrupt vector
.ORG 0x074
;0x074 USARTE0_INT_base USART 0 on port E Interrupt base
JMP USARTE0_RXC_ivect		;USART receive complete interrupt vector
JMP USARTE0_DRE_ivect		;USART data register empty interrupt vector
JMP USARTE0_TXC_ivect		;USART transmit complete interrupt vector
.ORG 0x07A
;0x07A USARTE1_INT_base 	USART 1 on port E interrupt base
JMP USARTE1_RXC_ivect 		;USART receive complete interrupt vector
JMP USARTE1_DRE_ivect 		;USART data register empty interrupt vector
JMP USARTE1_TXC_ivect 		;USART transmit complete interrupt vector
.ORG 0x080
;0x080 PORTD_INT_base 	Port D Interrupt base
JMP PORTD_INT0_ivect			;Port interrupt vector 0 offset
JMP PORTD_INT1_ivect			;Port interrupt vector 1 offset
.ORG 0x084
;0x084 PORTA_INT_base 	Port A Interrupt base
JMP PORTA_INT0_ivect			;Port interrupt vector 0 offset
JMP PORTA_INT1_ivect			;Port interrupt vector 1 offset
.ORG 0x088
;0x088 ACA_INT_base		Analog Comparator on Port A Interrupt base
JMP ACA_COMP0_ivect			;Analog comparator 0 interrupt vector
JMP ACA_COMP1_ivect			;Analog comparator 1 interrupt vector
JMP ACA_WINDOW_ivect			;Analog comparator window interrupt vector
.ORG 0x08E
;0x08E ADCA_INT_base 	Analog to Digital Converter on Port A Interrupt base
JMP ADCA_CH0				;Analog-to-digital converter channel 0 interrupt vector
JMP ADCA_CH1				;Analog-to-digital converter channel 1 interrupt vector
JMP ADCA_CH2				;Analog-to-digital converter channel 2 interrupt vector
JMP ADCA_CH3				;Analog-to-digital converter channel 3 interrupt vector
.ORG 0x096
;0x096 TWID_INT_base 		Two-Wire Interface on port D interrupt base
JMP TWID_SLAVE_ivect 		;TWI slave interrupt vector
JMP TWID_MASTER_ivect 		;TWI master interrupt vector
.ORG 0x09A
;0x09A TCD0_INT_base 	Timer/Counter 0 on port D Interrupt base
JMP TCD0_OVF_ivect			;Timer/counter overflow/underflow interrupt vector offset
JMP TCD0_ERR_ivect			;Timer/counter error interrupt vector offset
JMP TCD0_CCA_ivect			;Timer/counter compare or capture channel A interrupt vector offset
JMP TCD0_CCB_ivect			;Timer/counter compare or capture channel B interrupt vector offset
JMP TCD0_CCC_ivect			;Timer/counter compare or capture channel C interrupt vector offset
JMP TCD0_CCD_ivect			;Timer/counter compare or capture channel D interrupt vector offset
.ORG 0x0A6
;0x0A6 TCD1_INT_base 	Timer/Counter 1 on port D Interrupt base
JMP TCD1_OVF_ivect			;Timer/counter overflow/underflow interrupt vector offset
JMP TCD1_ERR_ivect			;Timer/counter error interrupt vector offset
JMP TCD1_CCA_ivect			;Timer/counter compare or capture channel A interrupt vector offset
JMP TCD1_CCB_ivect			;Timer/counter compare or capture channel B interrupt vector offset
.ORG 0x0AE
;0x0AE SPID_INT_ivector 	SPI on port D Interrupt vector
JMP SPID_ivect				;SPI interrupt vector
.ORG 0x0B0
;0x0B0 USARTD0_INT_base USART 0 on port D Interrupt base
JMP USARTD0_RXC_ivect		;USART receive complete interrupt vector
JMP USARTD0_DRE_ivect		;USART data register empty interrupt vector
JMP USARTD0_TXC_ivect		;USART transmit complete interrupt vector
.ORG 0x0B6
;0x0B6 USARTD1_INT_base USART 1 on port D Interrupt base
JMP USARTD1_RXC_ivect		;USART receive complete interrupt vector
JMP USARTD1_DRE_ivect		;USART data register empty interrupt vector
JMP USARTD1_TXC_ivect		;USART transmit complete interrupt vector
.ORG 0x0BC
;0x0BC PORTQ_INT_base 		Port Q INT base
JMP PORTQ_INT0_ivect 		;Port interrupt vector 0 offset
JMP PORTQ_INT1_ivect 		;Port interrupt vector 1 offset
.ORG 0x0C0
;0x0C0 PORTH_INT_base 		Port H INT base
JMP PORTH_INT0_ivect 		;Port interrupt vector 0 offset
JMP PORTH_INT1_ivect 		;Port interrupt vector 1 offset
.ORG 0x0C4
;0x0C4 PORTJ_INT_base 		Port J INT base
JMP PORTJ_INT0_ivect 		;Port interrupt vector 0 offset
JMP PORTJ_INT1_ivect 		;Port interrupt vector 1 offset
.ORG 0x0C8
;0x0C8 PORTK_INT_base 		Port K INT base
JMP PORTK_INT0_ivect 		;Port interrupt vector 0 offset
JMP PORTK_INT1_ivect 		;Port interrupt vector 1 offset
.ORG 0x0D0
;0x0D0 PORTF_INT_base	Port F INT base
JMP PORTF_INT0_ivect			;Port interrupt vector 0 offset
JMP PORTF_INT1_ivect			;Port interrupt vector 1 offset
.ORG 0x0D4
;0x0D4 TWIF_INT_base 		Two-Wire interface on Port F INT base
JMP TWIF_SLAVE_ivect 		;TWI slave interrupt vector
JMP TWIF_MASTER_ivect 		;TWI master interrupt vector
.ORG 0x0D8
;0x0D8 TCF0_INT_base 	Timer/Counter 0 on port F Interrupt base
JMP TCF0_OVF_ivect			;Timer/counter overflow/underflow interrupt vector offset
JMP TCF0_ERR_ivect			;Timer/counter error interrupt vector offset
JMP TCF0_CCA_ivect			;Timer/counter compare or capture channel A interrupt vector offset
JMP TCF0_CCB_ivect			;Timer/counter compare or capture channel B interrupt vector offset
JMP TCF0_CCC_ivect			;Timer/counter compare or capture channel C interrupt vector offset
JMP TCF0_CCD_ivect			;Timer/counter compare or capture channel D interrupt vector offset
.ORG 0x0E4
;0x0E4 TCF1_INT_base 		Timer/counter 1 on port F interrupt base
JMP TCF1_OVF_ivect 				;Timer/counter overflow/underflow interrupt vector offset
JMP TCF1_ERR_ivect				;Timer/counter error interrupt vector offset
JMP TCF1_CCA_ivect				;Timer/counter compare or capture channel A interrupt vector offset
JMP TCF1_CCB_ivect				;Timer/counter compare or capture channel B interrupt vector offset
.ORG 0x0EC
;0x0EC SPIF_INT_ivector 		SPI ion port F interrupt base
JMP SPIF_ivect 				;SPI interrupt vector
.ORG 0x0EE
;0x0EE USARTF0_INT_base USART 0 on port F Interrupt base
JMP USARTF0_RXC_ivect		;USART receive complete interrupt vector
JMP USARTF0_DRE_ivect		;USART data register empty interrupt vector
JMP USARTF0_TXC_ivect		;USART transmit complete interrupt vector
.ORG 0x0F4
;0x0F4 USARTF1_INT_base 	USART 1 on port F interrupt base
JMP USARTF1_RXC_ivect 		;USART receive complete interrupt vector
JMP USARTF1_DRE_ivect 		;USART data register empty interrupt vector
JMP USARTF1_TXC_ivect 		;USART transmit complete interrupt vector
.ORG 0x0FA
;0x0FA USB_INT_base 		USB on port D interrupt base
JMP USB_BUSEVENT_ivect			;SOF, suspend, resume, bus reset, CRC, underflow, overflow, and stall error interrupts
JMP USB_TRNCOMPL_ivect			;Transaction complete interrupt


;############################# Include Section ####################################
.set NO_PGM_READ_BYTE		= 1
.set NO_PGM_READ_WORD		= 1
;.set NO_PGM_READ_BUFFER	= 1
.set NO_PGM_READ_STR		= 1
.set NO_PGM_STRLEN			= 1
.set NO_PGM_FIND_CHAR		= 1
.INCLUDE "./drv/pgm.inc"
.INCLUDE "./drv/atxmega/clock.inc"

;############################# Include Section END ################################

RESET:					;RESET
	
	;Init stack pointer
	LDI		R16, LOW(RAMEND)	;
	LDI		R17, HIGH(RAMEND)	;
	OUT		CPU_SPL, R16		;
	OUT		CPU_SPH, R17		;

	;Clock Config
	ENABLE_EXT_16MHZ
	LDI R16, EXT_16MHZ
	LDI R17, 2
	RCALL SET_SYSCLOCK_PLL

	DISABLE_INT_2MHZ

	;Clear Ram
	LDI	XL, LOW(SRAM_START)
	LDI	XH, HIGH(SRAM_START)

	LDI YL, LOW(SRAM_SIZE)
	LDI YH, HIGH(SRAM_SIZE)
	LDI		R16, 0x00

	RAMCLEAN:
		ST X+, R16
		SBIW Y, 1
	BRNE RAMCLEAN
JMP MAIN

;0x002 OSCF_INT_ivect 	Crystal Oscillator Failure Interrupt vector (NMI)
OSCF_ivect:				;PLL and external oscillator failure interrupt vector (NMI)
RETI

;0x004 PORTC_INT_base 	Port C Interrupt base
PORTC_INT0_ivect:			;Port interrupt vector 0 offset
RETI

PORTC_INT1_ivect:			;Port interrupt vector 1 offset
RETI

;0x008 PORTR_INT_base 	Port R Interrupt base
PORTR_INT0_ivect:			;Port interrupt vector 0 offset
RETI

PORTR_INT1_ivect:			;Port interrupt vector 1 offset
RETI

;0x00C DMA_INT_base 	DMA Controller Interrupt base
DMA_CH0_ivect:			;DMA controller channel 0 interrupt vector
RETI

DMA_CH1_ivect:			;DMA controller channel 1 interrupt vector
RETI

DMA_CH2_ivect:			;DMA controller channel 2 interrupt vector
RETI

DMA_CH3_ivect:			;DMA controller channel 3 interrupt vector
RETI

;0x014 RTC32_INT_base 	32-bit Real Time Counter Interrupt base
RTC32_COMP_ivect:				;Real-time counter compare match interrupt vector
RETI

RTC32_OVF_ivect:				;Real-time counter overflow interrupt vector
RETI

COMP_ivect:				;Real-time counter compare match interrupt vector
RETI

;0x018 TWIC_INT_base 	Two-Wire Interface on Port C Interrupt base
TWIC_SLAVE_ivect:			;TWI slave interrupt vector
RETI

TWIC_MASTER_ivect:		;TWI master interrupt vector
RETI

;0x01C TCC0_INT_base 	Timer/Counter 0 on port C Interrupt base
TCC0_OVF_ivect:			;Timer/counter overflow/underflow interrupt vector offset
RETI

TCC0_ERR_ivect:			;Timer/counter error interrupt vector offset
RETI

TCC0_CCA_ivect:			;Timer/counter compare or capture channel A interrupt vector offset
RETI

TCC0_CCB_ivect:			;Timer/counter compare or capture channel B interrupt vector offset
RETI

TCC0_CCC_ivect:			;Timer/counter compare or capture channel C interrupt vector offset
RETI

TCC0_CCD_ivect:			;Timer/counter compare or capture channel D interrupt vector offset
RETI

;0x028 TCC1_INT_base 	Timer/Counter 1 on port C Interrupt base
TCC1_OVF_ivect:			;Timer/counter overflow/underflow interrupt vector offset
RETI

TCC1_ERR_ivect:			;Timer/counter error interrupt vector offset
RETI

TCC1_CCA_ivect:			;Timer/counter compare or capture channel A interrupt vector offset
RETI

TCC1_CCB_ivect:			;Timer/counter compare or capture channel B interrupt vector offset
RETI

;0x030 SPIC_INT_ivect 	SPI on port C Interrupt vector
SPIC_ivect:				;SPI interrupt vector
RETI

;0x032 USARTC0_INT_base USART 0 on port C Interrupt base
USARTC0_RXC_ivect:		;USART receive complete interrupt vector
RETI

USARTC0_DRE_ivect:		;USART data register empty interrupt vector
RETI

USARTC0_TXC_ivect:		;USART transmit complete interrupt vector
RETI

;0x038 USARTC1_INT_base USART 1 on port C Interrupt base
RETI

USARTC1_RXC_ivect:		;USART receive complete interrupt vector
RETI

USARTC1_DRE_ivect:		;USART data register empty interrupt vector
RETI

USARTC1_TXC_ivect:		;USART transmit complete interrupt vector
RETI

;0x03E AES_INT_ivect 	AES Interrupt vector
AES_ivect:				;AES interrupt vector
RETI

;0x040 NVM_INT_base 	Non-Volatile Memory Interrupt base
EE_ivect:				;Nonvolatile memory EEPROM interrupt vector
RETI

SPM_ivect:				;Nonvolatile memory SPM interrupt vector
RETI

;0x044 PORTB_INT_base 	Port B Interrupt base
PORTB_INT0_ivect:			;Port interrupt vector 0 offset
RETI

PORTB_INT1_ivect:			;Port interrupt vector 1 offset
RETI

;0x048 ACB_INT_base		Analog Comparator on Port B Interrupt base
ACB_COMP0_ivect:			;Analog comparator 0 interrupt vector
RETI

ACB_COMP1_ivect:			;Analog comparator 1 interrupt vector
RETI

ACB_WINDOW_ivect:			;Analog comparator window interrupt vector
RETI

;0x04E ADCB_INT_base 	Analog to Digital Converter on Port B Interrupt base
ADCB_CH0:				;Analog-to-digital converter channel 0 interrupt vector
RETI

ADCB_CH1:				;Analog-to-digital converter channel 1 interrupt vector
RETI

ADCB_CH2:				;Analog-to-digital converter channel 2 interrupt vector
RETI

ADCB_CH3:				;Analog-to-digital converter channel 3 interrupt vector
RETI

;0x056 PORTE_INT_base 	Port E Interrupt base
PORTE_INT0_ivect:			;Port interrupt vector 0 offset
RETI

PORTE_INT1_ivect:			;Port interrupt vector 1 offset
RETI

;0x05A TWIE_INT_base 	Two-Wire Interface on Port E Interrupt base
TWIE_SLAVE_ivect:			;TWI slave interrupt vector
RETI

TWIE_MASTER_ivect:		;TWI master interrupt vector
RETI

;0x05E TCE0_INT_base 	Timer/Counter 0 on port E Interrupt base
TCE0_OVF_ivect:			;Timer/counter overflow/underflow interrupt vector offset
RETI

TCE0_ERR_ivect:			;Timer/counter error interrupt vector offset
RETI

TCE0_CCA_ivect:			;Timer/counter compare or capture channel A interrupt vector offset
RETI

TCE0_CCB_ivect:			;Timer/counter compare or capture channel B interrupt vector offset
RETI

TCE0_CCC_ivect:			;Timer/counter compare or capture channel C interrupt vector offset
RETI

TCE0_CCD_ivect:			;Timer/counter compare or capture channel D interrupt vector offset
RETI

;0x06A TCE1_INT_base 	Timer/Counter 1 on port E Interrupt base
TCE1_OVF_ivect:			;Timer/counter overflow/underflow interrupt vector offset
RETI

TCE1_ERR_ivect:			;Timer/counter error interrupt vector offset
RETI

TCE1_CCA_ivect:			;Timer/counter compare or capture channel A interrupt vector offset
RETI

TCE1_CCB_ivect:			;Timer/counter compare or capture channel B interrupt vector offset
RETI

;0x072 SPIE_INT_ivect 		SPI on port E interrupt vector
SPIE_ivect:				;SPI interrupt vector
RETI

;0x074 USARTE0_INT_base USART 0 on port E Interrupt base
USARTE0_RXC_ivect:		;USART receive complete interrupt vector
RETI

USARTE0_DRE_ivect:		;USART data register empty interrupt vector
RETI

USARTE0_TXC_ivect:		;USART transmit complete interrupt vector
RETI

;0x07A USARTE1_INT_base 	USART 1 on port E interrupt base
USARTE1_RXC_ivect:		;USART receive complete interrupt vector
RETI

USARTE1_DRE_ivect:		;USART data register empty interrupt vector
RETI

USARTE1_TXC_ivect:		;USART transmit complete interrupt vector
RETI

;0x080 PORTD_INT_base 	Port D Interrupt base
PORTD_INT0_ivect:			;Port interrupt vector 0 offset
RETI

PORTD_INT1_ivect:			;Port interrupt vector 1 offset
RETI

;0x084 PORTA_INT_base 	Port A Interrupt base
PORTA_INT0_ivect:			;Port interrupt vector 0 offset
RETI

PORTA_INT1_ivect:			;Port interrupt vector 1 offset
RETI

;0x088 ACA_INT_base		Analog Comparator on Port A Interrupt base
ACA_COMP0_ivect:			;Analog comparator 0 interrupt vector
RETI

ACA_COMP1_ivect:			;Analog comparator 1 interrupt vector
RETI

ACA_WINDOW_ivect:			;Analog comparator window interrupt vector
RETI

;0x08E ADCA_INT_base 	Analog to Digital Converter on Port A Interrupt base
ADCA_CH0:				;Analog-to-digital converter channel 0 interrupt vector
RETI

ADCA_CH1:				;Analog-to-digital converter channel 1 interrupt vector
RETI

ADCA_CH2:				;Analog-to-digital converter channel 2 interrupt vector
RETI

ADCA_CH3:				;Analog-to-digital converter channel 3 interrupt vector
RETI

;0x096 TWID_INT_base 		Two-Wire Interface on port D interrupt base
TWID_SLAVE_ivect:		;TWI slave interrupt vector
RETI

TWID_MASTER_ivect:		;TWI master interrupt vector
RETI

;0x09A TCD0_INT_base 	Timer/Counter 0 on port D Interrupt base
TCD0_OVF_ivect:			;Timer/counter overflow/underflow interrupt vector offset
RETI

TCD0_ERR_ivect:			;Timer/counter error interrupt vector offset
RETI

TCD0_CCA_ivect:			;Timer/counter compare or capture channel A interrupt vector offset
RETI

TCD0_CCB_ivect:			;Timer/counter compare or capture channel B interrupt vector offset
RETI

TCD0_CCC_ivect:			;Timer/counter compare or capture channel C interrupt vector offset
RETI

TCD0_CCD_ivect:			;Timer/counter compare or capture channel D interrupt vector offset
RETI

;0x0A6 TCD1_INT_base 	Timer/Counter 1 on port D Interrupt base
TCD1_OVF_ivect:			;Timer/counter overflow/underflow interrupt vector offset
RETI

TCD1_ERR_ivect:			;Timer/counter error interrupt vector offset
RETI

TCD1_CCA_ivect:			;Timer/counter compare or capture channel A interrupt vector offset
RETI

TCD1_CCB_ivect:			;Timer/counter compare or capture channel B interrupt vector offset
RETI

;0x0AE SPID_INT_ivector 	SPI on port D Interrupt vector
SPID_ivect:				;SPI interrupt vector
RETI

;0x0B0 USARTD0_INT_base USART 0 on port D Interrupt base
USARTD0_RXC_ivect:		;USART receive complete interrupt vector
RETI

USARTD0_DRE_ivect:		;USART data register empty interrupt vector
RETI

USARTD0_TXC_ivect:		;USART transmit complete interrupt vector
RETI

;0x0B6 USARTD1_INT_base USART 1 on port D Interrupt base
USARTD1_RXC_ivect:		;USART receive complete interrupt vector
RETI

USARTD1_DRE_ivect:		;USART data register empty interrupt vector
RETI

USARTD1_TXC_ivect:		;USART transmit complete interrupt vector
RETI

;0x0BC PORTQ_INT_base 		Port Q INT base
PORTQ_INT0_ivect:		;Port interrupt vector 0 offset
RETI

PORTQ_INT1_ivect:		;Port interrupt vector 1 offset
RETI

;0x0C0 PORTH_INT_base 		Port H INT base
PORTH_INT0_ivect:		;Port interrupt vector 0 offset
RETI

PORTH_INT1_ivect:		;Port interrupt vector 1 offset
RETI

;0x0C4 PORTJ_INT_base 		Port J INT base
PORTJ_INT0_ivect:		;Port interrupt vector 0 offset
RETI

PORTJ_INT1_ivect:		;Port interrupt vector 1 offset
RETI

;0x0C8 PORTK_INT_base 		Port K INT base
PORTK_INT0_ivect:		;Port interrupt vector 0 offset
RETI

PORTK_INT1_ivect:		;Port interrupt vector 1 offset
RETI

;0x0D0 PORTF_INT_base	Port F INT base
PORTF_INT0_ivect:			;Port interrupt vector 0 offset
RETI

PORTF_INT1_ivect:			;Port interrupt vector 1 offset
RETI

;0x0D4 TWIF_INT_base 		Two-Wire interface on Port F INT base
TWIF_SLAVE_ivect:		;TWI slave interrupt vector
RETI

TWIF_MASTER_ivect:		;TWI master interrupt vector
RETI

;0x0D8 TCF0_INT_base 	Timer/Counter 0 on port F Interrupt base
TCF0_OVF_ivect:			;Timer/counter overflow/underflow interrupt vector offset
RETI

TCF0_ERR_ivect:			;Timer/counter error interrupt vector offset
RETI

TCF0_CCA_ivect:			;Timer/counter compare or capture channel A interrupt vector offset
RETI

TCF0_CCB_ivect:			;Timer/counter compare or capture channel B interrupt vector offset
RETI

TCF0_CCC_ivect:			;Timer/counter compare or capture channel C interrupt vector offset
RETI

TCF0_CCD_ivect:			;Timer/counter compare or capture channel D interrupt vector offset
RETI

;0x0E4 TCF1_INT_base 		Timer/counter 1 on port F interrupt base
TCF1_OVF_ivect:				;Timer/counter overflow/underflow interrupt vector offset
RETI

TCF1_ERR_ivect:				;Timer/counter error interrupt vector offset
RETI

TCF1_CCA_ivect:				;Timer/counter compare or capture channel A interrupt vector offset
RETI

TCF1_CCB_ivect:				;Timer/counter compare or capture channel B interrupt vector offset
RETI

;0x0EC SPIF_INT_ivector 		SPI ion port F interrupt base
SPIF_ivect:				;SPI interrupt vector
RETI

;0x0EE USARTF0_INT_base USART 0 on port F Interrupt base
USARTF0_RXC_ivect:		;USART receive complete interrupt vector
RETI

USARTF0_DRE_ivect:		;USART data register empty interrupt vector
RETI

USARTF0_TXC_ivect:		;USART transmit complete interrupt vector
RETI

;0x0F4 USARTF1_INT_base 	USART 1 on port F interrupt base
USARTF1_RXC_ivect:		;USART receive complete interrupt vector
RETI

USARTF1_DRE_ivect:		;USART data register empty interrupt vector
RETI

USARTF1_TXC_ivect:		;USART transmit complete interrupt vector
RETI

;##########################################################
; in ./drv/atxmega/usb_interrupts.inc
;##########################################################

;0x0FA USB_INT_base 		USB on port D interrupt base
;USB_BUSEVENT_ivect:			;SOF, suspend, resume, bus reset, CRC, underflow, overflow, and stall error interrupts
;RETI

;USB_TRNCOMPL_ivect:			;Transaction complete interrupt
;RETI
;##########################################################


.INCLUDE "./drv/atxmega/nvm.inc"
.INCLUDE "./drv/atxmega/usb.inc"

.DSEG

.CSEG

MAIN:
	LDI R16, PMIC_LOLVLEN_bm | PMIC_MEDLVLEN_bm | PMIC_HILVLEN_bm
	STS PMIC_CTRL, R16
	CALL USB_CLK_INIT
	CALL USB_INIT
	SEI
	USB_ATTACH
LOOP:
	LDS R16, CDC_STATUS
	SBRS R16, CDC_RX_bp
	RJMP LOOP_CDC_RX_END
	LOOP_CDC_RX:
		LDI XL, LOW(CDC_OUT_BUFFER)
		LDI XH, HIGH(CDC_OUT_BUFFER)

		;RX Count to TX Count
		LDI R16, EP_CDC_D_OUT
		RCALL USB_EP_GET_CNT ; R16 = EP | RETURN Z

		LDI R16, EP_CDC_D_IN
		RCALL USB_EP_SET_CNT ; R16 = EP | Z = CNT

		MOVW Y, Z

		LDI ZL, LOW(CDC_DATA)
		LDI ZH, HIGH(CDC_DATA)

		;Lade CDC_DATA Pos
		LDS R20, CDC_DATA_POSL
		LDS R21, CDC_DATA_POSH

		ADD ZL, R20
		ADC ZH, R21

		;Set Buffer Pointer
		LDI R16, EP_CDC_D_IN
		RCALL USB_EP_SET_DATAPTR ; R16 = EP | Z = Buffer

		;Save CDC_DATA Pos
		ADD R20, YL
		ADC R21, YH
		STS CDC_DATA_POSL, R20
		STS CDC_DATA_POSH, R21

		;Copy CDC_OUT_BUFFER to CDC_DATA
		USB_CDC_COPY_LOOP:
			LD R16, X+
			ST Z+, R16
			SBIW Y, 1
		BRNE USB_CDC_COPY_LOOP
		
		CALL USB_CDC_STATUS_SET_TX
		CALL USB_CDC_STATUS_CLREAR_RX
	LOOP_CDC_RX_END:
RJMP LOOP
