/*
 * Copyright (c) 1992, 2015, Oracle and/or its affiliates. All rights reserved.
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
 * fbconsole - fallback console
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <fcntl.h>
#include <poll.h>
#include <signal.h>
#include <stropts.h>
#include <termios.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <sys/param.h>
#include <sys/strredir.h>

#include <X11/Xos.h>
#include <X11/Xlib.h>

static char		LogPath[MAXPATHLEN];	/* pathname of log file */

/*
 * Default settings to use if they can't actually be obtained from a
 * descriptor relevant to the application.
 *
 * XXX:	These settings shouldn't be used unless absolutely necessary, since
 *	they're almost certain to get out of sync with the kernel's defaults
 *	(which is what they're intended to be).
 */
static struct termios	termios_dflt = {
	BRKINT|ICRNL|IXON|IGNPAR|IMAXBEL,	    	/* input modes */
	OPOST|ONLCR,				    	/* output modes */
	B9600|(B9600 << IBSHIFT)|CS8|HUPCL|CREAD,    	/* control modes */
	ISIG|ICANON|ECHO|IEXTEN|ECHOE|ECHOK|ECHOCTL|ECHOKE, /* local modes */
						       /* control characters */
	CINTR,		/* VINTR */
	CQUIT,		/* VQUIT */
	CERASE,		/* VERASE */
	CKILL,		/* VKILL */
	CEOT,		/* VEOF */
	CEOL,		/* VEOL */
	CEOL2,		/* VEOL2 */
	CNUL,		/* VSWTCH */
	CSTART,		/* VSTART */
	CSTOP,		/* VSTOP */
	CSUSP,		/* VSUSP */
	CDSUSP,		/* VDSUSP */
	CRPRNT,		/* VRPRNT */
	CFLUSH,		/* VDISCARD */
	CWERASE,	/* VWERASE */
	CLNEXT,		/* VLNEXT */
};


#ifdef	NOTDEF
/*
 * OpenConsole
 *	Returns a file descriptor which has had the console redirected to it
 *
 * This version (unused) opens a pipe and redirects the console to it.
 */
static int
OpenConsole(void)
{
	int	fds[2];
	int	fdcons;

	if (pipe(fds) == -1) {
		fprintf(stderr,"Couldn't open console pipes\n");
		perror("pipe");
		exit(1);
	}

	if ((fdcons = open("/dev/console", O_RDONLY)) == -1) {
		fprintf(stderr,"Couldn't open /dev/console\n");
		perror("open");
		exit(1);
	}

	if (ioctl(fdcons, SRIOCSREDIR, fds[0]) == -1) {
		fprintf(stderr,"Couldn't redirect console to console pipe\n");
		exit(1);
	}

	return fds[1];
}
#endif /* NOTDEF */


/*
 * OpenConsole
 *
 * Opens a pty, copies tty settings into it from /dev/console, and redirects
 * console output to it.  Returns the master end of the pty.
 */
static int
OpenConsole(void)
{
	int	console;
	int	master;
	int	slave;
	char	*slavename;
	struct termios termios;

	if ((console = open("/dev/console", O_RDONLY | O_NOCTTY, 0)) == -1) {
		perror("fbconsole: open /dev/console");
		exit(1);
	}

	if ((master = open("/dev/ptmx", O_RDWR, 0)) == -1) {
		perror("fbconsole: open /dev/ptmx");
		exit(1);
	}

	if (grantpt(master) == -1) {
		fputs("fbconsole: grantpt failed\n", stderr);
		exit(1);
	}

	if (unlockpt(master) == -1) {
		fputs("fbconsole: unlockpt failed\n", stderr);
		exit(1);
	}

	if ((slavename = ptsname(master)) == NULL) {
		fputs("fbconsole: ptsname failed\n", stderr);
		exit(1);
	}

#ifdef	DEBUG
	fprintf(stderr, "slavename = \"%s\"\n", slavename);
#endif

	if ((slave = open(slavename, O_RDWR, 0)) == -1) {
		perror("fbconsole: open slave");
		exit(1);
	}

	if (ioctl(slave, I_PUSH, "ptem") == -1) {
		perror("fbconsole: push ptem");
		exit(1);
	}

	if (ioctl(slave, I_PUSH, "ldterm") == -1) {
		perror("fbconsole: push ldterm");
		exit(1);
	}

	/*
	 * Propagate tty settings from the real console to the new console.  
	 * If the erase character is zero, apply default settings to the new 
	 * console.  If the erase character is nonzero, leave most of the 
	 * settings intact and apply default values only to the modes and to 
	 * the EOF and EOL character.  (Why apply defaults for EOF and EOL?)
	 *
	 * Code originally taken from XView, lib/libxview/ttysw/tty_gtty.c
	 */

	if (tcgetattr(console, &termios) == -1) {
		perror("fbconsole: tcgetattr");
		exit(1);
	}

	if (termios.c_cc[VERASE] == 0) {
		termios = termios_dflt;
	} else {
		termios.c_iflag = termios_dflt.c_iflag;
		termios.c_oflag = termios_dflt.c_oflag;
		termios.c_cflag = termios_dflt.c_cflag;
		termios.c_lflag = termios_dflt.c_lflag;
		termios.c_cc[VEOF] = termios_dflt.c_cc[VEOF];
		termios.c_cc[VEOL] = termios_dflt.c_cc[VEOL];
	}

	if (tcsetattr(slave, TCSANOW, &termios) == -1) {
		perror("fbconsole: tcsetattr");
		exit(1);
	}

	/* redirect console output into the slave side */

	if (ioctl(console, SRIOCSREDIR, slave) == -1) {
		perror("fbconsole: ioctl SRIOCSREDIR");
		exit(1);
	}

	return master;
}


/*
 * OpenLog
 *	Opens the console log file; returns a file descriptor
 */
static FILE *
OpenLog(
	const char *dpyName,
	char	*path)
{
	const char *tmpName;
	FILE	*log;
	int	tmpFd;

	if (path == NULL) {
		tmpName = getenv("TMPDIR");
		if (tmpName == NULL) {
			tmpName = P_tmpdir;
		}
		if (snprintf(LogPath, sizeof(LogPath), "%s/wscon-%s-XXXXXX",
		    tmpName, dpyName) > sizeof(LogPath)) {
			tmpFd = -1;
		} else {
			tmpFd = mkstemp(LogPath);
		}
		path = LogPath;
	} else {
		LogPath[0] = '\0';

		if ((strcmp(path,"-") == 0) || 
		    (strcmp(path,"stderr") == 0)) {
			return stderr;
		}
		tmpFd = open(path, O_WRONLY | O_CREAT | O_EXCL, 
		    S_IRUSR|S_IWUSR);
	}

#ifdef	DEBUG
	fprintf(stderr, "log file = \"%s\"\n", path);
#endif

	if ( (tmpFd < 0) || (log = fdopen(tmpFd, "w")) == NULL) {
		fprintf(stderr,
		    "fbconsole: couldn't open console log file '%s'\n",path);
		exit(1);
	}
	setvbuf(log, NULL, _IONBF, 0);

	fchmod(fileno(log), S_IRUSR|S_IWUSR);

	return log;
}

/*
 * CloseLog
 */
static void
CloseLog(void)
{
	if (LogPath[0] == '\0')
		return;

	if (unlink(LogPath) == -1)
		perror("unlink");
}

/*
 * CleanupAndExit
 *	Closes log file and exits
 */
static void
CleanupAndExit(void)
{
	CloseLog();
	exit(0);
}


/*
 * SignalHandler
 *	The signal handler for SIGINT and SIGTERM.
 */
/*ARGSUSED*/
void
SignalHandler(int sig)
{
	CleanupAndExit();
}


/*
 * DisplayErrorHandler
 *	X I/O error handler.
 */
/*ARGSUSED*/
int
DisplayErrorHandler(Display *dpy)
{
	CleanupAndExit();
	return 0;
}


/*
 * LogConsole
 *	Reads a console message and writes it to the console log file
 */
static void
LogConsole(
	int	console,
	FILE	*log)
{
	char	buf[1024];
	int	rcount;

	rcount = read(console, buf, 1024);

	if (rcount == -1)
		return;

	(void) fwrite(buf, rcount, 1, log);
}

/*
 * InputLoop
 *	Waits for input from the console message pipe or the xserver.
 *	On input from the console - logs it to the console log file.
 *	On any input (or EOF) from the xserver, exits
 */
static void
InputLoop(
	Display		*dpy,
	int		console,
	FILE		*log)
{
	struct pollfd	fds[2];
	XEvent		event;
	int		fdcount = 1;
	
#define CONSOLE_FD 0
#define XSERVER_FD 1	
	
	fds[CONSOLE_FD].fd 	= console;
	fds[CONSOLE_FD].events 	= POLLIN;
	if (dpy != NULL) {
		fds[XSERVER_FD].fd 	= ConnectionNumber(dpy);
		fds[XSERVER_FD].events 	= POLLIN;
		fdcount++;
	}
	
	while (poll(fds, fdcount, -1) >= 0) {

		if ((dpy != NULL) && (fds[XSERVER_FD].revents)) {
			while (XPending(dpy))
				XNextEvent(dpy, &event);
		}

		if (fds[CONSOLE_FD].revents & POLLIN) {
			LogConsole(console,log);
		}
	}
}

/*
 * Usage
 *	Prints a usage message
 */
static void
Usage(void)
{
	
	fprintf(stderr,"Usage: fbconsole [-d <display>] [-f <logfile>] [-n]\n");
	exit(1);
}

/*
 * main
 */
int
main(int argc, char **argv)
{
	Display	*dpy = NULL;
	char	*dpyName = NULL;
	int	console;
	char	*logFile = NULL;
	FILE	*log;
	int	opt;
	int	noDisplay = False;

	while ((opt = getopt(argc, argv, "d:f:n")) != EOF) {
		switch (opt) {
		case 'd':
			dpyName = optarg;
			break;
		case 'n':
		    	noDisplay = True;
			break;
		case 'f':
			logFile = optarg;
			break;
		case '?':
			Usage();
			break;
		}
	}

	if (noDisplay) {
	    dpyName = XDisplayName(dpyName);	    
	} else {
	    if ((dpy = XOpenDisplay(dpyName)) == NULL) {
		fprintf(stderr,
			"Couldn't open display connection %s\n",
			XDisplayName(dpyName));
		exit(1);
	    }
	    (void) XSetIOErrorHandler(DisplayErrorHandler);
	    dpyName = XDisplayString(dpy);
	}

	console = OpenConsole();

	log = OpenLog(dpyName, logFile);

	(void)sigset(SIGHUP, SignalHandler);
	(void)sigset(SIGINT, SignalHandler);
	(void)sigset(SIGQUIT, SignalHandler);
	(void)sigset(SIGTERM, SignalHandler);
	(void)sigset(SIGPIPE, SignalHandler);

	InputLoop(dpy, console, log);

	return(0);
}
