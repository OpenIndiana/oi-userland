#
# Copyright (c) 2003, 2011, Oracle and/or its affiliates. All rights reserved.
#
# U.S. Government Rights - Commercial software. Government users are subject
# to the Sun Microsystems, Inc. standard license agreement and applicable
# provisions of the FAR and its supplements.
#
# This distribution may include materials developed by third parties. Sun,
# Sun Microsystems, the Sun logo and Solaris are trademarks or registered
# trademarks of Sun Microsystems, Inc. in the U.S. and other countries.
#
# Copyright 2022 Klaus Ziegler
#

#
# Makefile to generate libseaExtensions.so
# 

LDLIBS=-lrpcsvc

PROG= libseaExtensions.so
SRCS= sunHostPerf.c sunProcesses.c sunSystem.c seaExtensions.c
OBJS = $(SRCS:.c=.o)

all:$(PROG)
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(LDFLAGS) $(LDLIBS) -G -o $@ $(OBJS)
.c.o:
	$(CC) $(CFLAGS) $(LDFLAGS) -g  -o $@ -c $<

clean:
	rm -f *.o *.so

install:
	if test "$(ARCH)" = "sparcv9" ; then \
		cp $(PROG) $(ROOT)/$(CFGLIB64); \
	elif test "$(ARCH)" = "32" ; then \
		cp $(PROG) $(ROOT)/$(CFGLIB); \
	elif test "$(ARCH)" = "amd64" ; then \
		cp $(PROG) $(ROOT)/$(CFGLIB64); \
	fi
