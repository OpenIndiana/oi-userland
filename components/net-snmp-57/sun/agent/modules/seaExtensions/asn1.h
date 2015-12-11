/*
 * Copyright (c) 2003, 2011, Oracle and/or its affiliates. All rights reserved.
 *
 * U.S. Government Rights - Commercial software. Government users are subject
 * to the Sun Microsystems, Inc. standard license agreement and applicable
 * provisions of the FAR and its supplements.
 *
 *
 * This distribution may include materials developed by third parties. Sun,
 * Sun Microsystems, the Sun logo and Solaris are trademarks or registered
 * trademarks of Sun Microsystems, Inc. in the U.S. and other countries.
 *
 */

#if !defined(lint) && !defined(NOID)
#pragma ident	"@(#)asn1.h	2.17	00/07/17 SMI"
#endif

/*
** Sun considers its source code as an unpublished, proprietary trade 
** secret, and it is available only under strict license provisions.  
** This copyright notice is placed here only to protect Sun in the event
** the source is deemed a published work.  Disassembly, decompilation, 
** or other means of reducing the object code to human readable form is 
** prohibited by the license agreement under which this code is provided
** to the user or company in possession of this copy.
** 
** RESTRICTED RIGHTS LEGEND: Use, duplication, or disclosure by the 
** Government is subject to restrictions as set forth in subparagraph 
** (c)(1)(ii) of the Rights in Technical Data and Computer Software 
** clause at DFARS 52.227-7013 and in similar clauses in the FAR and 
** NASA FAR Supplement.
*/
/****************************************************************************
 *     Copyright (c) 1986, 1988  Epilogue Technology Corporation
 *     All rights reserved.
 *
 *     This is unpublished proprietary source code of Epilogue Technology
 *     Corporation.
 *
 *     The copyright notice above does not evidence any actual or intended
 *     publication of such source code.
 ****************************************************************************/

/* $Header: /net/bigblock.east/files5/SMA_CVS/sun/agent/modules/seaExtensions/asn1.h,v 1.3 2003/08/12 21:14:53 rr144420 Exp $	*/
/*
 * $Log: asn1.h,v $
 * Revision 1.3  2003/08/12 21:14:53  rr144420
 * 4895376 - correct Sun copyright statements. Cannot use (c), and must use Copyright Copyright in makefiles
 *
 * Revision 1.2  2003/08/08 15:39:52  pcarroll
 * 4895376 - The copyright statement in the demo* codes do not look right
 *
 * Revision 1.1  2003/07/28 17:59:15  dporter
 * 4892877 - Need SMA Agent to implement sun extensions found in SEA sun.mib
 *
 * 
 *    Rev 2.0   31 Mar 1990 15:11:26
 * Release 2.00
 * 
 *    Rev 1.1   14 Dec 1989 16:01:16
 * Added support for Borland Turbo C compiler
 * 
 *    Rev 1.0   12 Sep 1988 10:46:12
 * Initial revision.
*/

#if (!defined(asn1_inc))
#define asn1_inc

/**********************************************************************
 If necessary adjust the following to match the compiler being used.
 **********************************************************************/
typedef long		INT_32_T;
typedef unsigned long	UINT_32_T;
typedef short int	INT_16_T;
typedef unsigned short 	UINT_16_T;
typedef unsigned char	UINT_8_T;
typedef unsigned char	OCTET_T ;
	/* SNMP ASN.1 tags and lengths can always fit into 16 bits...	*/
typedef unsigned short 	ATVALUE_T;	/* ASN.1 type values		*/
typedef unsigned short 	ALENGTH_T;	/* ASN.1 contents field	lengths	*/
#define OCTETS_PER_INT32    (sizeof(INT_32_T)/sizeof(OCTET_T))
#define OCTETS_PER_INT16    (sizeof(INT_16_T)/sizeof(OCTET_T))

/* Allow the components of an object identifer to be either 16 or 32-bits */
/* 16-bit is default, define OIDC_32 to switch to 32-bits.		  */
#if defined(OIDC_32)
typedef	unsigned long	OIDC_T;
#else
typedef	unsigned short	OIDC_T;
#endif	/* OIDC_32 */

/* ASN.1 FLAGS (form and class), adjusted for position within an octet */
#define A_IDCF_MASK         0xE0        /* Mask for ID CLASS and FORM bits */
#define A_IDC_MASK          0xC0        /* Mask for ID CLASS bits */
#define A_IDF_MASK          0x20        /* Mask for ID FORM bit */
#define A_FLAG_MASK         0xE0
#define A_UNIVERSAL         0x00
#define A_APPLICATION       0x40
#define A_CONTEXT           0x80
#define A_PRIVATE           0xC0
#define A_PRIMITIVE         0x00
#define A_CONSTRUCTOR       0x20

#define A_DEFAULT_SCOPE     A_CONTEXT

/* ASN.1 basic types, all in UNIVERSAL scope */
#define A_NO_ID             0x00
#define A_BOOLEAN           0x01
#define A_INTEGER           0x02
#define A_BITSTRING         0x03
#define A_OCTETSTRING       0x04
#define A_NULL              0x05
#define A_OBJECTID	    0x06
#define A_SEQUENCE          0x10
#define A_SET               0x11

/* ASN.1 defined types, all based on OCTETSTRING */
#define A_NUMERICSTRING     0x12
#define A_PRINTABLESTRING   0x13
#define A_T61STRING         0x14
#define A_TELETEXSTRING     A_T61STRING
#define A_VIDEOTEXSTRING    0x15
#define A_IA5STRING         0x16
#define A_GRAPHICSTRING     0x19
#define A_VISIBLESTRING     0x1A
#define A_GENERALSTRING     0x1B

/* Other ASN.1 defined universal types */
#define A_GENERALIZEDTIME   0x18
#define A_UTCTIME           0x17
#define A_OBJECTDESCRIPTOR  0x07

/****************************************************************************

NAME:  A_SizeOfLength

PURPOSE:  Compute the number of octets needed to hold an ASN.1 length field.

PARAMETERS:
	    ALENGTH_T	The proposed length

RETURNS:    ALENGTH_T	The number of octets needed

RESTRICTIONS:  

BUGS:  
****************************************************************************/
#define A_SizeOfLength(S) ((ALENGTH_T)((S) <= 127 ? 1 : ((S) <= 255 ? 2 : 3)))

/****************************************************************************

NAME:  A_SizeOfType

PURPOSE:  Compute the number of octets needed to hold an ASN.1 type field

PARAMETERS:
	    ATVALUE_T		The proposed type (without CLASS & FORM bits)

RETURNS:    unsigned int	The number of octets needed

RESTRICTIONS:  

BUGS:  
****************************************************************************/
#define A_SizeOfType(V) ((unsigned int) ((V) <= 30 ? 1 : \
			 ((V) <= 127 ? 2 : ((V) <= 16383 ? 3 : 4))))


/****************************************************************************
A_SizeOfOctetString --	Return total size that an octet string would
			occupy when ASN.1 encoded (tag and length fields
			are NOT included)

Parameters:
        ALENGTH_T	The size of the string

Returns: ALENGTH_T  Number of octets the octet string would occupy if
		    in ASN.1 encoding, NOT including the type/length fields
		    of the outermost wrapper.  Since these routines only
		    generate non-constructor encodings, the length is
		    exactly that given.
****************************************************************************/
#define A_SizeOfOctetString(L)	((ALENGTH_T)(L))


/****************************************************************************
OBJECT IDENTIFIER
****************************************************************************/

/* The following structure is used to internally hold an object identifier */
/* Each component is limited in range from 0 to 64K-1.			   */

typedef	struct	OBJ_ID_S
	{
	int	num_components;	/* # of object id components	*/
				/* Note: this is the number of	*/
				/* components in the object id,	*/
				/* which is one more than the #	*/
				/* of subidentifiers in an	*/
				/* encoded object id.		*/
	OIDC_T	*component_list;
	} OBJ_ID_T;

#endif	/* asn1_inc */
