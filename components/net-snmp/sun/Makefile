#
# Copyright (c) 2008, 2011, Oracle and/or its affiliates. All rights reserved.
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
# Makefile for sun directory in SMA
#
# $Log: Makefile,v $
# Revision 1.10  2004/01/09 14:04:14  rr144420
# 4974843 - directory change per LSARC
#
# Revision 1.9  2003/12/11 16:20:17  rr144420
# 4964336 - eliminate sdk_buildrev
#
# Revision 1.8  2003/12/05 15:04:26  rr144420
# 4964325 - Sun: pass ARCH=isa to make install
#
# Revision 1.7  2003/11/17 17:52:11  pcarroll
# 4953668 - Sun: updated masfcnv migration script needs to be added to pkg
#
# Revision 1.6  2003/11/11 22:49:24  pcarroll
# 4952508 - Sun: need to add a script to SMA pkgs for Enchilada migration
#
# Revision 1.5  2003/10/24 11:45:48  rr144420
# 4943260 - add sdk_buildrev
#
# Revision 1.4  2003/08/21 14:41:58  rr144420
# 4908816 - further makefile changes to install into correct lib
#
# Revision 1.3  2003/08/12 21:14:34  rr144420
# 4895376 - correct Sun copyright statements. Cannot use (c), and must use Copyright Copyright in makefiles
#
# Revision 1.2  2003/08/01 16:32:12  rr144420
# more of Paul's changes for packaging
#
# Revision 1.1  2003/07/23 15:53:28  rr144420
# new makefiles for building sun directory
# 
#
SUBDIRS		= agent
BUILDREV_SRCS   = sma_buildrev.c
BUILDREV_PROGS = $(BUILDREV_SRCS:.c=)
SCRIPT_PROG	= masfcnv \
		masfd \
		snmpd.conf

all: subdirs buildrevs

buildrevs:$(BUILDREV_PROGS)
.c:
	$(CC) $< -o $@

subdirs:
	echo "SUBDIRS:  $(MAKE) CFGPREFIX=$(CFGPREFIX) CFGLIB64=$(CFGLIB64) CFGLIB=$(CFGLIB) CC=$(CC) DEBUG=$(DEBUG) ARCH=$(ARCH)" ; 
	@if test "$(SUBDIRS)" != ""; then \
		it="$(SUBDIRS)" ; \
		for i in $$it ; do       \
			echo "making all in `pwd`/$$i"; \
	                ( cd $$i ; $(MAKE) CFGPREFIX=$(CFGPREFIX) CFGLIB64=$(CFGLIB64) CFGLIB=$(CFGLIB) CC=$(CC) DEBUG=$(DEBUG) ARCH=$(ARCH) ) ; \
                        if test $$? != 0 ; then \
				exit 1 ; \
			fi  \
	        done \
	fi

subdirs_install:
	@if test "$(SUBDIRS)" != ""; then \
		it="$(SUBDIRS)" ; \
		for i in $$it ; do       \
			echo "making install in `pwd`/$$i"; \
	                ( cd $$i ; $(MAKE) CFGPREFIX=$(CFGPREFIX) CFGLIB64=$(CFGLIB64) CFGLIB=$(CFGLIB) install ARCH=$(ARCH) ) ; \
                        if test $$? != 0 ; then \
				exit 1 ; \
			fi  \
	        done \
	fi

install: subdirs_install

force:
# dummy target to force rebuilding
