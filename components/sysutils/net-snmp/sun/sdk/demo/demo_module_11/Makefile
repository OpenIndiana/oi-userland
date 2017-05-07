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
# Makefile to generate demo_module_11.so
# 
# usage:
# To point to a particular compiler, set CC.
# Example: setenv CC /usr/dist/share/forte_dev/bin/cc
# "make" : generate library for 64bit
# "make ARCH=32" : generate library for 32bit
# "make clean" : remove *.o , *.so
#

ARCH=64
CFLAGS_64=-g -m64 -I/usr/include/sma_snmp -I.
CFLAGS_32=-g -I/usr/include/sma_snmp -I.
CFLAGS=$(CFLAGS_$(ARCH))

LDLIBS_64= -B dynamic -L /usr/lib/sparcv9 -l entity
LDLIBS_32= -B dynamic -l entity
LDLIBS=$(LDLIBS_$(ARCH))

PROG= demo_module_11.so
SRCS= MyTable.c
OBJS = $(SRCS:.c=.o)

all:$(PROG)
$(PROG): $(OBJS)
	$(CC) $(CFLAGS) $(LDLIBS) -G -o $@ $(OBJS)
.c.o:
	$(CC) $(CFLAGS) -g  -o $@ -c $<

clean:
	rm -f MyTable.o demo_module_11.so


