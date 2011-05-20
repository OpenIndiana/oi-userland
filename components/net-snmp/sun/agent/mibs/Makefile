#
# Copyright (c) 2003, 2011, Oracle and/or its affiliates. All rights reserved.
#
# U.S. Government Rights - Commercial software. Government users are subject
# to the Sun Microsystems, Inc. standard license agreement and applicable
# provisions of the FAR and its supplements.
#
#
# This distribution may include materials developed by third parties. Sun,
# Sun Microsystems, the Sun logo and Solaris are trademarks or registered
# trademarks of Sun Microsystems, Inc. in the U.S. and other countries.
#
#

#
# Makefile to install mibs
# 
# usage:
# "make install"

# removed health-monitor-mib.mib

MIBFILES= smatrap.mib \
      ENTITY-MIB.txt \
      SUN-MIB.txt \
      SUN-SEA-EXTENSIONS-MIB.txt \
      SUN-SEA-PROXY-MIB.txt

all:
# make all does nothing, but the upper-level makefile calls it

install:
	cp ./$(MIBFILES) $(ROOT)/etc/net-snmp/snmp/mibs
