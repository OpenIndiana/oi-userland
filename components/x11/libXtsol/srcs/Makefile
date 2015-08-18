# Copyright (c) 2008, 2014, Oracle and/or its affiliates. All rights reserved.
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

HEADERSPublic = Xtsol.h Xtsolproto.h
HEADERSPublic_dir = $(PREFIX)/include/X11/extensions

SRCS = Xtsol.c
OBJS = $(SRCS:.c=.o)

REQUIREDLIBS = -lX11 -ltsol -lc

XLIB_CFLAGS:sh = pkg-config --cflags x11

libXtsol.so.1: $(OBJS) mapfile-vers
	$(CC) -shared -o $@ -Wl,-h$@ $(CFLAGS) $(LDFLAGS) -Wl,-Mmapfile-vers \
	  $(OBJS) $(REQUIREDLIBS)

.c.o:
	$(CC) -fPIC -DPIC $(XLIB_CFLAGS) $(CFLAGS) $(CPPFLAGS) -c $<

install: libXtsol.so.1 $(HEADERSPublic)
	mkdir -p $(DESTDIR)$(HEADERSPublic_dir)
	$(INSTALL) -m 0444 $(HEADERSPublic) $(DESTDIR)$(HEADERSPublic_dir)
	mkdir -p $(DESTDIR)$(libdir)
	-rm -f $(DESTDIR)$(libdir)/libXtsol.so \
	       $(DESTDIR)$(libdir)/libXtsol.so.1
	$(INSTALL) -m 0555 libXtsol.so.1 $(DESTDIR)$(libdir)/libXtsol.so.1
	ln -s libXtsol.so.1 $(DESTDIR)$(libdir)/libXtsol.so
