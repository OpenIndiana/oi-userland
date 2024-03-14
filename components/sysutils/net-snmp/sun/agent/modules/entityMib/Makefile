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
# Makefile to generate libentity.so
# 

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
