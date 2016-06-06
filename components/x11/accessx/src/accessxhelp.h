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
/* AccessXHelp.h							*/
/************************************************************************/ 

/* The following define the number of lines in each of the help strings.
   These must be precisely defined by counting the lines in the 
   corresponding strings in order for the accessx help facility to work
   properly.
*/
#define NUM_GENERAL_HELP_LINES		(28)
#define NUM_STICKY_HELP_LINES		(19)
#define NUM_MOUSE_HELP_LINES		(28)
#define NUM_TOGGLE_HELP_LINES		(9)
#define NUM_REPEAT_HELP_LINES		(24)
#define NUM_SLOW_HELP_LINES		(23)
#define NUM_BOUNCE_HELP_LINES		(20)

/****************************************************************/
/*								*/
/* General Help String						*/
/*								*/
/****************************************************************/
static char *generalHelpString[] = { "General Help\n\n",
"This help text provides information about the accessx utility in general and\n",
"describes the general setting items on the user interface.\n\n",
"The AccessX utility was co-developed by Digital Equipment Corportation, The\n",
"Trace Research Center at the University of Wisconsin-Madison and by Sun\n",
"Microsystems Laboratories, Inc. The accessx utility will be a part of the X11\n",
"Windows systems version R6 and later.\n\n",
"The Main menu bar contains four pulldown menus: File, Status, Options and Help.\n",
"The File menu allows you to either load or save your current settings for future\n",
"use. The exit option allows you to gracefully exit the AccessX utility.\n\n",
"The Status menu allows you to pull up separate windows indicating the current\n",
"status of the Sticky Key modifier keys (i.e. whether they are latched or\n",
"locked) and the status of the Mouse Keys mouse buttons (i.e. whether they\n",
"are pressed or released).\n\n",
"The Help menu options allows you to get help on the various features of\n",
"AccessX.\n\n",
"Directly below the main menu bar are three general setting items. The first,\n",
"labelled 'Enable AccessX' allows you to turn off the entire utility. When\n",
"this box is unchecked the rest of the interface in greyed out to indicate that\n",
"AccessX in inactive. It also disables the keyboard invocation features.\n\n",
"The second checkbox item allows you to hear a beep when each individual\n",
"feature is toggled on or off.\n\n",
"The third item is a time out time. In environments where many users use\n",
"one machine, this allows you to tell the AccessX utility to clear your\n",
"user specific settings and turn off all of the features after a settable time\n",
"period of inactivity. When the 'Time Out' checkbox is check, then the features\n",
"will turn off according to the time currently set on the scale. The time\n",
"markings for the scale are labelled in minutes.\n" };


/****************************************************************/
/*								*/
/* Sticky Keys Help String					*/
/*								*/
/****************************************************************/
static char *stickyHelpString[] = {
"Sticky Keys\n\n",
"DESCRIPTION: Sticky Keys benefits users who type with only one finger and\n",
"             for users who use a mouth stick. The Sticky Keys feature allow\n",
"             you to latch and lock modifier keys. A latched modifier key\n",
"             will modify the next alpha-numeric key and a locked modifier\n",
"             key will modify all future alpha-numeric keys pressed until\n",
"             the modifier is unlocked. Pressing a modifier key once will\n",
"             latch that modifier. Pressing a modifier key twice in a row\n",
"             will lock that modifier.\n\n",
"ENABLING:    Users can turn Sticky Keys on and off in one of two ways.\n",
"             Clicking on the check box marked 'Sticky Keys' under the \n",
"             'Enable' panel will turn on and off Sticky Keys. Sticky Keys\n",
"             may also be turned on or off via the keyboard by pressing\n",
"             the left or right Shift key five times in a row.\n\n",
"FEATURES:    Sticky Keys has two user settable options that are located\n",
"             under the 'Sticky Keys' panel. The first check box allows\n",
"             users to hear a system beep when a modifier is latched. The\n",
"             second allows the user to turn the Sticky Keys feature off\n",
"             when two modifier keys a pressed simultaneously.\n\n\n" };   

/****************************************************************/
/*								*/
/* Mouse Keys Help String					*/
/*								*/
/****************************************************************/
static char *mouseHelpString[] = { 
"Mouse Keys\n\n",
"DESCRIPTION: Mouse Keys benefits users who have RSI or mouth stick users\n",
"             who are unable to control a mouse. Also CAD users who need\n",
"             pixel by pixel control of a mouse pointer benefit from Mouse\n",
"             Keys. The Mouse Keys feature turn the numeric keypad into a\n",
"             mouse control mechanism. The keys '1' through '4' and keys '6'\n",
"             through '9' are use for navigation of the mouse. The '5' key\n",
"             simulates a mouse button click; the Plus key simulates mouse\n",
"             button double click; the '0' key simulates a mouse button\n",
"             press; and the Period key simulates a mouse button release.\n",
"             These latter keys operate on a 'current' button which is set\n",
"             via keys specific to each vendor. Often these keys, which set\n",
"             the current mouse button, are located directly above the key\n",
"             pad.\n\n",
"ENABLING:    Mouse Keys may be turned on or off in one of two ways.\n",
"             Clicking the 'Mouse Keys' check box under the 'Enable' panel\n",
"             turns Mouse Keys on or off. Mouse Keys is also turned on or\n",
"             off via the keyboard. A vendor-specific three key combination\n",
"             is used.\n\n",
"FEATURES:    There are two user settable parameters which control the\n",
"             behavior of the mouse pointer. These two parameters are set\n",
"             via scales in the 'Mouse Keys' panel. The 'Maximum Pointer\n",
"             Speed' is displayed in Pixels/Second and the 'Time To Maximum\n",
"             Speed' is displayed in Seconds. When a user holds down one of\n",
"             the direction keys on the key pad, the mouse pointer moves in\n",
"             that direction eventually reaching the 'Maximum Pointer Speed'\n",
"             It takes the amount of time specified by 'Time To Maximum\n",
"             Speed' to reach the maximum speed.\n\n\n" };

/****************************************************************/
/*								*/
/* Toggle Keys Help String					*/
/*								*/
/****************************************************************/
static char *toggleHelpString[] = {
"Toggle Keys\n\n",
"DESCRIPTION: Toggle Keys benefits the visually impaired user who has\n",
"             difficulty seeing the small LED keyboard indicators. Toggle\n",
"             Keys beeps once when a toggle key (i.e the Caps Lock\n",
"             key, etc) is toggle 'on' and beeps twice when a toggle keys is\n",
"             toggled 'off'.\n\n",
"ENABLING:    Toggles Keys is turned on and off via the check box in the\n",
"             'Enable' panel.\n\n",
"FEATURES:    There are no additional user settable options for Toggle Keys.\n\n\n" };


/****************************************************************/
/*								*/
/* Repeat Keys Help String					*/
/*								*/
/****************************************************************/
static char *repeatHelpString[] = {
"Repeat Keys\n\n",
"DESCRIPTION: Users who have difficulty in removing their finger from\n",
"             pressed keys benefit from Repeat Keys. Repeat Keys allows\n",
"             users to control the key-repeating characteristics of the\n",
"             system's keyboard.\n\n",
"ENABLING:    Repeat Keys may be turned on or off in one of two ways. It\n",
"             may be turned on or off via the check box in the 'Enable'\n",
"             panel. It also may be turned off via the keyboard. Holding the\n",
"             left or right Shift key down for four seconds will turn Repeat\n",
"             Keys on or off. After holding the Shift Key for two seconds,\n",
"             the user will hear three warning beeps. Two seconds later,\n",
"             Repeat Keys will be turned on or off.\n\n",
"             Note that Slow Keys is also turned on or off when holding the\n",
"             the left or right Shift key for four seconds.\n\n",
"FEATURES:    Repeat Keys allows the user to set two parameters, a 'Delay\n",
"             Until Repeat' time displayed in seconds and a 'Repeat Rate'\n",
"             time displayed in Keys/Second. The 'Delay Until Repeat' time\n",
"             instructs the system to wait a certain number of seconds\n",
"             before repeating a pressed key. This time delay is measured\n",
"             after the first accepted key stroke. The 'Repeat Rate'\n",
"             parameters instructs the system to generate a certain number\n",
"             of keys each second once a key has begun repeating itself.\n\n",
"CALIBRATING: A text field is provided on the interface so that users may\n",
"             test their Repeat Keys settings.\n\n\n" };


/****************************************************************/
/*								*/	
/* Slow Keys Help String					*/
/*								*/
/****************************************************************/
static char *slowHelpString[] = {
"Slow Keys\n\n",
"DESCRIPTION: Slow Keys benefits users who hit unwanted keys as they search\n",
"             for the desired key. Mouth stick users often exhibit this\n",
"             typing behavior. The Slow Keys feature instructs the system\n",
"             to accept key presses if they have been held down for a\n",
"             certain amount of time\n\n",
"ENABLING:    Slow Keys may be turned on or off in one of two ways. It may\n",
"             be turned on or off via the check box in the 'Enable' panel\n",
"             Also, Slow Keys may be turned on or off via the keyboard by\n",
"             holding the left or right Shift key for four seconds. This\n",
"             also turns Repeat Keys on or off. Refer to the Help\n",
"             description of Repeat Keys for more information.\n\n",
"             Note that the Slow Keys and Bounce Keys features a mutually\n",
"             exclusive, i.e. only one may be turned on at one time.\n\n",
"FEATURES:    Slow Keys has three settable parameters. The first allows the\n",
"             user to hear a beep when either the key has first been\n",
"             pressed or when the key has been accepted as a key stroke or\n",
"             both.  The 'Acceptance Delay parameters, displayed in Seconds,\n",
"             instructs the system to only accept a key stroke after it has\n",
"             been held down for a certain number of seconds. These are set\n",
"             in the 'Slow Keys' panel.\n\n",
"CALIBRATING: A text field is provided in interface allowing users to test\n",
"             Slow Keys settings.\n\n\n" };


/****************************************************************/
/*								*/
/* Bounce Keys Help String					*/ 
/*								*/
/****************************************************************/
static char *bounceHelpString[] = {
"Bounce Keys\n\n",
"DESCRIPTION: Bounce Keys benefits users who type by bouncing up and down\n",
"             on one key. The Bounce Keys feature instructs the system to\n",
"             ignore all future key presses of a certain key if they happen\n",
"             within a certain period of time.\n\n",
"ENABLING:    Bounce Keys may be turned on or off via the check box in the\n",
"             'Enable' panel.\n\n",
"             Note that Bounce Keys and Slow Keys are mututall exclusive,",
"             i.e. only one of these features may be turned on at one\n",
"             time.\n\n",
"FEATURES:    Bounce Keys has one user settable parameter, the 'Debounce\n",
"             Time', displayed in seconds. The first key press of a key\n",
"             is accepted. If this key is pressed again in a time shorter\n",
"             than the 'Debounce Time', it will be ignored. The next key\n",
"             stroke will only be accepted if it has been released for a\n",
"             period longer than the 'Debounce Time'. The 'Debounce Time'\n",
"             parameters is settable via a scale in the 'Bounce Keys'\n",
"             panel.\n\n",
"CALIBRATION: A text field is provided in the interface allowing users to\n",
"             test Bounce Keys settings.\n\n\n" };
