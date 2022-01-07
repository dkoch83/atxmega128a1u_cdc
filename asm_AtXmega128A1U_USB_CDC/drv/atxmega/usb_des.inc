/*
 * usb_des.inc
 *
 *  Created: 12.01.2016 19:32:29
 *   Author: Dominik Koch
 */ 
 .ifndef usb_des_include
.set usb_des_include = 1

.EQU EP0_SIZE	= 8
.EQU EP1_SIZE	= 0
.EQU EP2_SIZE	= 32
.EQU EP3_SIZE	= 32

.CSEG
;##################################################################################
DEV_DES:
.DB	0x12,			/* bLength */ \
	0x01			/* bDescriptorType */
.DB	0x00, 0x02		/* bcdUSB */
.DB	0xFF,			/* bDeviceClass */ \
	0x00			;/* bDeviceSubclass */
.DB	0x00, 			/* bDeviceProtocol */ \
	EP0_SIZE		;/* bMaxPacketSize0 */ 
.DB	0xEB, 0x03		;/* Vendor-ID. */
.DB	0x06, 0x21		;/* Geräte-ID. */
.DB	0x00, 0x02		;/* Releasenummer des Geräts in BCD-Form. */
.DB	0x01,			/* ID des Stringdescriptors, der den Herstellernamen angibt. */ \
	0x02			/* ID des Stringdescriptors, der den Gerätenamen angibt. */ 
.DB	0x03,			/* ID des Stringdescriptors, der die Seriennummer angibt. */ \
	0x01			/* Anzahl der möglichen Konfigurationen. */
DEV_DES_END:
;##################################################################################
CONF_DES:
.DB	9,				/* bLength */ \
	2				/* bDescriptorType */
.DB	32, 0x00		/* wTotalLength */ \
.DB	0x01,			/* bNumInterfaces */ \
	0x01			/* bConfigurationValue */
.DB	0x00,			/* iConfiguration */ \
	0x80			/* bmAttributes */
.DB	0x64,			/* bMaxPower */ \
	/** Interfacedescriptor **/ \
	9				/* bLength */
.DB	4,				/* bDescriptorType */ \
	0x00			/* bInterfaceNumber */
.DB	0x00,			/* bAlternateSetting */ \
	0x02			/* bNumEndpoints */
.DB	0xFF,			/* bInterfaceClass */ \
	0x00			/* bInterfaceSubClass */
.DB	0x00,			/* bInterfaceProtocol */ \
	0x00			/* iInterface */
	;/** Endpunktdescriptor 3**/
.DB	7,				/* bLength */ \
	5				/* bDescriptorType */
.DB	0x83,			/* bEndpointAddress */ \
	0x02			/* bmAttributes */
.DB	EP3_SIZE, 0x00	/* wMaxPacketSize */
.DB	0x00,			/* bInterval 0x0A */ \
	/** Endpunktdescriptor 2**/ \
	7				/* bLength */
.DB	5,				/* bDescriptorType */ \
	0x02			/* bEndpointAddress */
.DB	0x02,			/* bmAttributes */ \
	EP2_SIZE, 0x00,	/* wMaxPacketSize */ \
	0x00			/* bInterval */
CONF_DES_END:
;##################################################################################
.SET LANG_DES_LEN = ((1*2)+2)
LANG_DES:
.DB	LANG_DES_LEN, 0x03
.DB	0x07,0x04 ;LANGID = 0x0407 = German
LANG_DES_END:
;##################################################################################
.SET STRING_DES_1_LEN = (10*2)+2
STRING_DES_1:
.DB	STRING_DES_1_LEN, 0x03
.DB	'A',0,'T',0,'M',0,'E',0,'L',0,' ',0,'C',0,'O',0,'R',0,'P',0
STRING_DES_1_END:
;##################################################################################
.SET STRING_DES_2_LEN = (12*2)+2
STRING_DES_2:
.DB STRING_DES_2_LEN, 0x03
.DB 'S',0,'T',0,'K',0,'6',0,'0',0,'0',0,' ',0,'C',0,'L',0,'O',0,'N',0,'E',0
STRING_DES_2_END:
;##################################################################################
.SET STRING_DES_3_LEN = (4*2)+2
STRING_DES_3:
.DB STRING_DES_3_LEN, 0x03
.DB '0',0,'0',0,'0',0,'1',0
STRING_DES_3_END:



.endif ;usb_des_include