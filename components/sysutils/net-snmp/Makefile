#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
# net-snmp has a "special" build where only 32-bit items are installed into
# proto area; so prefer 32-bit to preserve existing sourcing.
#

#
# Copyright 2016 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved.
#

include ../../../make-rules/shared-macros.mk

DOXYGEN= /usr/bin/doxygen
PATH=$(VPATH):$(PATH.gnu)

COMPONENT_NAME=		net-snmp
COMPONENT_VERSION=	5.7.3
COMPONENT_REVISION=	4
COMPONENT_FMRI=	system/management/snmp/net-snmp
COMPONENT_PROJECT_URL=	http://www.net-snmp.org/
COMPONENT_SRC=    $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:12ef89613c7707dc96d13335f153c1921efc9d61d3708ef09f3fc4a7014fb4f0
COMPONENT_ARCHIVE_URL=	http://ftp.ntua.gr/mirror/net-snmp/net-snmp/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION= System/Enterprise Management
COMPONENT_SUMMARY= Net-SNMP Agent files and libraries

BUILD_32_and_64 += $(BUILD_DIR_32)/.docs

COMPONENT_BUILD_ARGS=
include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
  ($(CLONEY) $(SOURCE_DIR) $(@D); $(CLONEY) $(COMPONENT_DIR)/sun $(@D)/sun)

CPPFLAGS += "-DFALSE_SHARING_ALIGN=64"

CONFIGURE_ENV +=	PYTHONPROG=$(PYTHON.$(BITS))
CONFIGURE_ENV.32     += PERL=$(PERL.5.22)
CONFIGURE_ENV.64     += PERL=$(PERL.5.24)

CONFIGURE_OPTIONS  += --srcdir=$(@D)
CONFIGURE_OPTIONS  +=	--with-default-snmp-version=3
CONFIGURE_OPTIONS  +=	--with-sys-contact="root@localhost"
CONFIGURE_OPTIONS  +=	--with-sys-location=Unknown
CONFIGURE_OPTIONS  +=	--with-logfile=$(VARDIR)/log/snmpd.log
CONFIGURE_OPTIONS  +=	--with-persistent-directory=$(VARDIR)/net-snmp

CONFIGURE_OPTIONS  +=	--with-mibdirs=$(ETCDIR)/net-snmp/snmp/mibs
CONFIGURE_OPTIONS  +=	--datadir=$(ETCDIR)/net-snmp
CONFIGURE_OPTIONS  +=	--enable-ucd-snmp-compatibility
CONFIGURE_OPTIONS  +=	--enable-ipv6
CONFIGURE_OPTIONS  +=	--enable-mfd-rewrites
CONFIGURE_OPTIONS  +=	--with-openssl=/lib/openssl
CONFIGURE_OPTIONS  += --sysconfdir=$(ETCDIR)/net-snmp

# Which MIB modules do we want to build
MIB_MOBULES.sparc = ucd-snmp/lmSensors
MIB_MOBULES.i386 = ucd-snmp/lmSensors
MIB_MODULES = host disman/event-mib ucd-snmp/diskio udp-mib tcp-mib if-mib
MIB_MOBULES += $(MIB_MODULES.$(MACH))
CONFIGURE_OPTIONS  +=	--with-mib-modules="$(MIB_MODULES)"

# Python bindings support.
PYTHON_ARGS =		--basedir=/usr/bin
CONFIGURE_OPTIONS  +=	--with-python-modules="$(PYTHON_ARGS)"

# Only build 64 bit Perl support
PERL_ARGS =	DESTDIR=$(PROTO_DIR) INSTALLDIRS=vendor
CONFIGURE_OPTIONS.32  +=  PERLPROG="$(PERL.5.22)"
CONFIGURE_OPTIONS.32  +=	--disable-embedded-perl
CONFIGURE_OPTIONS.32  +=  --with-perl-modules="$(PERL_ARGS)"
CONFIGURE_OPTIONS.64  +=	PERLPROG="$(PERL.5.24)"
CONFIGURE_OPTIONS.64  +=  --disable-embedded-perl
CONFIGURE_OPTIONS.64  +=	--with-perl-modules="$(PERL_ARGS)"

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D); $(CLONEY) $(COMPONENT_DIR)/sun $(@D)/sun)

# for the goofy definition of ARCH in the extra Makefiles
ARCH=32
ARCH=$(BITS:64=$(MACH64))

CCSMAKE_ARGS =	CC="$(CC)" CFGPREFIX=$(USRDIR) CFGLIB64=$(USRLIBDIR64)
CCSMAKE_ARGS +=	CFGLIB=$(USRLIBDIR) ARCH=$(ARCH) ROOT=$(PROTO_DIR)

# Test section, use ./RUNTESTS or ./RUNFULLTESTS
COMPONENT_TEST_DIR = $(BUILD_DIR)/$(MACH$(BITS))/testing/
## Get correct binaries from the proto area.
TEST_BINPATH.32 =	$(PROTOUSRBINDIR)
TEST_BINPATH.64 =	$(BUILD_DIR)/prototype/$(MACH64)$(USRBINDIR64)
# Get correct libraries from the proto area.
TEST_LIBPATH.32 =	$(PROTOUSRLIBDIR)
TEST_LIBPATH.64 =	$(BUILD_DIR)/prototype/$(MACH64)$(USRLIBDIR64)
# use the same perl as in build
TEST_PERL.32 = $(PERL.5.22)	
TEST_PERL.64 = $(PERL.5.24)
#
# use 72 tests in default
# COMPONENT_TEST_CMD =	$(KSH93)
# COMPONENT_TEST_TARGETS =	./RUNTESTS
# or all tests found
COMPONENT_TEST_ENV +=	TESTOPTS='-g all'
COMPONENT_TEST_CMD =	$(TEST_PERL.$(BITS))
COMPONENT_TEST_TARGETS =	./RUNFULLTESTS
#
# provide new results-$(BITS).master if number of tests change: delete runtime specific measurements after second comma
# original: Files=72, Tests=320, 94 wallclock secs ( 0.21 usr  0.11 sys +  8.76 cusr  1.92 csys = 11.00 CPU)
# edited:   Files=72, Tests=320,
# the transform provides the edited version
COMPONENT_TEST_TRANSFORMS +=  '-re "/Files=72, Tests=320,/s/([^,]+,[^,]+,*).*/\1/"'
COMPONENT_TEST_MASTER =	$(COMPONENT_TEST_RESULTS_DIR)/results-$(BITS).master
COMPONENT_TEST_ENV +=	PATH=$(TEST_BINPATH.$(BITS)):$(PATH)
COMPONENT_TEST_ENV +=	LD_LIBRARY_PATH=$(TEST_LIBPATH.$(BITS))
#

# perl man pages hiding here in 64-bit PROTO_DIR
PKG_PROTO_DIRS += $(BUILD_DIR)/prototype/$(MACH64)

COMPONENT_INSTALL_ARGS += PYTHON_VENDOR_PACKAGES=$(PYTHON_VENDOR_PACKAGES.32)

$(BUILD_32): COMPONENT_POST_BUILD_ACTION= \
	(cd $(BUILD_DIR)/$(MACH32)/sun ; ls agent; $(CCSMAKE) -e $(CCSMAKE_ARGS))

$(BUILD_64): COMPONENT_POST_BUILD_ACTION= \
	(cd $(BUILD_DIR)/$(MACH64)/sun ; ls agent; $(CCSMAKE) -e $(CCSMAKE_ARGS))

$(INSTALL_32): COMPONENT_POST_INSTALL_ACTION= \
	($(MKDIR) -p $(BUILD_DIR)/prototype/$(MACH)/etc/net-snmp/snmp/mibs; \
	 cd $(BUILD_DIR)/$(MACH32)/sun ; ls agent; $(CCSMAKE) -e $(CCSMAKE_ARGS) install)

$(INSTALL_64): COMPONENT_POST_INSTALL_ACTION= \
	($(MKDIR) -p $(BUILD_DIR)/prototype/$(MACH64)/etc/net-snmp/snmp/mibs; \
	 cd $(BUILD_DIR)/$(MACH64)/sun ; ls agent; $(CCSMAKE) -e $(CCSMAKE_ARGS) install)

$(INSTALL_64): COMPONENT_INSTALL_ARGS += DESTDIR=$(BUILD_DIR)/prototype/$(MACH64)

# common targets
build:  $(BUILD_32) $(BUILD_64) $(BUILD_DIR_32)/.docs

$(INSTALL_64): COMPONENT_INSTALL_ARGS += DESTDIR=$(BUILD_DIR)/prototype/$(MACH64)

install:  build $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

# build the docs
$(BUILD_DIR_32)/.docs:
	(cd $(@D) ; $(ENV) srcdir=$(@D) $(DOXYGEN) -u $(@D)/doxygen.conf ; \
	    $(ENV) srcdir=$(@D) $(DOXYGEN) $(@D)/doxygen.conf)
	$(TOUCH) $@

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += developer/documentation-tool/doxygen
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/network
REQUIRED_PACKAGES += service/picl
REQUIRED_PACKAGES += system/header/header-picl
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
