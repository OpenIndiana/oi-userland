#
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
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
###############################################################################
#
#  This Makefile builds mdb modules.
#  It is designed to build both kernel kmdb and mdb .so files
#
###############################################################################

include $(TOP)/Makefile.inc

include $(TOP)/Makefile.rules


BUILD_TYPE = 64

KMOD	= i915
MDBMOD	= i915.so
MODULES	= $(KMOD) $(MDBMOD)

CFLAGS		+= -Wall
CFLAGS		+= -std=gnu11
CFLAGS		+= -D_ELF64 -DMDB_DEBUG -D_KERNEL -D_KMDB -g -m64
CPPFLAGS	+= -I$(TOP) -I$(TOP)/sys/drm -I$(TOP)/sys -I/usr/include
KMOD_LDFLAGS	= -dy -r -Nmisc/kmdbmod
SO_LDFLAGS	= $(LDFLAGS) -Wl,-z,direct -Wl,-z,text -Wl,-Mmapfile
CPPFLAGS	+= -O3 -m64 -Ui386 -U__i386 -g \
	-DTEXT_DOMAIN=\"SUNW_OST_OSCMD\" -D_ERRNO_VERIFY -DMDB_DEBUG \
	-D_KERNEL -D_ELF64

SOURCES		= i915.c
OBJECTS		= $(SOURCES:%.c=%.o)
LINTFILES	= $(SOURCES:%.c=%.ln)
BC_OBJS		= $(SOURCES:%.c=%.o.bc)

all: $(MODULES)

.KEEP_STATE:

.NO_PARALLEL:
.PARALLEL: $(OBJECTS) $(LINTFILES)

%.o: %.c
	$(CC) -c $(CFLAGS) $(CPPFLAGS) $< -o $@
	$(CTFCONVERT) $(CTFCVTFLAGS) $@

$(KMOD): $(OBJECTS)
	$(LD) -o $@ $(OBJECTS) $(KMOD_LDFLAGS) $(LIBS)
	$(CTFMERGE) $(CTFMERGE_LABEL) -o $@ $(OBJECTS)

$(MDBMOD): $(OBJECTS)
	$(CC) $(CFLAGS) -fPIC -DPIC $(CPPFLAGS) -shared -o $@ $(SOURCES) $(LDFLAGS) \
		$(SO_LDFLAGS) $(LIBS)

install: $(MODULES)
	@print Installing $(KMOD) in $(DESTDIR)$(ROOT_KMOD_DIR)
	@print Installing $(MDBMOD) in $(DESTDIR)$(ROOT_MDB_DIR)
	@mkdir -p $(DESTDIR)$(ROOT_KMOD_DIR)
	@mkdir -p $(DESTDIR)$(ROOT_MDB_DIR)
	@$(INSTALL) -m 555 $(KMOD) $(DESTDIR)$(ROOT_KMOD_DIR)
	@$(INSTALL) -m 555 $(MDBMOD) $(DESTDIR)$(ROOT_MDB_DIR)

clean:
	rm -f $(OBJECTS) $(BC_OBJS) $(MODULES)

clean.lint:
	rm -f $(LINTFILES)

clobber: clean clean.lint
	rm -f $(MODULES)

%.ln:%.c
	$(LINT) $(LINTFLAGS) $(CPPFLAGS) -o $@ $<

lint: $(LINTFILES)
