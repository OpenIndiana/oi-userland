/* $XConsortium: kbd_mode.c,v 4.6 94/04/17 20:29:33 kaleb Exp $ */
/* Copyright (c) 1994, 2008, Oracle and/or its affiliates. All rights reserved.
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

/*
 *      kbd_mode:       set keyboard encoding mode
 */

#include <sys/types.h>
#include <sys/file.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/kbio.h>
#include <sys/kbd.h>
#include <stdio.h>
#include <stdlib.h>

static void         die(const char *);
static void         usage(void);
static int          kbd_fd;

int
main(int argc, char** argv)
{
    int    code = 0, translate, direct = -1;
    char   led;
    int    click;

    if ((kbd_fd = open("/dev/kbd", O_RDONLY, 0)) < 0) {
	die("Couldn't open /dev/kbd");
    }
    argc--; argv++;
    if (argc-- && **argv == '-') {
	code = *(++*argv);
    } else {
	usage();
    }
    switch (code) {
      case 'a':
      case 'A':
	translate = TR_ASCII;
	direct = 0;
	break;
      case 'e':
      case 'E':
	translate = TR_EVENT;
	break;
      case 'n':
      case 'N':
	translate = TR_NONE;
	break;
      case 'u':
      case 'U':
	translate = TR_UNTRANS_EVENT;
	break;
      default:
	usage();
    }
#ifdef KIOCSLED
    led = 0;
    if (ioctl(kbd_fd, KIOCSLED, &led))
	die("Couldn't set LEDs");
#endif
#ifdef KIOCCMD
    click = KBD_CMD_NOCLICK;
    if (ioctl(kbd_fd, KIOCCMD, &click))
	die("Couldn't set click");
#endif
    if (ioctl(kbd_fd, KIOCTRANS, (caddr_t) &translate))
	die("Couldn't set translation");
    if (direct != -1 && ioctl(kbd_fd, KIOCSDIRECT, (caddr_t) &direct))
	die("Couldn't set redirect");
    return 0;
}

static void
die(const char *msg)
{
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

static void
usage(void)
{
    int             translate;

    if (ioctl(kbd_fd, KIOCGTRANS, (caddr_t) &translate)) {
	die("Couldn't inquire current translation");
    }
    fprintf(stderr, "kbd_mode {-a | -e | -n | -u }\n");
    fprintf(stderr, "\tfor ascii, encoded (normal) SunView events,\n");
    fprintf(stderr, " \tnon-encoded, or unencoded SunView events, resp.\n");
    fprintf(stderr, "Current mode is %s.\n",
		(   translate == 0 ?    "n (non-translated bytes)"      :
		 (  translate == 1 ?    "a (ascii bytes)"               :
		  ( translate == 2 ?    "e (encoded events)"            :
		  /* translate == 3 */  "u (unencoded events)"))));
    exit(1);
}


