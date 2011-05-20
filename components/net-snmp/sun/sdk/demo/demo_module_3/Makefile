#
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#
# U.S. Government Rights - Commercial software. Government users are subject
# to the Sun Microsystems, Inc. standard license agreement and applicable
# provisions of the FAR and its supplements.
#
# Use is subject to license terms.
#
# This distribution may include materials developed by third parties. Sun,
# Sun Microsystems, the Sun logo and Solaris are trademarks or registered
# trademarks of Sun Microsystems, Inc. in the U.S. and other countries.
#
#

#
#
# Makefile to generate demo_module_3.so
# 
# usage:
# setenv CC /usr/bin/cc (or correct path)
# "make" : generate library for 64bit
# "make ARCH=32" : generate library for 32bit
# "make clean" : remove *.o , *.so
#

ARCH=64
LDFLAGS_64=-g -m64 -I.
LDFLAGS_32=-g -I.
LDFLAGS=$(LDFLAGS_$(ARCH))

LDLIBS=

PROG= demo_module_3.so
SRCS= demo_module_3.c
OBJS = $(SRCS:.c=.o)

all:$(PROG)
$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) $(LDLIBS) -G -o $@ $(OBJS)
.c.o:
	@if test "$(CC)" = "" ; then \
	echo "Environment variable CC must be set with compiler path" ; \
	exit 1 ; \
	fi
	$(CC) $(LDFLAGS) -g  -o $@ -c $<

clean:
	rm -f demo_module_3.o demo_module_3.so
