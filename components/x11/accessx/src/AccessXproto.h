/*
 * Copyright (c) 1993, 2004, Oracle and/or its affiliates. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice (including the next
 * paragraph) shall be included in all copies or substantial portions of the
 * Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */
/************************************************************************/
/*									*/
/*		Copyright 1987, 1988, 1989, 1990, 1991, 1992, 1993	*/
/*		by Digital Equipment Corp., Maynard, MA			*/
/*									*/
/*	Permission to use, copy, modify, and distribute this software	*/
/*	and its documentation for any purpose and without fee is hereby	*/
/*	granted, provided that the above copyright notice appear in all	*/
/*	copies and that both that copyright notice and this permission 	*/
/*	notice appear in supporting documentation, and that the name of	*/
/*	Digital not be used in advertising or publicity pertaining to	*/
/*	distribution of the software without specific, written prior 	*/
/*	permission.  							*/
/*									*/
/*	DIGITAL DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE,	*/
/*	INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND 	*/
/*	FITNESS, IN NO EVENT SHALL DIGITAL BE LIABLE FOR ANY SPECIAL,	*/
/*	INDIRECT OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER 	*/
/*	RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN 	*/
/*	ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, 	*/
/*	ARISING OUT OF OR IN CONNECTION WITH THE USE OR PERFORMANCE 	*/
/*	OF THIS SOFTWARE.						*/
/*									*/
/************************************************************************/

/************************************************************************/
/*									*/
/* AccessXproto	   						        */
/* 									*/
/* 	This module provides the protocol definitions for the AccessX	*/
/*	server extension.						*/
/*									*/
/* Revision History:							*/
/*									*/
/*	11-Jun-1993	WDW & MEN					*/
/*			Develop sample implementation.			*/
/*									*/
/************************************************************************/
#ifndef ACCESSX_PROTO_H
#define ACCESSX_PROTO_H

#define AccessXExtName		"AccessX"
#define AccessXMajorVersion	1
#define AccessXMinorVersion	0
#define AccessXNumEvents	1
#define AccessXNumErrors	0

/* Extension request definitions.
 */
#define X_AccessXQueryVersion	0
#define X_AccessXSelectInput	1
#define X_AccessXQueryState	2
#define X_AccessXConfigure	3
#define X_AccessXGetMouseKeys	4
#define X_AccessXSetMouseKey	5

/************************************************************************
 *
 * xAccessXQueryVersionReq
 * xAccessXQueryVersionReply
 */
typedef struct
{
    CARD8  majorOpcode;			/* The major opcode for this ext*/
    CARD8  minorOpcode;			/* Always X_AccessXQueryVersion */
    CARD16 length B16;			/* Must be 1			*/
} xAccessXQueryVersionReq;

#define sz_xAccessXQueryVersionReq 4

typedef struct 
{
    CARD8  type;			/* Must be X_Reply		*/
    CARD8  pad1;			/* Unused			*/
    CARD16 sequenceNumber B16;		/* Last sequence number		*/
    CARD32 length B32;			/* Must be 0			*/
    CARD16 majorVersion B16;		/* Major version number		*/
    CARD16 minorVersion B16;		/* Minor version number		*/
    CARD32 pad2 B32;			/* Unused			*/
    CARD32 pad3 B32;			/* Unused			*/
    CARD32 pad4 B32;			/* Unused			*/
    CARD32 pad5 B32;			/* Unused			*/
    CARD32 pad6 B32;			/* Unused			*/
} xAccessXQueryVersionReply;

#define sz_xAccessXQueryVersionReply 32

/************************************************************************
 *
 * xAccessXSelectInputReq
 */
typedef struct
{
    CARD8  majorOpcode;			/* The major opcode for this ext*/
    CARD8  minorOpcode;			/* Always X_AccessXSelectInput  */
    CARD16 length B16;			/* Must be 2			*/
    BYTE   enable;			/* True = send events.		*/
    CARD8  pad1;			/* Unused			*/
    CARD16 pad2;			/* Unused			*/
} xAccessXSelectInputReq;

#define sz_xAccessXSelectInputReq 8
    
/************************************************************************
 *
 * xAccessXQueryStateReq
 * xAccessXQueryStateReply
 */
typedef struct
{
    CARD8  majorOpcode;			/* The major opcode for this ext*/
    CARD8  minorOpcode;			/* Always X_AccessXQueryState	*/
    CARD16 length B16;			/* Must be 1			*/
} xAccessXQueryStateReq;

#define sz_xAccessXQueryStateReq 4

typedef struct 
{
    CARD8  type;			/* Must be X_Reply		*/
    CARD8  pad1;			/* Unused			*/
    CARD16 sequenceNumber B16;		/* Last sequence number	        */
    CARD32 length B32;			/* Must be 2		        */
    CARD32 control B32;			/* State of AccessX Features    */
    CARD16 timeOutInterval B16;		/* Duration after which the 	*/
                                        /*  AccessX features should be	*/
                                        /*  turned off if there aren't 	*/
                                        /*  any input events.		*/
    CARD16 mouseKeysTimeToMax B16;	/* Time (in seconds)	        */
                                        /*  until we reach max speed.	*/
    CARD16 mouseKeysGain;		/* Pixels per mouse movement  	*/
                                        /*  when at maximum speed.	*/
    CARD16 mouseKeysInterval B16;	/* Time (in milliseconds)       */
                                        /*  between MouseKeys actions.	*/
    CARD8  mouseKeysCtrlMask;		/* Modifier mask used for magic */
                                        /*  sequence to turn on MouseKs */
    CARD8  mouseKeysCtrlKeyCode;        /* KeyCode used in conjunction  */
                                        /*  with mouseKeysCtrlMask.	*/
    CARD8  currentMouseButton;		/* Current Mouse Button		*/
    CARD8  latchedModifiers;		/* What modifiers are latched   */
    CARD8  lockedModifiers;		/* What modifiers are locked	*/
    CARD8  pad2;			/* Unused			*/
    CARD16 slowKeysDelay B16;           /* Time (in milliseconds) for a */
                                        /*  to be pressed before it is	*/
                                        /*  accepted as a real KeyPress.*/
    CARD16 debounceDelay B16;           /* Time (in milliseconds)	*/
                                        /*  between release and press	*/
                                        /*  of the same key before it 	*/
                                        /*  will be accepted.		*/
                                        /*  accepted as a real KeyPress.*/
    CARD16 repeatKeysDelay B16; 	/* Time (in milliseconds) before*/
                                        /*  a key begins to autorepeat.	*/
    CARD16 repeatKeysRate B16;		/* Time (in milliseconds) for 	*/
                                        /*  handling rate of repeat.	*/
    CARD16 pad3 B16;			/* Unused			*/
    CARD32 pad4 B32;			/* Unused			*/
} xAccessXQueryStateReply;

#define sz_xAccessXQueryStateReply 40

/************************************************************************
 *
 * xAccessXConfigureReq
 */
typedef struct
{
    CARD8  majorOpcode;			/* The major opcode for this ext*/
    CARD8  minorOpcode;			/* Always X_AccessXConfigure	*/
    CARD16 length B16;			/* Must be 8			*/
    CARD16 pad1 B16;			/* Unused			*/
    CARD16 mask B16;			/* Bitmap saying what fields	*/
                                        /*  to pay attention to.	*/
    CARD32 control B32;       		/* State of AccessX Features	*/
                                        /*  in the form of a bitmask.	*/
                                        /*  For example, is mouse keys  */
                                        /*  on, is sticky keys on?      */
    CARD16 timeOutInterval;		/* Duration after which the 	*/
                                        /*  AccessX features should be	*/
                                        /*  turned off if there aren't 	*/
                                        /*  any input events.		*/
    CARD16 mouseKeysTimeToMax;		/* Time (in seconds)	  	*/
                                        /*  until we reach max speed.	*/
    CARD16 mouseKeysGain;		/* Pixels per mouse movement  	*/
                                        /*  when at maximum speed.	*/
    CARD16 mouseKeysInterval;		/* Time (in milliseconds)  	*/
                                        /*  between MouseKeys actions.	*/
    CARD8  mouseKeysCtrlMask;		/* Modifier mask used for magic */
                                        /*  sequence to turn on MouseKs */
    CARD8  mouseKeysCtrlKeyCode;	/* KeyCode used in conjunction  */
                                        /*  with mouseKeysCtrlMask.	*/
    CARD8  currentMouseButton;		/* Current Mouse Button		*/
    CARD8  pad2 B16;			/* Unused			*/
    CARD16 slowKeysDelay;               /* Time (in milliseconds) for a	*/
                                        /*  to be pressed before it is	*/
                                        /*  accepted as a real KeyPress.*/
    CARD16 debounceDelay;               /* Time (in milliseconds)	*/
                                        /*  between release and press	*/
                                        /*  of the same key before it 	*/
                                        /*  will be accepted.		*/
                                        /*  accepted as a real KeyPress.*/
    CARD16 repeatKeysDelay;		/* Time (in milliseconds) before*/
                                        /*  a key begins to autorepeat.	*/
    CARD16 repeatKeysRate;		/* Time (in milliseconds) for 	*/
                                        /*  handling rate of repeat.	*/
} xAccessXConfigureReq;

#define sz_xAccessXConfigureReq	32

/************************************************************************
 *
 * xAccessXGetMouseKeysReq
 * xAccessXGetMouseKeysReply
 */
typedef struct
{
    CARD8  majorOpcode;			/* The major opcode for this ext*/
    CARD8  minorOpcode;			/* Always X_AccessXGetMouseKeys	*/
    CARD16 length B16;			/* Must be 1			*/
} xAccessXGetMouseKeysReq;

#define sz_xAccessXGetMouseKeysReq 4

typedef struct 
{
    CARD8  type;			/* Must be X_Reply		*/
    CARD8  pad1;			/* Unused			*/
    CARD16 sequenceNumber B16;		/* Last sequence number		*/
    CARD32 length B32;			/* Must be 0			*/
    CARD32 numKeys;			/* Number of keys in actions map*/
    CARD32 pad2 B32;			/* Unused			*/
    CARD32 pad3 B32;			/* Unused			*/
    CARD32 pad4 B32;			/* Unused			*/
    CARD32 pad5 B32;			/* Unused			*/
    CARD32 pad6 B32;			/* Unused			*/
} xAccessXGetMouseKeysReply;

#define sz_xAccessXGetMouseKeysReply 32

/************************************************************************
 *
 * xAccessXSetMouseKeyReq
 */
typedef struct
{
    CARD8  majorOpcode;			/* The major opcode for this ext*/
    CARD8  minorOpcode;			/* Always X_AccessXSelectInput  */
    CARD16 length B16;			/* Must be 2			*/
    CARD8  keyCode;			/* KeyCode to define.		*/
    CARD8  action;			/* MOVE_ACTION, DOWN_ACTION, etc*/
    INT8   info1;			/* button or deltax		*/
    INT8   info2;			/* how_many or deltay		*/
} xAccessXSetMouseKeyReq;

#define sz_xAccessXSetMouseKeyReq	8

/* Extension event definitions.  The AccessX extension has only one
 * X event, so it uses the "detail" field to distinguish between the
 * different AccessX events.
 */
#define X_AccessXStickyKeysOn		0
#define X_AccessXStickyKeysOff		1
#define X_AccessXMouseKeysOn		2
#define X_AccessXMouseKeysOff		3
#define X_AccessXKRGWarning		4
#define X_AccessXKRGOn			5
#define X_AccessXKRGOff			6
#define X_AccessXToggleKeysOn		7
#define X_AccessXToggleKeysOff		8
#define X_AccessXToggleKeyDown		9
#define X_AccessXToggleKeyUp		10
#define X_AccessXModifierLatch		11
#define X_AccessXModifierUnlatch	12
#define X_AccessXModifierLock		13
#define X_AccessXModifierUnlock		14
#define X_AccessXPressSlowKey		15
#define X_AccessXAcceptSlowKey		16
#define X_AccessXChangeCurrentButton	17
#define X_AccessXPressButton		18
#define X_AccessXReleaseButton		19
#define X_AccessXChangeGain		20

/************************************************************************
 *
 * xAccessXEvent
 * XAccessXEvent
 */
typedef struct 
{
    CARD8  type;
    CARD8  detail;
    CARD16 sequenceNumber B16;
    CARD8  keyOrButton;
    CARD8  modifier;
    CARD16 gain B16;
    CARD32 control B32;
    CARD32 pad1 B32;
    CARD32 pad2 B32;
    CARD32 pad3 B32;
    CARD32 pad4 B32;
    CARD32 pad5 B32;
} xAccessXEvent;

#define sz_xAccessXEvent 32

typedef struct 
{
    int type;
    unsigned long serial;
    Bool send_event;
    Display *display;
    CARD8  detail;
    CARD8  keyOrButton;
    CARD8  modifier;
    CARD32 control;
    CARD16 gain;
    CARD8  pad[10];
} XAccessXEvent;

#endif /* ACCESSX_PROTO_H */
