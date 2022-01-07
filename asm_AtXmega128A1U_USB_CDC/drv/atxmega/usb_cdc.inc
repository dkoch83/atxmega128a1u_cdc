;/*
; * usb_cdc.inc
; *
; *  Created: 23.02.2016 18:45:41
; *   Author: Dominik Koch
; */ 
.ifndef USB_CDC_INCLUDE
.set USB_CDC_INCLUDE = 1

.DSEG

.CSEG

;##################################################
;
;##################################################
USB_CDC_INIT:
	PUSH R16
	PUSH XL
	PUSH XH
		LDI R16, 0x00
		STS dwDTERate+0, R16
		LDI R16, 0x00
		STS dwDTERate+1, R16
		LDI R16, 0x00
		STS dwDTERate+2, R16
		LDI R16, 0x00
		STS dwDTERate+3, R16

		LDI R16, 0b00000001
		STS bCharFormat+0, R16

		LDI R16, 0b00000000
		STS bParityType+0, R16
	
		LDI R16, 8
		STS bDataBits+0, R16

		LDI R16, 0x00
		STS CDC_STATUS, R16

		STS  CDC_DATA_POSL, R16
		STS  CDC_DATA_POSH, R16
	POP XH
	POP XL
	POP R16
RET
;##################################################
;
;##################################################
USB_CDC_SEND_ENCAPSULATED_COMMAND:
;	PUSH ZL
;	PUSH ZH
;	PUSH R16
;	PUSH R17
;		LDS R16, CDC_RESPONSE_AVAILABLE
;		CPI R16, 0x01
;		BREQ USB_CDC_SEND_ENCAPSULATED_COMMAND_RESPONSE_AVAILABLE
;		RJMP USB_CDC_SEND_ENCAPSULATED_COMMAND_RESPONSE_AVAILABLE_END
;		USB_CDC_SEND_ENCAPSULATED_COMMAND_RESPONSE_AVAILABLE:
;			LDI R16, 0x00
;			STS CDC_RESPONSE_AVAILABLE, R16
;
;			LDI R16, 0b10100001
;			STS EP0_BUFFER+0, R16
;			LDI R16, 0x01 ; RESPONSE_AVAILABLE
;			STS EP0_BUFFER+1, R16
;			LDI R16, 0
;			STS EP0_BUFFER+2, R16
;			LDI R16, 0
;			STS EP0_BUFFER+3, R16
;			LDI R16, 0	; Interface
;			STS EP0_BUFFER+4, R16
;			LDI R16, 0
;			STS EP0_BUFFER+5, R16
;			LDI R16, 0
;			STS EP0_BUFFER+6, R16
;			LDI R16, 0
;			STS EP0_BUFFER+7, R16
;
;			LDI ZL, 0x08
;			LDI ZH, 0x00
;			CALL USB_EP0_SEND ; Z = Size	
;
;			RJMP USB_CDC_SEND_ENCAPSULATED_COMMAND_END
;		USB_CDC_SEND_ENCAPSULATED_COMMAND_RESPONSE_AVAILABLE_END:
;		; Else Send ZLP
;		LDI ZL, 0x08
;		LDI ZH, 0x00
;		CALL USB_EP0_SEND ; Z = Size	
USB_CDC_SEND_ENCAPSULATED_COMMAND_END:
;	POP R17
;	POP R16
;	POP ZH
;	POP ZL
RET
;##################################################
;
;##################################################
USB_CDC_GET_ENCAPSULATED_RESPONSE:
	PUSH ZL
	PUSH ZH
		; Send ZLP
		CLR ZL
		CLR ZH
		RCALL USB_EP0_SEND ; Z = Size	
	POP ZH
	POP ZL
RET
;##################################################
;
;##################################################
USB_CDC_SET_LINE_CODING:	; X = Buffer Pointer
	PUSH ZL
	PUSH ZH
	PUSH R16
	PUSH R17
		LDI R16, 0x00
		LDI ZL, LOW(CDC_LINE_CODING)
		LDI ZH, HIGH(CDC_LINE_CODING)
		RCALL USB_EP_SET_DATAPTR ; R16 = EP | Z = Buffer	

			LDI R16, 0x00
			LDI R17, USB_EP_BUSNACK0_bm | 1<<6
			RCALL USB_EP_CLEAR_STATUS ; R16 = EP, R17 = MASK
			
			USB_CDC_SET_LINE_CODING_WAIT:
				LDI R16, 0x00
				RCALL USB_EP_GET_STATUS
				ANDI R17, USB_EP_BUSNACK0_bm | USB_EP_TRNCOMPL0_bm
				CPI R17, (USB_EP_BUSNACK0_bm | USB_EP_TRNCOMPL0_bm)
			BRNE USB_CDC_SET_LINE_CODING_WAIT

		LDI R16, 0x00
		LDI ZL, LOW(USB_EP_SETUP_BUFFER)
		LDI ZH, HIGH(USB_EP_SETUP_BUFFER)
		RCALL USB_EP_SET_DATAPTR ; R16 = EP | Z = Buffer		
		
		; Send ZLP
		CLR ZL
		CLR ZH
		RCALL USB_EP0_SEND ; Z = Size	
	POP R17
	POP R16
	POP ZH
	POP ZL
RET
;##################################################
;
;##################################################
USB_CDC_GET_LINE_CODING:
	PUSH ZL
	PUSH ZH
	PUSH R16
		LDI R16, 0x80
		LDI ZL, LOW(CDC_LINE_CODING)
		LDI ZH, HIGH(CDC_LINE_CODING)
		RCALL USB_EP_SET_DATAPTR ; R16 = EP | Z = Buffer

		LDI ZH, HIGH(CDC_LINE_CODING_END - CDC_LINE_CODING)
		LDI ZL, LOW(CDC_LINE_CODING_END - CDC_LINE_CODING)
		RCALL USB_EP0_SEND ; Z = Size
	POP R16
	POP ZH
	POP ZL
RET
;##################################################
;
;##################################################
USB_CDC_STATUS_CLREAR_TX:
PUSH R16
	LDS R16, CDC_STATUS
	CBR R16, CDC_TX_bm
	STS CDC_STATUS, R16

	LDI R16, EP_CDC_D_IN
	LDI R17, USB_EP_BUSNACK0_bm | USB_EP_TRNCOMPL0_bm | USB_EP_OVF_bm
	RCALL USB_EP_CLEAR_STATUS ; R16 = EP, R17 = MASK
USB_CDC_STATUS_CLREAR_TX_END:
POP R16
RET
;##################################################
;
;##################################################
USB_CDC_STATUS_CLREAR_RX:
PUSH R16
	LDS R16, CDC_STATUS
	CBR R16, CDC_RX_bm
	STS CDC_STATUS, R16

	LDI R16, EP_CDC_D_OUT
	LDI R17, USB_EP_BUSNACK0_bm | USB_EP_TRNCOMPL0_bm | USB_EP_OVF_bm
	RCALL USB_EP_CLEAR_STATUS ; R16 = EP, R17 = MASK
USB_CDC_STATUS_CLREAR_RX_END:
POP R16
RET
;##################################################
;
;##################################################
USB_CDC_STATUS_SET_TX:
PUSH R16
	LDS R16, CDC_STATUS
	SBR R16, CDC_TX_bm
	STS CDC_STATUS, R16
USB_CDC_STATUS_SET_TX_END:
POP R16
RET
;##################################################
;
;##################################################
USB_CDC_STATUS_SET_RX:
PUSH R16
	LDS R16, CDC_STATUS
	SBR R16, CDC_RX_bm
	STS CDC_STATUS, R16
USB_CDC_STATUS_SET_RX_END:
POP R16
RET
;##################################################
;
;##################################################
USB_CDC_DISABLE_ECHO:
PUSH R16
	LDS R16, CDC_STATUS
	SBR R16, CDC_ECHO_DISABLE_bm
	STS CDC_STATUS, R16
USB_CDC_DISABLE_ECHO_END:
POP R16
RET
;##################################################
;
;##################################################
USB_CDC_ENABLE_ECHO:
PUSH R16
	LDS R16, CDC_STATUS
	CBR R16, CDC_ECHO_DISABLE_bm
	STS CDC_STATUS, R16
USB_CDC_ENABLE_ECHO_END:
POP R16
RET
;##################################################
;
;##################################################
USB_CDC_COPY_BUFFER_TO_Z:
PUSH R16

USB_CDC_COPY_BUFFER_TO_Z_END:
POP R16
RET


.endif