/*
 * Copyright (c) 1993, 2015, Oracle and/or its affiliates. All rights reserved.
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
/* AccessXlib	   						        */
/* 									*/
/* 	This module defines public structures for client access to the	*/
/*	AccessX server extension.					*/
/*									*/
/* Revision History:							*/
/*									*/
/*	11-Jun-1993	WDW & MEN					*/
/*			Develop sample implementation.			*/
/*									*/
/************************************************************************/
#ifndef ACCESSX_LIB_H
#define ACCESSX_LIB_H

#include "AccessXproto.h"

/************************************************************************
 *
 * AccessXStateRec - structure for setting/determining the AccessX state.
 *
 */
#define SET_CONTROL_MASK			(1 << 0)
#define SET_TIME_OUT_INTERVAL_MASK		(1 << 1)
#define SET_MOUSE_KEYS_TIME_TO_MAX_MASK		(1 << 2)
#define SET_MOUSE_KEYS_GAIN_MASK		(1 << 3)
#define SET_MOUSE_KEYS_INTERVAL_MASK  		(1 << 4)
#define SET_REPEAT_DELAY_MASK			(1 << 5)
#define SET_REPEAT_RATE_MASK			(1 << 6)
#define SET_SLOW_KEYS_DELAY_MASK		(1 << 7)
#define SET_DEBOUNCE_DELAY_MASK			(1 << 8)
#define SET_MOUSE_KEYS_CTRL_MASK		(1 << 9)

#define SET_CONTROL_MASK			(1 << 0)
#define SET_TIME_OUT_INTERVAL_MASK		(1 << 1)
#define SET_MOUSE_KEYS_TIME_TO_MAX_MASK		(1 << 2)
#define SET_MOUSE_KEYS_GAIN_MASK		(1 << 3)
#define SET_MOUSE_KEYS_INTERVAL_MASK  		(1 << 4)
#define SET_REPEAT_DELAY_MASK			(1 << 5)
#define SET_REPEAT_RATE_MASK			(1 << 6)
#define SET_SLOW_KEYS_DELAY_MASK		(1 << 7)
#define SET_DEBOUNCE_DELAY_MASK			(1 << 8)
#define SET_MOUSE_KEYS_CTRL_MASK		(1 << 9)
#define SET_CURRENT_MOUSE_BUTTON_MASK		(1 << 10)

#define ALLOW_ACCESSX_MASK		(1 << 0)
#define	STICKY_KEYS_MASK		(1 << 1)
#define	MOUSE_KEYS_MASK			(1 << 2)
#define TOGGLE_KEYS_MASK		(1 << 3)
#define	SLOW_KEYS_MASK			(1 << 4)
#define	BOUNCE_KEYS_MASK		(1 << 5)
#define REPEAT_KEYS_MASK		(1 << 6)
#define TWO_KEYS_MASK			(1 << 7)
#define TIME_OUT_MASK			(1 << 8)
#define NO_LOCK_ON_TWO_MASK		(1 << 9)
#define STICKY_ONOFF_SOUND_MASK		(1 << 10)
#define STICKY_MOD_SOUND_MASK		(1 << 11)
#define MOUSE_ONOFF_SOUND_MASK		(1 << 12)
#define TOGGLE_ONOFF_SOUND_MASK		(1 << 13)
#define KRG_ONOFF_SOUND_MASK		(1 << 14)
#define KRG_PRESS_SOUND_MASK		(1 << 15)
#define KRG_ACCEPT_SOUND_MASK		(1 << 16)

#define KRG_MASK			(SLOW_KEYS_MASK | \
					 BOUNCE_KEYS_MASK | \
					 REPEAT_KEYS_MASK)

#define ANY_OPTIONS_MASK		(STICKY_KEYS_MASK | \
					 MOUSE_KEYS_MASK | \
					 TOGGLE_KEYS_MASK | \
					 KRG_MASK)

typedef struct _AccessXStateRec
{
    CARD32 control B32;			/* State of AccessX Features	*/
    CARD16 timeOutInterval B16;		/* Duration after which the 	*/
                                        /*  AccessX features should be	*/
                                        /*  turned off if there aren't 	*/
                                        /*  any input events.		*/
    CARD16 mouseKeysTimeToMax B16;	/* Time (in seconds)	  	*/
                                        /*  until we reach max speed.	*/
    CARD16 mouseKeysGain;		/* Pixels per mouse movement  	*/
                                        /*  when at maximum speed.	*/
    CARD16 mouseKeysInterval B16;	/* Time (in milliseconds)  	*/
                                        /*  between MouseKeys actions.	*/
    CARD8  mouseKeysCtrlMask;		/* Modifier mask used for magic */
                                        /*  sequence to turn on MouseKs */
    CARD8  mouseKeysCtrlKeyCode;       	/* KeyCode used in conjunction  */
                                        /*  with mouseKeysCtrlMask.	*/
    CARD8  currentMouseButton;		/* Current Mouse Button		*/
    CARD8  latchedModifiers;		/* What modifiers are latched	*/
    CARD8  lockedModifiers;		/* What modifiers are locked	*/
    CARD16 slowKeysDelay B16;           /* Time (in milliseconds) for a	*/
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
} AccessXStateRec;

/************************************************************************
 *
 * AccessXClientContextRec - Structure for a client
 *
 */
typedef struct _AccessXClientContextRec
{
    CARD16	majorOpcode;
    CARD16	eventBase;
    CARD16	errorBase;
    void	(*eventHandler)(XAccessXEvent *);
} AccessXClientContextRec;

/************************************************************************
 *
 * AccessXMouseKeysRec - Table for holding actions for MouseKeys keys.
 *
 */
#define ACCESSX_NO_ACTION			0
#define ACCESSX_BTN_DOWN_ACTION			1
#define ACCESSX_BTN_UP_ACTION			2
#define ACCESSX_BTN_DOWN_UP_ACTION		3
#define ACCESSX_BTN_SELECT_ACTION		4
#define ACCESSX_CLICK_ACTION			5
#define ACCESSX_MOVE_ACCELERATED_ACTION		6
#define ACCESSX_MOVE_INCREMENTAL_ACTION		7
#define ACCESSX_TOGGLE_GAIN_ACTION		8
#define ACCESSX_MAX_ACTION			8

typedef struct _AccessXButtonRec
{
    CARD8	button;
    CARD8	how_many;
} AccessXButtonRec;

typedef struct _AccessXMovementRec
{
    INT8	deltax;
    INT8	deltay;
} AccessXMovementRec;

typedef struct _AccessXGainRec
{
    INT8	slow;
    INT8	fast;
} AccessXGainRec;

typedef struct _AccessXMouseKeysRec
{
    CARD8	action;

    union
    {
	AccessXButtonRec	btn;
	AccessXMovementRec	move;
	AccessXGainRec		gain;
    } u;

    CARD8	pad;
    
} AccessXMouseKeysRec;

#endif /* ACCESSX_LIB_H */


