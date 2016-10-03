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
# Makefile to generate demo_module_9.so
# 
# usage:
# "make" : generate library for 64bit / sparc
# "make ARCH=32" : generate library for 32bit / sparc
# "make ARCH=32 MACH=x86" : generate library for 32bit / x86
# "make clean" : remove *.o , *.so
#


ARCH=64
LDFLAGS_64=-g -m64  -I.
LDFLAGS_32=-g -I.
LDFLAGS=$(LDFLAGS_$(ARCH))

LDLIBS=

PROG= demo_module_10.so
SRCS= demo_module_10.c
OBJS = $(SRCS:.c=.o)

all:$(PROG)
$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) $(LDLIBS) -G -o $@ $(OBJS)
.c.o:
	$(CC) $(LDFLAGS) -g  -o $@ -c $<

clean:
	rm -f *.o *.so


