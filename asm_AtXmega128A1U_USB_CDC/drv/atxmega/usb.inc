;/*	
; * usb.inc
; *
; *  Created: 07.01.2016 22:48:44
; *   Author: Dominik Koch
; */ 
 .ifndef USB_INCLUDE
.set USB_INCLUDE = 1

.EQU CONTROL		= 0b00000000
.EQU ISOCHRONOUS	= 0b00000001
.EQU BULK			= 0b00000010
.EQU INTERRUPT		= 0b00000011

.EQU EP_IN			= 0b10000000
.EQU EP_OUT			= 0b00000000
;Synchronisation Type (Iso Mode) 
.EQU ISO_NO_SYNC	= 0b00000000
.EQU ISO_ASYNC		= 0b00000100
.EQU ISO_ADAPTIVE	= 0b00001000
.EQU ISO_SYNC		= 0b00001100
;Usage Type (Iso Mode) 
.EQU DATA_EP			= 0b00000000
.EQU FEEDBACK_EP		= 0b00010000
.EQU FEEDBACK_DATA_EP	= 0b00100000



; standard control endpoint request types
.EQU GET_STATUS			= 0x00
.EQU CLEAR_FEATURE		= 0x01
.EQU SET_FEATURE		= 0x03
.EQU SET_ADDRESS		= 0x05
.EQU GET_DESCRIPTOR		= 0x06
.EQU SET_DESCRIPTOR		= 0x07
.EQU GET_CONFIGURATION	= 0x08
.EQU SET_CONFIGURATION	= 0x09
.EQU GET_INTERFACE		= 0x0A
.EQU SET_INTERFACE		= 0x0B
.EQU SYNCH_FRAME		= 0x12
; HID (human interface device)
.EQU GET_REPORT			= 0x01
.EQU GET_IDLE			= 0x02
.EQU GET_PROTOCOL		= 0x03
.EQU SET_REPORT			= 0x09
.EQU SET_IDLE			= 0x0A
.EQU SET_PROTOCOL		= 0x0B
; CDC (communication class device)
.EQU SEND_ENCAPSULATED_COMMAND		= 0x00
.EQU GET_ENCAPSULATED_RESPONSE		= 0x01
.EQU SET_LINE_CODING				= 0x20
.EQU GET_LINE_CODING				= 0x21
.EQU SET_CONTROL_LINE_STATE			= 0x22
.EQU SEND_BREAK						= 0x23
; USB Mass Storage Class Bulk-Only (BBB) Transport
.EQU Get_Max_LUN		= 0xFE
.EQU GML				= 0xFE
.EQU BOMSR				= 0xFF

; Descriptors
.EQU DEVICE_DESCRIPTOR				= 0x01
.EQU CONFIG_DESCRIPTOR				= 0x02
.EQU STRING_DESCRIPTOR				= 0x03
.EQU INTERFACE_DESCRIPTOR			= 0x04
.EQU ENDPOINT_DESCRIPTOR			= 0x05
.EQU DEVICE_QUALIFIER_DESCRIPTOR	= 0x06
.EQU OTHER_SPEED_DESCRIPTOR			= 0x07
.EQU HID_DESCRIPTOR					= 0x21
.EQU REPORT_DESCRIPTOR				= 0x22
.EQU PHYSICAL_DESCRIPTOR			= 0x23

; Request Type
.EQU STANDARDREQUEST	= 0b00000000
.EQU CLASSREQUEST		= 0b00100000
.EQU USERREQUEST		= 0b01000000

; Recipient
.EQU RequestType_DEVICE			= 0
.EQU RequestType_INTERFACE		= 1
.EQU RequestType_ENDPOINT		= 2
.EQU RequestType_OTHER			= 3



.IFNDEF USB_BASE
	.SET USB_BASE = 0x04C0 ;USB_CTRL
.ENDIF

.IFNDEF USB_EPPTRL
	.SET USB_EPPTRL = 0x04C6 ;USB_EPPTRL
.ENDIF

.IFNDEF USB_EPPTRH
	.SET USB_EPPTRH = 0x04C7 ;USB_EPPTRH
.ENDIF

.IFNDEF CLK_BASE
	.SET CLK_BASE = 0x0040 ;DFLLRC32M_CTRL
.ENDIF

 .IFNDEF OCR_BASE
	.SET OCR_BASE = 0x0050 ;DFLLRC32M_CTRL
.ENDIF

.IFNDEF DFLLRC32M_BASE
	.SET DFLLRC32M_BASE = 0x0060 ;DFLLRC32M_CTRL
.ENDIF

.SET USB_ENABLE_SOF = 0

.SET USBCAL0 = 0x1A
.SET USBCAL1 = 0x1B

.SET USBCOMP1 = 0x1B
.SET USBCOMP2 = 0xB7

.SET USB_LOW_SPEED	= (0<<6)
.SET USB_FULL_SPEED	= (1<<6)

.macro USB_ATTACH
	LDS R16, USB_CTRLB
	SBR R16, USB_ATTACH_bm
	STS USB_CTRLB, R16
.endm

.macro USB_DETACH
	LDS R16, USB_CTRLB
	CBR R16, USB_ATTACH_bm
	STS USB_CTRLB, R16
.endm

.macro USB_SET_GNACK
	PUSH R16
	LDS R16, USB_CTRLB
	SBR R16, USB_GNACK_bm
	STS USB_CTRLB, R16
	POP R16
.endm

.macro USB_CLEAR_GNACK
	PUSH R16
	LDS R16, USB_CTRLB
	CBR R16, USB_GNACK_bm
	STS USB_CTRLB, R16
	POP R16
.endm

.macro USB_SET_RWAKEUP
	PUSH R16
	LDS R16, USB_CTRLB
	SBR R16, USB_RWAKEUP_bm
	STS USB_CTRLB, R16
	POP R16
.endm

.macro USB_CLEAR_RWAKEUP
	PUSH R16
	LDS R16, USB_CTRLB
	CBR R16, USB_RWAKEUP_bm
	STS USB_CTRLB, R16
	POP R16
.endm

.SET EP_DISABLE		= (0b00<<6)
.SET EP_CONTROL		= (0b01<<6)
.SET EP_BULK		= (0b10<<6)
.SET EP_INTERRUPT	= (0b10<<6)
.SET EP_ISOCHRONOUS = (0b11<<6)

.SET EPS_8		= 0b000
.SET EPS_16		= 0b001
.SET EPS_32		= 0b010
.SET EPS_64		= 0b011
.SET EPS_128	= 0b100
.SET EPS_256	= 0b101
.SET EPS_512	= 0b110
.SET EPS_1023	= 0b111

.INCLUDE "./drv/atxmega/usb_config.inc"

.IF USB_CDC_ENABLE == 1
	.INCLUDE "./drv/atxmega/usb_cdc.inc"
.ENDIF

;############################################################################################
;
;############################################################################################
USB_CLK_INIT:
PUSH R16
PUSH R24
	;USB RCOSC Calibration 
	LDI R16, NVM_PSR_RCOSC48M
	CALL NVM_READ_PSR 
	STS DFLLRC32M_CALB, R16 

	;DFLLRC32M COMP1 COMP2
	LDI R16, USBCOMP1
	STS DFLLRC32M_COMP1, R16
	LDI R16, USBCOMP2
	STS DFLLRC32M_COMP2, R16

	;32MHz oscillator reference selection
	LDS R16, OSC_DFLLCTRL
	SBRC R16, (0b11<<1)
	SBRS R16, OSC_RC32MCREF_USBSOF_gc
	STS OSC_DFLLCTRL, R16

	;Enable DFLL auto-calibration
	LDI R16, 0x01
	STS DFLLRC32M_CTRL, R16
	
	;Enable 32MHz oscillator
	LDS R24, OSC_CTRL
	SBR R24, OSC_RC32MEN_bm
	STS OSC_CTRL, R24
	CLOCK_EN_INT_32MHZ_WAIT:
		LDS R24, OSC_STATUS
		SBRS R24, OSC_RC32MRDY_bp
	RJMP CLOCK_EN_INT_32MHZ_WAIT

	LDI R16, (0b01<<1) | (1<<0)

	STS CLK_USBCTRL, R16
POP R24
POP R16
RET


;############################################################################################
;
;############################################################################################
USB_INIT:
PUSH R16
PUSH R17
PUSH R18	
	;USB Calibration 
	LDI R16, USBCAL0
	CALL NVM_READ_PSR 
	STS USB_CAL0, R16 
	LDI R16, USBCAL1
	CALL NVM_READ_PSR 
	STS USB_CAL1, R16 

	LDI R16, LOW(ENDPOINTS)
	LDI R17, HIGH(ENDPOINTS)
	STS USB_EPPTRL, R16
	STS USB_EPPTRH, R17
	
	;Reset VARS
	LDI R16, 0x00
	;Clear USB Addr
	STS USB_ADDR, R16
	;Clear USB EP Status	
	
	;EP0_OUT Setup
	LDI R16, 0x00
	LDI R17, EP_CONTROL
	LDI XL, LOW(USB_EP_SETUP_BUFFER)
	LDI XH, HIGH(USB_EP_SETUP_BUFFER)
	LDI ZL, LOW(EP0_SIZE)
	LDI ZH, HIGH(EP0_SIZE)
	CALL USB_EP_SETUP ; R16 = EP_Nummer, R17 = ep_type, Z = ep_size, X = ep_Buffer
	
	;EP0_IN Setup
	LDI R16, 0x80
	RCALL USB_EP_SETUP ; R16 = EP_Nummer, R17 = ep_type, Z = ep_size, X = ep_Buffer
	
	;CTRLA Config and Enable
	LDI R16, USB_ENABLE_bm | (USB_MAX_EPS<<0);
	.IF USB_ENABLE_FULL_SPEED == 1
		SBR R16, USB_SPEED_bm
	.ENDIF
	.IF USB_FIFO_ENABLE == 1
		SBR R16, USB_FIFOEN_bm
	.ENDIF
	.IF USB_STORE_FRAME_NUM == 1
		SBR R16, USB_STFRNUM_bm
	.ENDIF
	STS USB_CTRLA, R16

	;CTRLB
	CLR R16
	.IF USB_PULL_DURING_RESET == 1
		SBR R16, USB_PULLRST_bm
	.ENDIF
	STS USB_CTRLB, R16

	;Set USB_INTCTRLA
	LDI R16, (USB_INTLVL_MED_gc)
	.IF USB_ENABLE_SOFIE == 1
		SBR R16, USB_SOFIE_bm
	.ENDIF
	.IF USB_ENABLE_BUSEVIE == 1
		SBR R16, USB_BUSEVIE_bm
	.ENDIF
	.IF USB_ENABLE_BUSERRIE == 1
		SBR R16, USB_BUSERRIE_bm
	.ENDIF
	.IF USB_ENABLE_STALLIE == 1
		SBR R16, USB_STALLIE_bm
	.ENDIF
	STS USB_INTCTRLA, R16
	
	;Set USB_INTCTRLB
	LDI R16, (USB_TRNIE_bm | USB_SETUPIE_bm)
	STS USB_INTCTRLB, R16	
	
	;Reset Interup Flags
	LDI R16, 0xFF
	STS USB_INTFLAGSACLR, R16
	STS USB_INTFLAGSBCLR, R16

	; Set VARS
	LDI R16, 0x00
	STS USB_CONFIG, R16

	.IF USB_CDC_ENABLE == 1
		RCALL USB_CDC_INIT
	.ENDIF
POP R18
POP R17
POP R16
RET


;############################################################################################
;
;############################################################################################
USB_EP_SETUP: ; R16 = EP_Nummer, R17 = ep_type, Z = ep_size, X = ep_Buffer
PUSH R16
PUSH R17
PUSH R18
PUSH ZL
PUSH ZH
PUSH XL
PUSH XH
	RCALL USB_GET_EP_ADDR

	SBRS R16, 7
	CLR R16
	; Set BUSNACK0 on EP_IN
	SBRC R16, 7
	LDI R16, USB_EP_BUSNACK0_bm
	STD Y+0, R16

	CLR R16
	
	RCALL TO_USB_SIZE
	MOVW ZL:ZH, YL:YH
	ADIW ZL:ZH, 1	; USB_EP_CTRL
	XCH Z, R17		; ep_type
	LAS Z, R18		; ep_size

	STD Y+4, XL		; USB_EP_DATAPTRL
	STD Y+5, XH		; USB_EP_DATAPTRH
USB_EP_SETUP_END:
POP XH
POP XL
POP ZH
POP ZL
POP R18
POP R17
POP R16
RET


;############################################################################################
;
;############################################################################################
USB_GET_EP_ADDR:	; R16 = EP | OUT = Y
USB_GET_EP_ADDR_Y:
PUSH R0
PUSH R1
PUSH R17
	PUSH R16
	CBR R16, 0x80

	;Calc Endpoint Address
	LDI YL, LOW(ENDPOINTS)
	LDI YH, HIGH(ENDPOINTS)
	ANDI R16, 0b01111111
	LDI R17, 16
	MUL R16, R17
	ADD YL, R0
	ADC YH, R1

	POP R16
	SBRC R16, 7	;ADD 8 IF EP_IN
	ADIW Y, 8
POP R17
POP R1
POP R0
RET


;############################################################################################
;
;############################################################################################
USB_GET_EP_ADDR_Z:	; R16 = EP | OUT = Z
PUSH R0
PUSH R1
PUSH R17
	PUSH R16
	CBR R16, 0x80

	;Calc Endpoint Address
	LDI ZL, LOW(ENDPOINTS)
	LDI ZH, HIGH(ENDPOINTS)
	ANDI R16, 0b01111111
	LDI R17, 16
	MUL R16, R17
	ADD ZL, R0
	ADC ZH, R1

	POP R16
	SBRC R16, 7	;ADD 8 IF EP_IN
	ADIW Z, 8
POP R17
POP R1
POP R0
RET


;############################################################################################
;
;############################################################################################
USB_EP_PINGPONG_ENABLE: ; R16 = EP
	PUSH YL
	PUSH YH
	PUSH R16
		RCALL USB_GET_EP_ADDR
		LDD R16, Y+1 ; USB_EP_CTRL
		SBR R16, USB_EP_PINGPONG_bm
		STD Y+1, R16
	POP R16
	POP YH
	POP YL
RET


;############################################################################################
;
;############################################################################################
USB_EP_PINGPONG_DISABLE: ; R16 = EP
	PUSH YL
	PUSH YH
	PUSH R16
		RCALL USB_GET_EP_ADDR
		LDD R16, Y+1 ; USB_EP_CTRL
		CBR R16, USB_EP_PINGPONG_bm
		STD Y+1, R16
	POP R16
	POP YH
	POP YL
RET


;############################################################################################
;
;############################################################################################
USB_EP_MULTI_ENABLE: ; R16 = EP
	PUSH YL
	PUSH YH
	PUSH R16
		RCALL USB_GET_EP_ADDR
		LDD R16, Y+1 ; USB_EP_CTRL
		SBR R16, USB_EP_MULTIPKT_bm
		STD Y+1, R16
	POP R16
	POP YH
	POP YL
RET


;############################################################################################
;
;############################################################################################
USB_EP_MULTI_DISABLE:
	PUSH YL
	PUSH YH
	PUSH R16
		RCALL USB_GET_EP_ADDR
		LDD R16, Y+1 ; USB_EP_CTRL
		CBR R16, USB_EP_MULTIPKT_bm
		STD Y+1, R16
	POP R16
	POP YH
	POP YL
RET


;############################################################################################
;
;############################################################################################
USB_EP_CLEAR_STATUS: ; R16 = EP, R17 = MASK
	PUSH ZL
	PUSH ZH
	PUSH R17
			RCALL USB_GET_EP_ADDR_Z
			CBR R17, USB_EP_TOGGLE_bm
			LAC Z, R17
	POP R17
	POP ZH
	POP ZL
RET


;############################################################################################
;
;############################################################################################
USB_EP_SET_STATUS: ; R16 = EP, R17 = MASK
	PUSH YL
	PUSH YH
	PUSH R17
			RCALL USB_GET_EP_ADDR
			STD Y+0, R17
	POP R17
	POP YH
	POP YL
RET


;############################################################################################
;
;############################################################################################
USB_EP_GET_STATUS: ; R16 = EP | RETURN R17
	PUSH YL
	PUSH YH
		RCALL USB_GET_EP_ADDR
		LDD R17, Y+0 ;STATUS
	USB_EP_GET_STATUS_END:
	POP YH
	POP YL
RET


;############################################################################################
;
;############################################################################################
USB_EP_SET_DATAPTR: ; R16 = EP | Z = Buffer
	PUSH YL
	PUSH YH
		RCALL USB_GET_EP_ADDR
		STD Y+4, ZL ;DATAPTRL
		STD Y+5, ZH ;DATAPTRh
	USB_EP_SET_DATAPTR_END:
	POP YH
	POP YL
RET


;############################################################################################
;
;############################################################################################
USB_EP_GET_DATAPTR: ; R16 = EP | RETURN Z
	PUSH YL
	PUSH YH
		RCALL USB_GET_EP_ADDR
		LDD ZL, Y+4 ;DATAPTRL
		LDD ZH, Y+5 ;DATAPTRh
	USB_EP_GET_DATAPTR_END:
	POP YH
	POP YL
RET


;############################################################################################
;
;############################################################################################
USB_EP_SET_CNT: ; R16 = EP | Z = CNT
	PUSH YL
	PUSH YH
		RCALL USB_GET_EP_ADDR
		ANDI ZL, LOW(0b0000001111111111)
		ANDI ZH, HIGH(0b0000001111111111)
		STD Y+2, ZL ;DATAPTRL
		STD Y+3, ZH ;DATAPTRh
	USB_EP_SET_CNT_END:
	POP YH
	POP YL
RET


;############################################################################################
;
;############################################################################################
USB_EP_GET_CNT: ; R16 = EP | RETURN Z
	PUSH YL
	PUSH YH
		RCALL USB_GET_EP_ADDR
		LDD ZL, Y+2 ;DATAPTRL
		LDD ZH, Y+3 ;DATAPTRh
	USB_EP_GET_CNT_END:
	POP YH
	POP YL
RET


;############################################################################################
;
;############################################################################################
USB_EP_SET_AUXDATA: ; R16 = EP | Z = AUXDATA
	PUSH YL
	PUSH YH
		RCALL USB_GET_EP_ADDR
		STD Y+6, ZL ;AUXDATAL
		STD Y+7, ZH ;AUXDATAH
	USB_EP_SET_AUXDATA_END:
	POP YH
	POP YL
RET


;############################################################################################
;
;############################################################################################
USB_EP_GET_AUXDATA: ; R16 = EP | RETURN Z
	PUSH YL
	PUSH YH
		RCALL USB_GET_EP_ADDR
		LDD ZL, Y+6 ;AUXDATAL
		LDD ZH, Y+7 ;AUXDATAH
	USB_EP_GET_AUXDATA_END:
	POP YH
	POP YL
RET


;############################################################################################
;
;############################################################################################
USB_EP_SET_CTRL: ; R16 = EP | R17 = CTRL
	PUSH YL
	PUSH YH
		RCALL USB_GET_EP_ADDR
		STD Y+1, R17 ;CTRL
	USB_EP_SET_CTRL_END:
	POP YH
	POP YL
RET


;############################################################################################
;
;############################################################################################
USB_EP_GET_CTRL: ; R16 = EP | RETURN R17
	PUSH YL
	PUSH YH
		RCALL USB_GET_EP_ADDR
		LDD R17, Y+1 ;CTRL
	USB_EP_GET_CTRL_END:
	POP YH
	POP YL
RET


;############################################################################################
;
;############################################################################################
USB_EP0_SEND_DESCRIPTOR:	; Z = Pointer Descriptor | X = Descriptor Size 
PUSH XL
PUSH XH
PUSH YL
PUSH YH
PUSH ZL
PUSH ZH
PUSH R16
PUSH R17
PUSH R18
PUSH R19
PUSH R20
PUSH R21
;NVM CMD SAVE
LDS R18, NVM_BASE+0x0A
PUSH R18
;END NVM CMD SAVE

;NVM CMD SET
LDI R18, NVM_CMD_NO_OPERATION 
STS NVM_BASE+0x0A, R18
;END CMD SET

LDS R18, wLengthL
LDS R19, wLengthH

CP  XL, R18
CPC XH, R19
BRSH USB_EP0_SEND_DESCRIPTOR_SEND_SIZE
RJMP USB_EP0_SEND_DESCRIPTOR_SEND_SIZE_END
USB_EP0_SEND_DESCRIPTOR_SEND_SIZE:
	MOVW X, R19:R18
USB_EP0_SEND_DESCRIPTOR_SEND_SIZE_END:

MOVW R19:R18, XL:XH

;########################################	
;Alloc Ram
IN R16, CPU_SPL
IN R17, CPU_SPH

MOVW R21:R20, R17:R16
	
SUB R16, R18
SBC R17, R19
	
OUT CPU_SPL, R16
OUT CPU_SPH, R17
	
STS EP0_BUFFER_START+0, R16
STS EP0_BUFFER_START+1, R17

PUSH R20
PUSH R20
PUSH R21
;End Alloc Ram
;###########################################
	LDI R16, LOW(EP0_SIZE)
	LDI R17, HIGH(EP0_SIZE)

	USB_EP0_SEND_DESCRIPTOR_enable_multi:
		LDI R16, 0x80 
		RCALL USB_EP_MULTI_ENABLE ; R16 = EP		
	USB_EP0_SEND_DESCRIPTOR_enable_multi_end:

	PUSH XL
	PUSH XH	

	;########################################		
	;Load Descriptor to Buffer
	MOVW R19:R18, X
	LDS YL, EP0_BUFFER_START+0
	LDS YH, EP0_BUFFER_START+1

	CALL PGM_READ_BUFFER ; (Z) Pointer PGM, (Y) Pointer SRAM, (X) Read Bytes
	;End Load Descriptor to Buffer
	;########################################	
	
	;EP0 SEND
	LDS ZL, EP0_BUFFER_START+0
	LDS ZH, EP0_BUFFER_START+1
	LDI R16, 0x80
	RCALL USB_EP_SET_DATAPTR ; R16 = EP | Z = Buffer
	
	POP ZH	; POP X IN Z
	POP ZL	; POP X IN Z
	RCALL USB_EP0_SEND ; Z = Size
USB_EP0_SEND_DESCRIPTOR_END:
;########################################	
;Free Alloc Ram
LDS R16, EP0_BUFFER_START+0
LDS R17, EP0_BUFFER_START+1 

LDI R18, 0x03
LDI R19, 0x00

SUB R16, R18
SBC R17, R19

OUT CPU_SPL, R16
OUT CPU_SPH, R17

POP R17
POP R16

OUT CPU_SPL, R16
OUT CPU_SPH, R17
;End Free Alloc Ram
;########################################	

;NVM CMD RESET
POP R18
STS NVM_BASE+0x0A, R18
;END NVM CMD RESET
POP R21
POP R20
POP R19
POP R18
POP R17
POP R16
POP ZH
POP ZL
POP YH
POP YL
POP XH
POP XL
RET


;############################################################################################
;
;############################################################################################
USB_EP0_SEND: ; Z = Size
PUSH ZL
PUSH ZH
PUSH YL
PUSH YH
PUSH R16
PUSH R17
PUSH R18
PUSH R0
PUSH R1
	MOVW R1:R0, Z
	LDI R16, 0x80

	LDI ZL, 0x00
	LDI ZH, 0x00
	RCALL USB_EP_SET_AUXDATA ; R16 = EP | Z = AUXDATA

	; Test for Mutli
	RCALL USB_EP_GET_CTRL ;R16 = EP | RETURN R17
	SBRS R17, USB_EP_MULTIPKT_bp
	RJMP USB_EP0_SEND_MULTI_END
	;##########################################################
	; Multi Enabled
	;##########################################################
	USB_EP0_SEND_MULTI:
		MOVW Z, R1:R0
		RCALL USB_EP_SET_CNT ; R16 = EP | Z = CNT 

		LDI R16, 0x00 ; EP0 OUT
		LDI R17, USB_EP_TRNCOMPL0_bm | USB_EP_BUSNACK0_bm | USB_EP_BUSNACK1_bm | USB_EP_UNF_bm
		RCALL USB_EP_CLEAR_STATUS ; R16 = EP, R17 = MASK

		LDI R16, 0x80 ; EP0 IN
		LDI R17, (USB_EP_BUSNACK0_bm | USB_EP_TRNCOMPL0_bm | USB_EP_UNF_bm)
		RCALL USB_EP_CLEAR_STATUS ; R16 = EP, R17 = MASK

		USB_EP0_SEND_MULTI_WAIT_FINISH:
			LDI R16, 0x00  ; EP0 OUT
			RCALL USB_EP_GET_STATUS ; R16 = EP | RETURN R17
			SBRS R17, USB_EP_TRNCOMPL0_bp
			RJMP USB_EP0_SEND_MULTI_JMP_TO_END_END
			USB_EP0_SEND_MULTI_JMP_TO_END:
				RJMP USB_EP0_SEND_END
			USB_EP0_SEND_MULTI_JMP_TO_END_END:

			LDI R16, 0x80 ; EP0 IN
			RCALL USB_EP_GET_STATUS ; R16 = EP | RETURN R17
			SBRS R17, USB_EP_UNF_bp
			RJMP USB_EP0_SEND_CHECK_READY_END
			USB_EP0_SEND_CHECK_READY:
				LDI R16, 0x80 ; EP0 IN
				LDI R17, (USB_EP_BUSNACK0_bm | USB_EP_UNF_bm)
				RCALL USB_EP_CLEAR_STATUS ; R16 = EP, R17 = MASK
			USB_EP0_SEND_CHECK_READY_END:

			LDI R16, 0x80 ; EP0 IN
			RCALL USB_EP_GET_STATUS ; R16 = EP | RETURN R17
			SBRC R17, USB_EP_TRNCOMPL0_bp
			RJMP USB_EP0_SEND_MULTI_END
		RJMP USB_EP0_SEND_MULTI_WAIT_FINISH
		USB_EP0_SEND_MULTI_WAIT_FINISH_END:
	RJMP USB_EP0_SEND_END
	USB_EP0_SEND_MULTI_END:
	; Ende Multi Enabled
	;##########################################################



	;##########################################################
	; Multi Disabled
	;##########################################################




	; Ende Multi Disable
	;##########################################################
	

	;##########################################################
	;Send ZLP
	;##########################################################
	USB_EP0_SEND_ZLP:
	LDI R16, 0x80
	RCALL USB_EP_SEND_ZLP ;R16 = EP_IN
	;Ende Send ZLP
	;##########################################################
USB_EP0_SEND_END:
POP R1
POP R0
POP R18
POP R17
POP R16
POP YH
POP YL
POP ZH
POP ZL
RET


;############################################################################################
;
;############################################################################################
USB_EP_SEND_ZLP:	;R16 = EP_IN
PUSH R16
PUSH R17
	SBR R16, 0x80
	CLR ZL
	CLR ZH
	RCALL USB_EP_SET_CNT		; R16 = EP | Z = CNT 
	RCALL USB_EP_SET_AUXDATA ; R16 = EP | Z = AUXDATA
	LDI R17, (USB_EP_BUSNACK0_bm | USB_EP_UNF_bm)
	RCALL USB_EP_CLEAR_STATUS; R16 = EP, R17 = MASK
USB_EP_SEND_ZLP_END:
POP R17
POP R16
RET


;############################################################################################
;
;############################################################################################
USB_EP_STALL: ; R16 = EP
PUSH R17
PUSH ZL
PUSH ZH
	RCALL USB_GET_EP_ADDR_Z	; R16 = EP | OUT = Z
	ADIW Z, 1 ; Point Z to USB_EP CTRL
	LDI R17, USB_EP_STALL_bm
	LAS Z, R17
USB_EP_STALL_END:
POP ZH
POP ZL
POP R17
RET


;############################################################################################
;
;############################################################################################
USB_EP_CLEAR_STALL: ; R16 = EP
PUSH R16
PUSH R17
PUSH ZL
PUSH ZH
	RCALL USB_GET_EP_ADDR_Z	; R16 = EP | OUT = Z
	ADIW Z, 1 ; Point Z to USB_EP CTRL

	USB_EP_STALL_EP0_WAIT_1:
		RCALL USB_EP_GET_STATUS ; R16 = EP, R17 = MASK
		ANDI R17, USB_EP_STALLF_bm
		CPI R17, USB_EP_STALLF_bm
	BRNE USB_EP_STALL_EP0_WAIT_1

	LDI R17, USB_EP_STALL_bm 
	LAC Z, R17

	LDI R17, USB_EP_STALLF_bm | USB_EP_UNF_bm
	RCALL USB_EP_CLEAR_STATUS ; R16 = EP, R17 = MASK
USB_EP_CLEAR_STALL_END:
POP ZH
POP ZL
POP R17
POP R16
RET


;############################################################################################
;
;############################################################################################
TO_USB_SIZE:	; Z = SIZE [8, 16, 32, 64, 128, 256, 512, 1023] , OUT = R18
PUSH ZL
PUSH ZH
	CLR R18
	TO_USB_SIZE_COUTN_ZEROS:
		LSR ZH
		ROR	ZL
		INC R18
	BRCC TO_USB_SIZE_COUTN_ZEROS
	SUBI R18, 4
TO_USB_SIZE_END:
POP ZH
POP ZL
RET



;############################################################################################
;
;############################################################################################
.INCLUDE "./drv/atxmega/usb_interrupts.inc"
.INCLUDE "./drv/atxmega/usb_cdc_des.inc"
.INCLUDE "./drv/atxmega/usb_ep0_control.inc"
.INCLUDE "./drv/atxmega/usb_ep.inc"
;############################################################################################
;
;############################################################################################
 .endif