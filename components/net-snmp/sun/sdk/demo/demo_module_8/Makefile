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
#
# Makefile to generate demo_module_8.so
# 
# usage:
# setenv CC /usr/bin/cc (or correct path)
# "make" : generate library for 64bit
# "make ARCH=32" : generate library for 32bit
# "make clean" : remove *.o , *.so
#

INSTALL_PATH=/usr
ARCH=64
#LDFLAGS_64=-g -m64 -I$(INSTALL_PATH)/include -I.
#LDFLAGS_32=-g -I$(INSTALL_PATH)/include -I.
#LDFLAGS=$(LDFLAGS_$(ARCH))

OBJS1=demo_module_8.o me1LoadGroup.so
TARGETS=demo_module_8
LD=/usr/ccs/bin/ld

CFLAGS=-I. `$(INSTALL_PATH)/bin/net-snmp-config-$(ARCH) --cflags`
BUILDLIBS=`$(INSTALL_PATH)/bin/net-snmp-config-$(ARCH) --libs`
BUILDAGENTLIBS=`$(INSTALL_PATH)/bin/net-snmp-config-$(ARCH) --agent-libs`

# shared library flags (assumes gcc)
#DLFLAGS=-fPIC -shared
# shared library flags (assumes cc)
DLFLAGS=-dy -G

# compile subagent
all: $(TARGETS)

# link subagent object, shared library module, and agent libs
# and output demo_module_8, the subagent.
demo_module_8: $(OBJS1)
	$(CC) -o demo_module_8  $(OBJS1) $(BUILDLIBS) $(BUILDAGENTLIBS)

clean: 
	rm $(OBJS1) $(TARGETS)

# compile module source, producing module object file
# produce (-G) and load module shared object from module object file, 
# using dynamic linking (-dy)
me1LoadGroup.so: me1LoadGroup.o Makefile
	$(CC) $(CFLAGS) -c -o me1LoadGroup.o me1LoadGroup.c
	$(LD) $(DLFLAGS) -o me1LoadGroup.so me1LoadGroup.o

