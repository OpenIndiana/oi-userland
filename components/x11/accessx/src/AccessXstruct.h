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
/* AccessXstruct   						        */
/* 									*/
/* 	This module defines structures private to the server extension	*/
/*									*/
/* Revision History:							*/
/*									*/
/*	11-Jun-1993	WDW & MEN					*/
/*			Develop sample implementation.			*/
/*									*/
/************************************************************************/
#include <resource.h>
#ifndef ACCESSX_STRUCT_H
#define ACCESSX_STRUCT_H

/************************************************************************
 *
 * AccessXTime     - needed because GetTimeInMillis returns different
 *		      types depending upon the processor.
 */
#if LONG_BIT == 64
typedef int AccessXTime;
#else
typedef long AccessXTime;
#endif

/************************************************************************
 *
 * AccessXInfo - used by the extension to keep track of everything.
 *
 */
typedef struct _AccessXInfo
{
    int		 majorOpcode;		/* Major Opcode for extension.	*/
    ClientPtr	 currentClient;		/* Client asking for events.	*/
                                        /*  Only one client is allowed  */
                                        /*  at a time.			*/
    XID		 currentClientID;	/* FakeID for currentClient	*/
    RESTYPE	 accessXResourceType;	/* Resource type to associate	*/
                                        /*  with clients.		*/
    int		 accessXEventType;	/* Number to associate with the	*/
                                        /*  one and only event that the	*/
                                        /*  extension will send.	*/
    CARD32       control;       	/* State of AccessX Features	*/
                                        /*  in the form of a bitmask.	*/
                                        /*  For example, is mouse keys  */
                                        /*  on, is sticky keys on?      */
    CARD16	 timeOutInterval;	/* Duration (in seconds) after	*/
                                        /*  which the AccessX features  */
                                        /*  should be turned off if     */
                                        /*  there aren't any input evts.*/
                                        /*  mouse actions.		*/
    CARD16	 mouseKeysTimeToMax;	/* Time (in seconds)    	*/
                                        /*  until we reach max speed.	*/
    CARD16 	 mouseKeysGain;		/* Pixels per mouse movement  	*/
                                        /*  when at maximum speed.	*/
    CARD16	 mouseKeysInterval;	/* Time (in milliseconds)  	*/
                                        /*  between MouseKeys actions.	*/
    CARD8  	 mouseKeysCtrlMask;	/* Modifier mask used for magic */
                                        /*  sequence to turn on MouseKs */
    CARD8  	 mouseKeysCtrlKeyCode;	/* KeyCode used in conjunction  */
                                        /*  with mouseKeysCtrlMask.	*/
    CARD8	 currentMouseButton;	/* What button will be used for */
    CARD8	 latchedModifiers;	/* Bit mask saying what mods	*/
                                        /*  are latched.		*/
    KeyCode	 latchTable[8];		/* KeyCodes which represent 	*/
                                        /*  what modifiers are latched	*/
    CARD8	 lockedModifiers;	/* Bit mask saying what mods	*/
                                        /*  are locked.			*/
    KeyCode	 lockTable[8];		/* KeyCodes which represent 	*/
                                        /*  what modifiers are locked	*/
    CARD16	 slowKeysDelay;         /* Time (in milliseconds) for a	*/
                                        /*  to be pressed before it is	*/
                                        /*  accepted as a real KeyPress.*/
    CARD16	 debounceDelay;         /* Time (in milliseconds)	*/
                                        /*  between release and press	*/
                                        /*  of the same key before it 	*/
                                        /*  will be accepted.		*/
                                        /*  accepted as a real KeyPress.*/
    CARD16	 repeatKeysDelay;	/* Time (in milliseconds) before*/
                                        /*  a key begins to autorepeat.	*/
    CARD16	 repeatKeysRate;	/* Time (in milliseconds) for 	*/
                                        /*  handling rate of repeat.	*/
    KeyCode	 repeatKey;		/* Key that is autorepeating.	*/
    Bool	 savedAutoRepeat;	/* Autorepeat mode saved when	*/
	                                /*   KRG is turned on.		*/
    unsigned char savedAutoRepeats[32]; /* AutoRepeats field saved when */
                                        /*   mouseKeys is turned on.    */
    CARD16	 state;			/* Bitmask saying what is going */
                                        /*  on right now.  For example, */
                                        /*  is the mouse moving, or is  */
                                        /*  the KRG hot key being held? */
    KeyCode	 currentKeyCode;	/* KeyCode of the key currently */
                                        /*  being pressed by the user.	*/
    CARD8	 currentModifier;	/* Bitmask saying if the current*/
                                        /*  key is modifier and what	*/
                                        /*  modifier it is.		*/
    AccessXTime	 timeKeyPressed;	/* The time the current key was */
                                        /*  pressed.			*/
    AccessXTime	 timeKeyReleased;	/* The time the current key was */
                                        /*  released.			*/
    CARD8	 physicalModifiers;	/* Bitmask which says what mods	*/
                                        /*  are physically down.	*/
    CARD8	 shiftKeyCount;		/* Number of times the right	*/
                                        /*  shift key has been pressed  */
                                        /*  in a row.			*/
    KeyCode	 lastKeyPressed;	/* KeyCode of the last key	*/
                                        /*  pressed by the user.	*/
    CARD8	 lastModPressed;	/* Bit which says which was the	*/
                                        /*  last modifier pressed.	*/
    KeyCode	 previousKeyCode;       /* KeyCode of the key previously*/
                                        /*  acted upon by the user.	*/
    KeyCode	 ignoreKeyCode;       	/* KeyCode of key to ignore	*/
                                        /*  when it is released.	*/
    AccessXTime	 timeOutTime;		/* Time disabling AccessX.	*/
    AccessXTime	 krgHoldTime;		/* Time for holding KRG hot key.*/
    AccessXTime	 slowKeysTime;		/* Time to do SlowKeys action.	*/
    AccessXTime	 repeatKeysTime;	/* Time to do RepeatKeys action	*/
    AccessXTime	 mouseKeysTime;		/* Time to do MouseKeys action.	*/
    int		 mouseAccel;		/* Used for MouseKeys accel.	*/
    int		 mouseCounter;		/*   "                  "       */
    int		 accelPass;		/*   "                  "       */
    int		 accelStep;		/*   "                  "       */
    AccessXTime	 timeStep;		/*   "                  "       */
    AccessXMouseKeysRec *mouseKeysActions; /* What keys act as MouseKeys*/
} AccessXInfo;

#endif /* ACCESSX_STRUCT_HH */
