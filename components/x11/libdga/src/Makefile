###############################################################################
#
# libdga Makefile
#
# Copyright (c) 2009, 2013, Oracle and/or its affiliates. All rights reserved.
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
#

SHLIBLDFLAGS = -G -z defs -z text $(LDFLAGS)
REQUIREDLIBS = -lX11 -lc -lnsl -lsocket
DEFINES = -D_TS_ERRNO -DMT -DXTHREADS -DPANORAMIX -DIPv6 -DSVR4

HEADERS = dga_Xrequests.h win_grab.h rtn_grab.h cmap_grab.h pix_grab.h \
	  mbufsetstr.h vmbuf_grab.h dga_incls.h
SRCS =  dga_Xrequests.c win_grab.c dga_db.c rtn_grab.c cmap_grab.c pix_grab.c \
	mbsmemb_update.c mbsmemb_inquiry.c win_update.c mbuf_update.c \
	mbufset.c draw_inquiry.c draw_db.c pix_update.c pix_inquiry.c dga_ab.c
OBJS = $(SRCS:.c=.o)

# Inspired by automake 1.11 silent rules - hides details by default
# Run make V=1 to show details
DEFAULT_V  = 0
V_CC       = $(V_CC_$(V))
V_CC_      = $(V_CC_$(DEFAULT_V))
V_CC_0     = @echo "  CC    " $@;

all: libdga.so.1

libdga.so.1: $(OBJS)
	$(V_CC)$(CC) $(CFLAGS) -shared -o $@ $(SHLIBLDFLAGS) -h libdga.so.1 \
		$(OBJS) $(REQUIREDLIBS)

.c.o:
	$(V_CC)$(CC) -fpic $(CFLAGS) $(CPPFLAGS) $(DEFINES) -c $<

install: libdga.so.1
	mkdir -p $(DESTDIR)$(libdir) $(DESTDIR)$(INCDIR)
	$(INSTALL) libdga.so.1 $(DESTDIR)$(libdir)/libdga.so.1
