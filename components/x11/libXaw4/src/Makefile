# Copyright (c) 2009, 2011, Oracle and/or its affiliates. All rights reserved.
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

SRCS = 	Xaw3_1AsciiSink.c Xaw3_1AsciiSrc.c Xaw3_1AsciiText.c Xaw3_1Box.c\
	Xaw3_1Clock.c Xaw3_1Command.c Xaw3_1Dialog.c Xaw3_1Form.c \
	Xaw3_1Grip.c Xaw3_1Label.c Xaw3_1List.c Xaw3_1Logo.c \
	Xaw3_1Mailbox.c Xaw3_1MenuButton.c Xaw3_1Paned.c Xaw3_1Scrollbar.c \
	Xaw3_1Simple.c Xaw3_1SimpleMenu.c Xaw3_1Sme.c Xaw3_1SmeBSB.c \
	Xaw3_1SmeLine.c Xaw3_1StripChart.c Xaw3_1Template.c Xaw3_1Text.c \
	Xaw3_1TextAction.c Xaw3_1TextPop.c Xaw3_1TextSink.c Xaw3_1TextSrc.c \
	Xaw3_1TextTr.c Xaw3_1Toggle.c Xaw3_1Vendor.c Xaw3_1Viewport.c \
	Xaw3_1XawInit.c
OBJS = $(SRCS:.c=.o)

REQUIREDLIBS = -lX11 -lXmu -lXt -lm -lc

XLIB_CFLAGS:sh = pkg-config --cflags x11

libXaw.so.4: $(OBJS) 
	$(CC) -shared -fPIC -Wl,-soname,$@ -o $@ $(LDFLAGS) $(OBJS) $(REQUIREDLIBS)

.c.o:
	$(CC) -fPIC $(CPPFLAGS) $(CFLAGS) $(XLIB_CFLAGS) $(CPPFLAGS) -c $<

install: libXaw.so.4
	mkdir -p $(DESTDIR)$(libdir)
	$(INSTALL) libXaw.so.4 $(DESTDIR)$(libdir)/libXaw.so.4
