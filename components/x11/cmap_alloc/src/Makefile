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

SRCS = cmap_alloc.c
BINDIR:=${BINDIR}

cmap_alloc: cmap_alloc.c
	$(CC) -o $@ $(CFLAGS) $(LDFLAGS) cmap_alloc.c -lX11

install: cmap_alloc cmap_alloc.1
	mkdir -p $(DESTDIR)$(BINDIR) $(DESTDIR)$(PREFIX)/share/man/man1
	$(INSTALL) -m 0555 cmap_alloc $(DESTDIR)$(BINDIR)
	$(INSTALL) -m 0444 cmap_alloc.1 $(DESTDIR)$(PREFIX)/share/man/man1
