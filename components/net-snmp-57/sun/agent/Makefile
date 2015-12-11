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
# Makefile for sun/agent directory in SMA
#
# $Log: Makefile,v $
# Revision 1.5  2003/09/18 11:39:08  rr144420
# 4922904 - include sea directory in makefile
#
# Revision 1.4  2003/08/21 14:42:00  rr144420
# 4908816 - further makefile changes to install into correct lib
#
# Revision 1.3  2003/08/12 21:14:36  rr144420
# 4895376 - correct Sun copyright statements. Cannot use (c), and must use Copyright Copyright in makefiles
#
# Revision 1.2  2003/08/01 16:32:16  rr144420
# more of Paul's changes for packaging
#
# Revision 1.1  2003/07/23 15:53:29  rr144420
# new makefiles for building sun directory
# 
#

SUBDIRS		= modules mibs

all:
	@if test "$(SUBDIRS)" != ""; then \
		it="$(SUBDIRS)" ; \
		for i in $$it ; do       \
			echo "making all in `pwd`/$$i"; \
			echo "SUBDIRS2:  $(MAKE) CC=$(CC) DEBUG=$(DEBUG) ARCH=$(ARCH)" ; \
	                ( cd $$i ; $(MAKE) CC=$(CC) DEBUG=$(DEBUG) ARCH=$(ARCH) ROOT=$(ROOT) ) ; \
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
