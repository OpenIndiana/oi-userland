# Copyright (c) 2010, Oracle and/or its affiliates. All rights reserved.
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

MODULES=Xserver.so
MDB_MODULE_DIR=/usr/lib/mdb/proc/$(ARCHLIBSUBDIR)

CFLAGS += -fPIC -DPIC -g
CPPFLAGS += -I ../../../../include -I ../../../.. -I ../../../../Xext -I/usr/include/pixman-1
LDFLAGS += -Wl,-z,text -Wl,-Mmapfile

HEADERS = Xserver_mdb.h
SOURCES = Xserver_clients.c Xserver_device_grabs.c mdb_module.c
OBJECTS = $(SOURCES:%.c=%.o)
LINTFILES = $(SOURCES:%.so=%.ln)

all: $(MODULES)

.KEEP_STATE:

.NO_PARALLEL:
.PARALLEL: $(OBJECTS) $(LINTFILES)

Xserver.so: $(OBJECTS)
	$(CC) $(CFLAGS) -shared -o Xserver.so $(OBJECTS) $(LDFLAGS) $(LIBS)

install: Xserver.so
	mkdir -p $(DESTDIR)$(MDB_MODULE_DIR)$(SERVERMOD_SUBDIR)
	cp Xserver.so $(DESTDIR)$(MDB_MODULE_DIR)$(SERVERMOD_SUBDIR)

clean:
	rm -f $(OBJECTS)

clean.lint:
	rm -f $(LINTFILES)

clobber: clean clean.lint
	rm -f $(MODULES)

%.ln: %.c
	$(LINT) $(LINTFLAGS) $(CPPFLAGS) -c $<

lint: $(LINTFILES)
