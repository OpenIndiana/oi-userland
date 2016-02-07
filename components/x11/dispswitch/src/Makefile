# Copyright (c) 2009, 2014, Oracle and/or its affiliates. All rights reserved.
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

PKGS= 'xrandr >= 1.2.0' x11
PKG_CFLAGS=`pkg-config --cflags $(PKGS)`
PKG_LIBS=`pkg-config --libs $(PKGS)`
CFLAGS+= $(PKG_CFLAGS)
LIBS= $(PKG_LIBS)
BINDIR:=${BINDIR}

dispswitch: dispswitch.c
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) dispswitch.c $(LIBS)

install: dispswitch dispswitch.man gnome-dispswitch.desktop
	mkdir -p $(DESTDIR)$(BINDIR) \
		 $(DESTDIR)$(PREFIX)/share/man/man1 \
		 $(DESTDIR)/etc/xdg/autostart
	$(INSTALL) -m 0555 dispswitch $(DESTDIR)$(BINDIR)
	$(INSTALL) -m 0444 dispswitch.man \
		$(DESTDIR)$(PREFIX)/share/man/man1/dispswitch.1
	$(INSTALL) -m 0444 gnome-dispswitch.desktop $(DESTDIR)/etc/xdg/autostart
