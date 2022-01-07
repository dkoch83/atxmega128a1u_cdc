;/*
; * delay.inc
; *
; *  Created: 15.05.2014 22:57:38
; *   Author: Dominik
; */
.ifndef delay_include
.set delay_include = 1

;.set F_MCU		= 8000000

; delay_ns ns,clk,rx		max 8bit
; delay_us us				max 16bit
; delay_ms ms				max 16bit
; delay_s s					max 8bit 


 ; delay_ns ns,clk	max 8bit
 .macro delay_ns
	.set clk_time_ns	= (1000000000 / F_MCU)		;ns pro Clk 
	.set ns_delay_clk = ((@0 + clk_time_ns - 1) / clk_time_ns - @1)
	.if (ns_delay_clk > (255 * 3 + 2))
		.error "MACRO delay_ns - zu viele clk"
	.else
		.if (ns_delay_clk > 6)
			.set loop_count = (ns_delay_clk / 3)
			ldi R25, loop_count
			dec	R25
			brne pc-1
			.set ns_delay_clk = (ns_delay_clk - (loop_count * 3))
		.endif
		.if (ns_delay_clk > 0)
			.if (ns_delay_clk & 4)
				rjmp  pc+1
				rjmp  pc+1
			.endif
			.if (ns_delay_clk & 2)
				rjmp  pc+1
			.endif
			.if (ns_delay_clk & 1)
				nop
			.endif
		.endif
	.endif
 .endmacro

 ; delay_us us		max 16bit
  .macro delay_us
	.set loop_count_us = (@0)
	.if (loop_count_us <= 255)
		push ZL										; save ZL
		push R16
		ldi ZL, LOW(loop_count_us)
		DELAY_US_LOOP:
			delay_ns 1000, 3
			dec ZL
			brne DELAY_US_LOOP
		pop R16
		pop ZL										; restore ZL
	.endif
	.if (loop_count_us > 255)
		push ZL
		push ZH
		push R16
		ldi ZL, LOW(loop_count_us)
		ldi ZH, HIGH(loop_count_us)
		DELAY_US_LOOP:
			delay_ns 1000, 4, R16
			sbiw Z,1
			brne DELAY_US_LOOP
		pop R16
		pop ZH
		pop ZL
	.endif
 .endmacro

 ; delay_ms ms		max 16bit
 .macro delay_ms
	.set loop_count_ms = (@0)
	.if (loop_count_ms <= 255)
		push ZL										; Save ZL
		ldi ZL, loop_count_ms
		DELAY_MS_LOOP:
			delay_us 1000
			dec ZL
			brne DELAY_MS_LOOP
		pop ZL										; restore ZL
	.endif

	.if (loop_count_ms > 255)
		push ZL										; save ZL
		push ZH										; save ZH
		ldi ZL, LOW(loop_count_ms)
		ldi ZH, HIGH(loop_count_ms)
		DELAY_MS_LOOP:
			delay_us 1000
			sbiw Z,1
			brne DELAY_MS_LOOP
		pop ZH
		pop ZL
	.endif
 .endmacro

 ; delay_s s		max 8bit 
 .macro delay_s
	.set loop_count_s = (@0)
	.if (loop_count_s <= 255)
		push ZL										; save ZL
		ldi ZL, LOW(loop_count_s)
			DELAY_S_LOOP:
				delay_ms 1000
				dec ZL
				brne DELAY_S_LOOP
		pop ZL										; restore ZL
	.endif
 .endmacro

.endif ;delay_include