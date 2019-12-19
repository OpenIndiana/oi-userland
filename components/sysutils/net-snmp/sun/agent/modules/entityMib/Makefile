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
#

#
#
# Makefile to generate libentity.so
# 
# usage:
# "make" : generate library for 64bit / sparc
# "make ARCH=32" : generate library for 32bit / sparc
# "make ARCH=32 MACH=x86" : generate library for 32bit / x86
# "make ARCH=amd64" : generate 64bit AMD64 libraries
# "make clean" : remove *.o , *.so
#

MARCH=$(ARCH)
LDFLAGS_sparcv9=-m64 -I$(ROOT)$(CFGPREFIX)/include -I.
LDFLAGS_32=-I$(ROOT)$(CFGPREFIX)/include -I.
LDFLAGS_amd64=-m64 -I$(ROOT)$(CFGPREFIX)/include -I.
LDFLAGS=$(LDFLAGS_$(MARCH))

LDLIBS=

CFLAGS_32=-fpic
CFLAGS_sparcv9=-fpic
CFLAGS_amd64=-fpic
CFLAGS=$(CFLAGS_$(MARCH))

PROG= libentity.so
SRCS= entPhysicalTable.c entLPMappingTable.c entPhysicalContainsTable.c \
	entLogicalTable.c entAliasMappingTable.c entLastChangeTime.c entity.c

OBJS = $(SRCS:.c=.o)

HEADERS= \
	entAliasMappingTable.h \
	entLogicalTable.h \
	stdhdr.h \
	entLPMappingTable.h \
	entPhysicalContainsTable.h \
	entLastChangeTime.h \
	entPhysicalTable.h


all:$(PROG)
$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) $(LDLIBS) -G -o $@ $(OBJS)
.c.o:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<

clean:
	rm -f entPhysicalTable.o entLPMappingTable.o \
	entPhysicalContainsTable.o entLogicalTable.o \
	entAliasMappingTable.o entLastChangeTime.o entity.o libentity.so

install:
	if test "$(ARCH)" = "sparcv9" ; then \
		cp $(PROG) $(ROOT)/$(CFGLIB64); \
	elif test "$(ARCH)" = "32" ; then \
		cp $(PROG) $(ROOT)/$(CFGLIB); \
	elif test "$(ARCH)" = "amd64" ; then \
		cp $(PROG) $(ROOT)/$(CFGLIB64); \
	fi

#all
#cp $(PROG) /usr/local/lib
