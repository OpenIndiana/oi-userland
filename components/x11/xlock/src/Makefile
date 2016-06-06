###############################################################################
#
# xlock Makefile
#
# Copyright (c) 2008, 2015, Oracle and/or its affiliates. All rights reserved.
#
# Permission is hereby granted, free of charge, to any person obtaining a
# copy of this software and associated documentation files (the "Software"),
# to deal in the Software without restriction, including without limitation
# the rights to use, copy, modify, merge, publish, distribute, sublicense,
# and/or sell copies of the Software, and to permit persons to whom the
# Software is furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice (including the next
# paragraph) shall be included in all copies or substantial portions of the
# Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
# THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
# DEALINGS IN THE SOFTWARE.
#
# Makefile for xlock. 

CPPFLAGS += ${DEFINES} -DUSE_PAM -DIPv6
C_SRCS=xlock.c hsbramp.c resource.c \
	hopalong.c qix.c life.c image.c blank.c swarm.c rotor.c pyro.c flame.c
HDRS=xlock.h
IMAGES=lifeicon.bit sunlogo.bit
SRCS=${C_SRCS} ${HDRS} ${IMAGES} xlock.man XLock.ad
OBJS=${C_SRCS:.c=.o}
LIBS=-lX11 -lm -lpam -lbsm -lsocket
# Base lint flags
LINTFLAGS = -fd -s -errtags=yes -Xc99
# 64-bit checks
LINTFLAGS += -m64 -L/usr/lib/64 -errchk=longptr64,sizematch
LINTFLAGS += -erroff=E_CAST_INT_TO_SMALL_INT -erroff=E_CAST_UINT_TO_SIGNED_INT
# higher level checks for potential security issues since xlock is setuid
LINTFLAGS += -errsecurity=extended
# but don't warn about use of random() for screen displays, not security purposes
LINTFLAGS += -erroff=E_SEC_RAND_WARN

# Get default XFILESEARCHPATH from libXt & use it in resource.c
DEF_FILESEARCHPATH=`pkg-config --variable=xfilesearchpath xt` 
datadir=$(PREFIX)/share
libdir=$(PREFIX)/lib
sysconfdir=/etc
#resource.o lint := CPPFLAGS += -DDEF_FILESEARCHPATH=\"$(DEF_FILESEARCHPATH)\"

xlock: ${OBJS}
	@print $(DEF_FILESEARCHPATH) | perl -n -e \
	   'die("*** xfilesearchpath not found in xt.pc") if $$_ =~ /^$$/'
	${CC} -o $@ ${OBJS} ${CFLAGS} ${LDFLAGS} ${LIBS}

install: xlock xlock.1 XLock.ad
	mkdir -p $(DESTDIR)$(bindir)
	$(INSTALL) -m 0555 xlock $(DESTDIR)$(bindir)/xlock
	mkdir -p $(DESTDIR)$(mandir)/man1
	$(INSTALL) -m 0444 xlock.1 $(DESTDIR)$(mandir)/man1/xlock.1
	mkdir -p $(DESTDIR)$(datadir)/X11/app-defaults
	$(INSTALL) -m 0444 XLock.ad $(DESTDIR)$(datadir)/X11/app-defaults/XLock

lint: ${C_SRCS}
	${LINT} ${LINTFLAGS} ${CPPFLAGS} ${C_SRCS} ${LIBS}
