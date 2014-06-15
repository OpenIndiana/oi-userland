#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
#

CC?=gcc
SRCS=libbe_py.c
OBJS=libbe_py_26.o libbe_py_27.o
TGTS=libbe_py_26.so libbe_py_27.so
LIBS=-lbe -lnvpair -lc
MAPFILE=mapfile-vers

LDFLAGS+= -Wl,-M$(MAPFILE)

all: libbe_py_26.so libbe_py_27.so 

libbe_py_26.so: libbe_py_26.o
	$(CC) $(CFLAGS) $(LDFLAGS) -shared $<  -lpython2.6 $(LIBS) -o $@

libbe_py_27.so: libbe_py_27.o
	$(CC) $(CFLAGS) $(LDFLAGS) -shared $<  -lpython2.7 $(LIBS) -o $@

libbe_py_26.o: libbe_py.c Makefile
	$(CC) -c $(CFLAGS) libbe_py.c -fPIC -DPIC -I/usr/include/python2.6 -o $@

libbe_py_27.o: libbe_py.c Makefile
	$(CC) -c $(CFLAGS) libbe_py.c -fPIC -DPIC -I/usr/include/python2.7 -o $@

clean: 
	rm -fr $(OBJS) $(TGTS)

install:
# Do nothing, files are picked from BUILD_DIR
