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
# Makefile to generate demo_module_6.so
# 
# usage:
# "make" : generate library for 64bit / sparc
# "make ARCH=32" : generate library for 32bit / sparc
# "make ARCH=32 MACH=x86" : generate library for 32bit / x86
# "make clean" : remove *.o , *.so
#

ARCH=64
LIB32=/usr/lib
LIB64=/usr/lib/sparcv9
LD=/usr/ccs/bin/ld

OBJS1=demo_module_6.so
TARGETS=demo_module_6.so

#CFLAGS_64=-g -I. -Dsolaris_2 -m64
CFLAGS_64=-I. -Dsolaris_2 -m64
#CFLAGS_32=-g -I. -Dsolaris_2 
CFLAGS_32=-I. -Dsolaris_2 
CFLAGS=$(CFLAGS_$(ARCH))

BUILDAGENTLIBS_64=-R../lib -L$(LIB64) -lnetsnmpagent -lnetsnmpmibs -l netsnmphelpers -lnetsnmp -ldl -lkvm -lz  -lpkcs11 -lkstat -lelf -lm -ldl -lnsl -lsocket -ladm
BUILDAGENTLIBS_32=-R../lib -L$(LIB32) -lnetsnmpagent -lnetsnmpmibs -l netsnmphelpers -lnetsnmp  -ldl -lkvm -lz  -lpkcs11 -lkstat -lelf -lm -ldl -lnsl -lsocket -ladm
BUILDAGENTLIBS=$(BUILDAGENTLIBS_$(ARCH))



# shared library flags (assumes gcc)
#DLFLAGS=-fPIC -shared
# shared library flags (assumes cc)
DLFLAGS=-dy -G

all: $(TARGETS)

#example-demon-testTypesA32: $(OBJS1)
#$(CC) $(CFLAGS) -o example-demon-testTypesA32 $(OBJS1)  $(BUILDAGENTLIBS)

clean:
	rm $(OBJS1)  $(TARGETS)

demo_module_6.so: demo_module_6.o Makefile
	$(CC) $(CFLAGS)  -c -o demo_module_6.o demo_module_6.c
	$(LD) $(DLFLAGS) $(LIBS1) -o demo_module_6.so demo_module_6.o

