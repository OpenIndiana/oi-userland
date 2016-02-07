/*
 * Copyright (c) 1990, 2015, Oracle and/or its affiliates. All rights reserved.
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
 * winsysck - determine which window system protocols are available
 *
 * usage: winsysck [ -va ] [ -display display_name ] protocol [...]
 *
 * options:
 *   -a  check every protocol listed, rather than stopping after
 *       the first one.
 *   -v  print the first available protocol (or every available
 *       protocol, with the -a option) to stdout.
 *   -display display_name
 *       use the display display_name for X11 connections instead of
 *	 the one specified by the $DISPLAY environment variable.
 *   -timeout seconds
 *       The timeout option sets the number  of  seconds  before
 *       the winsysck will time out. 
 *
 * protocols:
 *   x11
 *       The X11 protocol.
 *   news
 *       The NeWS protocol.
 *   x11news
 *       Both the X11 and the NeWS protocols, and both connect to
 *       the same server.
 *   sunview
 *       The SunView protocol.
 *
 * NOTE: Since news, x11news, and sunview have been unsupported for over
 * a decade, we no longer actually check for them, but always return false.
 *
 * exit status:
 *    0  if any listed protocols are available
 *    1  if no listed protocols are available
 *    2  usage error
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/time.h>
#include <signal.h>
#include <unistd.h>

static char* cmdname;

static void
usage (void) {
    fprintf(stderr, "usage: %s %s\n\t%s\n", cmdname,
	    "[-va] [-display display_name] [-timeout seconds] protocol [...]",
	    "protocol can be one of: x11 news x11news sunview");
    exit(2);
}

/*
 * Keep track of what protocols we're checking, and in what order.
 */

#define PROTO_NONE	0
#define PROTO_X11	1
#define PROTO_NeWS	2
#define PROTO_X11NeWS	3
#define PROTO_SunView	4
#define N_PROTO		4

static int proto_list[N_PROTO], n_proto;

static void
AddProto(int proto)
{
    int i;
    for (i=0; i<N_PROTO; i++) {
	if (proto_list[i]==proto) {
	    return;
	}
    }
    proto_list[n_proto++]=proto;
}

/*
 * Keep track of the options specified.
 */
static int verbose, showall, timeout = 0;

static char* display_name=NULL;

/*
 * Parse the options.
 */

static void
Parse (int argc, char* argv[])
{
    for (;argc > 1; argv++, argc--) {
	if (argv[1][0] == '-') {
	    if (!strcmp(argv[1], "-display")) {
		display_name=argv[2];
		argv++;
		argc--;
		continue;
	    }
	    if (!strcmp(argv[1], "-timeout")) {
                timeout = atoi(argv[2]);
                argv++;
                argc--;
                continue;
            } 
	    for (; argv[1][1]; argv[1]++) {
	        switch (argv[1][1]) {
	        case 'a':
		    showall++;
		    break;
		case 'v':
		    verbose++;
		    break;
		default:
		    fprintf(stderr, "%s: -%c: unknown option\n",
			    cmdname,argv[1][1]);
		    usage();
	        }
	    }
	}
	else {
	    if (!strcmp(argv[1], "x11")) {
		AddProto(PROTO_X11);
	    } else if (!strcmp(argv[1], "news")) {
		AddProto(PROTO_NeWS);
	    } else if (!strcmp(argv[1], "x11news")) {
		AddProto(PROTO_X11NeWS);
	    } else if (!strcmp(argv[1], "sunview")) {
		AddProto(PROTO_SunView);
	    } else {
		fprintf(stderr, "%s: %s: unknown protocol\n",
			cmdname,argv[1]);
		usage();
	    }
	}
    }
    if (!n_proto) {
	fprintf(stderr, "%s: no protocols specified\n",
		cmdname);
	usage();
    }
}

/* Last remnants of x11-procs.c */
#include <X11/Xlib.h>
#include <X11/Xos.h>

static Display *display=NULL;

static void OnAlarm(int i)
{
      fprintf(stderr, "winsysck timeout\n");
      exit(1);        
}
 
static int
ConnectToX (const char* display_name)
{
     if(timeout > 0){
       signal(SIGALRM, OnAlarm);
       alarm(timeout);
     }
     display=XOpenDisplay(display_name);
     if(timeout > 0)
       alarm(0);
     return((display != NULL));
}

static int
DisconnectFromX (void) {
    XCloseDisplay(display);
    return(1);
}


/*
 * Try connecting via the specified protocols.
 */
static void
Probe(void)
{
    int i, found=0;
    for(i=0; (i < N_PROTO) && (proto_list[i] != PROTO_NONE); i++) {
	switch (proto_list[i]) {
	case PROTO_X11:
	    if (ConnectToX(display_name)) {
		found++;
		if (verbose) printf("%s\n","x11");
	        DisconnectFromX();
		if (!showall) exit(0);
	    }
	    break;
	case PROTO_NeWS:
	case PROTO_X11NeWS:
	case PROTO_SunView:
	    /* Don't even bother */
	    break;
	default:
	    fprintf(stderr, "%s: WSGO: proto_list[%d]==%d\n",
		    cmdname,i,proto_list[i]);
	}
    }
    exit(!found);
}

int
main (int argc, char* argv[])
{
    cmdname=argv[0];
    Parse(argc,argv);
    Probe();
    exit(0);
}

