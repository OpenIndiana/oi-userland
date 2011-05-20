
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
#
# Makefile for sun/agent/modules directory in SMA
#
# $Log: Makefile,v $
# Revision 1.7  2003/09/04 17:53:26  rr144420
# 4917378 - remove healthMonitor from makefiles
#
# Revision 1.6  2003/08/21 14:42:01  rr144420
# 4908816 - further makefile changes to install into correct lib
#
# Revision 1.5  2003/08/12 21:14:38  rr144420
# 4895376 - correct Sun copyright statements. Cannot use (c), and must use Copyright Copyright in makefiles
#
# Revision 1.4  2003/08/04 17:10:57  dporter
# 4890836 - build new seaProxy module
#
# Revision 1.3  2003/07/31 21:34:44  pcarroll
# Add seaExtensions to Makefile
#
# Revision 1.2  2003/07/28 19:27:15  augustus
# This is the complete Entity MIB Implementation.
#
# Revision 1.1  2003/07/23 15:53:32  rr144420
# new makefiles for building sun directory
# 
#

# removed healthMonitor

SUBDIRS		= entityMib seaExtensions

all:
	@if test "$(SUBDIRS)" != ""; then \
		it="$(SUBDIRS)" ; \
		for i in $$it ; do       \
			echo "making all in `pwd`/$$i"; \
			echo "SUBDIRS3:  $(MAKE) CC=$(CC) DEBUG=$(DEBUG) ARCH=$(ARCH)" ; \
	                ( cd $$i ; $(MAKE) CC=$(CC) DEBUG=$(DEBUG) ARCH=$(ARCH) ROOT=$(ROOT) ) ; \
			echo "====> Makeing in dir $$i"; \
                        if test $$? != 0 ; then \
				exit 1 ; \
			fi  \
	        done \
	fi

install:
	@if test "$(SUBDIRS)" != ""; then \
		it="$(SUBDIRS)" ; \
		for i in $$it ; do       \
			echo "making install in `pwd`/$$i"; \
	                ( cd $$i ; $(MAKE) install ARCH=$(ARCH) ) ; \
                        if test $$? != 0 ; then \
				exit 1 ; \
			fi  \
	        done \
	fi
