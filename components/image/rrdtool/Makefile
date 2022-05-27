#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2013 Alexander Pyhalov.  All rights reserved.
# Copyright 2022 Friedrich Kink.  All rights reserved.
#

BUILD_STYLE=configure
BUILD_BITS=64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		rrdtool

COMPONENT_VERSION=	1.8.0
COMPONENT_FMRI=		image/rrdtool
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_SUMMARY=	Data analysis tool generating graphical representations
COMPONENT_DESCRIPTION=	RRDtool is the OpenSource industry standard, high performance data \
			logging and graphing system for time series data. RRDtool can be \
			easily integrated in shell scripts, perl, python, ruby, lua or tcl \
			applications.
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:bd37614137d7a8dc523359648eb2a81631a34fd91a82ed5581916a52c08433f4
COMPONENT_ARCHIVE_URL=	https://github.com/oetiker/rrdtool-1.x/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://github.com/oetiker/rrdtool-1.x
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	LICENSE

PERL_VERSION=		5.34

PYTHON_VERSION=		3.7

RUBY_VER=		2.6

PATH=/usr/ruby/$(RUBY_VER)/bin:$(PATH.gnu)
RUBY_LIB_VER=2.6.0

include $(WS_MAKE_RULES)/common.mk

#rrd_config.h is obviously a leftover of a configure run in original source directors
#as such it has precedence in include search path (includes features.h which does not exist 
#in openindiana. Simply deleting is save as configure run will just create a correct 
#rrd_config.h ind build directory
COMPONENT_PREP_ACTION= (cd $(@D) && /bin/rm -f src/rrd_config.h && bootstrap ) 

COMPONENT_POST_INSTALL_ACTION=	$(shell /bin/chmod -R u+w $(@D) )

CONFIGURE_ENV+=		PYTHON=python$(PYTHON_VERSION)
CONFIGURE_ENV+=		PERL=$(PERL)
CONFIGURE_ENV+=		PERLCC=$(CC)
# current gcc builds 32-bit by default which leads to the following error.
# error "LONG_BIT definition appears wrong for platform (bad gcc/glibc config?)."
# This setting fixes the issue with headers not found for python
CONFIGURE_OPTIONS+=	CPPFLAGS=-m64
CONFIGURE_OPTIONS+=	--with-ruby-options="sitedir=/usr/ruby/$(RUBY_VER)/lib/ruby/$(RUBY_LIB_VER)/$(MACH64)-solaris$(SOLARIS_VERSION) libdir=/usr/ruby/$(RUBY_VER)/lib/$(MACH64)"
CONFIGURE_OPTIONS+=	--with-perl-options="CC=$(CC) LD=$(CC) LIB=/usr/perl5/$(PERL_VERSION)/lib"
CONFIGURE_OPTIONS+= 	--enable-ruby
CONFIGURE_OPTIONS+= 	--enable-tcl
CONFIGURE_OPTIONS+= 	--enable-python
CONFIGURE_OPTIONS+= 	--enable-static=no
CONFIGURE_OPTIONS+=	--without-systemdsystemunitdir

# Needed for "gmake test" to work successfully.
unexport SHELLOPTS

#according to rrdtool github inside rpn2 does not work, therefor this explicit test enumeration
COMPONENT_TEST_TARGETS = check TESTS="modify1 modify2 modify3 modify4 modify5 tune1 tune2 graph1 rrdcreate dump-restore create-with-source-1 create-with-source-2 create-with-source-3 create-with-source-4 create-with-source-and-mapping-1 create-from-template-1 dcounter1 vformatter1 list1 rpn1 pdp-calc1 xport1 tune1 tune2"
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-64.master
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/^TOTAL/p" ' \
        '-e "/^SKIP/p" ' \
        '-e "/^PASS/p" ' \
        '-e "/^XPASS/p" ' \
        '-e "/^XFAIL/p" ' \
        '-e "/^FAIL/p" ' \
        '-e "/^ERROR/p" '

build: $(BUILD_64)

#RRDs.so is installed with perm 555 which breaks RUNPATH stripping
install: $(INSTALL_64) ; $(shell /bin/chmod -R u+w $(@D) )

test: 	$(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += image/library/libpng16
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += runtime/lua
REQUIRED_PACKAGES += runtime/python-37
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
