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
# Makefile to generate libhealthMonitor.so
# 
# usage:
# "make" : generate library for 64bit / sparc
# "make ARCH=32" : generate library for 32bit / sparc
# "make ARCH=32 MACH=x86" : generate library for 32bit / x86
# "make ARCH=amd64" : generate 64bit AMD64 libraries
# "make clean" : remove *.o , *.so
#


MARCH=$(ARCH)
LDFLAGS_sparcv9=-m64  -I$(ROOT)$(CFGPREFIX)/include -I.
LDFLAGS_32=-I$(ROOT)$(CFGPREFIX)/include -I.
LDFLAGS_amd64=-m64 -I$(ROOT)$(CFGPREFIX)/include -I.
LDFLAGS=$(LDFLAGS_$(MARCH))

CFLAGS_32=-fpic
CFLAGS_sparcv9=-fpic
CFLAGS_amd64=-fpic
CFLAGS=$(CFLAGS_$(MARCH))

LDLIBS_sparcv9= -L/usr/lib/sparcv9 -l kstat
LDLIBS_32= -l kstat
LDLIBS_amd64= -L /usr/lib/amd64 -lkstat
LDLIBS=$(LDLIBS_$(MARCH))


TARGET= libhealthMonitor.so
PROG= libhealthMonitor.so
SRCS= dsr.c kr_iostat.c kr_memory.c kr_nfsstat.c kr_vmstat.c healthMonitor.c
OBJS = $(SRCS:.c=.o)

all: $(PROG)
$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) $(LDLIBS) -G -o $@ $(OBJS)
.c.o:
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ -c $<
clean:
	rm -f *.o *.so

install:
	/usr/bin/cp health_monitor.conf $(ROOT)/etc/net-snmp/snmp ; \
