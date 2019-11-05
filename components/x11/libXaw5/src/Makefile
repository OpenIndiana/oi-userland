# Copyright (c) 2009, Oracle and/or its affiliates. All rights reserved.
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

SRCS = 	AllWidgets.c AsciiSink.c AsciiText.c Box.c \
	Command.c Dialog.c Form.c Grip.c Label.c List.c MenuButton.c \
	MultiSink.c Paned.c Panner.c Porthole.c \
	Repeater.c Scrollbar.c Simple.c SimpleMenu.c Sme.c SmeBSB.c \
	SmeLine.c StripChart.c TextSrc.c \
	TextAction.c TextPop.c TextTr.c Toggle.c Tree.c Vendor.c \
	XawIm.c XawInit.c XawI18n.c sharedlib.c \
	Text.c TextSink.c Viewport.c AsciiSrc.c MultiSrc.c
OBJS = $(SRCS:.c=.o)

REQUIREDLIBS = -lX11 -lc -lXext -lXmu -lXt

XLIB_CFLAGS:sh = pkg-config --cflags x11

libXaw.so.5: $(OBJS) 
	$(CC) -shared -fPIC -Wl,-soname,$@ -o $@ $(LDFLAGS) \
	$(OBJS) $(REQUIREDLIBS)

.c.o:
	$(CC) -fPIC $(CPPFLAGS) $(CFLAGS) $(XLIB_CFLAGS) $(CPPFLAGS) -c $<

install: libXaw.so.5
	mkdir -p $(DESTDIR)$(libdir)
	$(INSTALL) libXaw.so.5 $(DESTDIR)$(libdir)/libXaw.so.5
