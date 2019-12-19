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
# Copyright (c) 2011, 2019, Oracle and/or its affiliates. All rights reserved.
# Copyright 2019 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved. 
#
BUILD_BITS= 64_and_32

DOXYGEN= /usr/bin/doxygen

include ../../../make-rules/shared-macros.mk

PERL_VERSION=5.24
PERL=$(PERL.$(PERL_VERSION))
PERL_ARCH=$(shell $(PERL) -e 'use Config; print $$Config{archname}')

PATH=$(VPATH):$(PATH.gnu)

COMPONENT_NAME=		net-snmp
COMPONENT_VERSION=	5.8
COMPONENT_PROJECT_URL=	http://www.net-snmp.org/
COMPONENT_FMRI= system/management/snmp/net-snmp
COMPONENT_SRC=    $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:b2fc3500840ebe532734c4786b0da4ef0a5f67e51ef4c86b3345d697e4976adf
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/net-snmp/files/net-snmp/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION= System/Enterprise Management
COMPONENT_SUMMARY= Net-SNMP Agent files and libraries

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CPPFLAGS += "-DFALSE_SHARING_ALIGN=64"

CONFIGURE_ENV +=	PYTHONPROG=$(PYTHON.$(BITS))
CONFIGURE_ENV.32   += PERL=$(PERL.5.22)
CONFIGURE_ENV.64   += PERL=$(PERL.5.24)

CONFIGURE_OPTIONS  +=	--with-default-snmp-version=3
CONFIGURE_OPTIONS  +=	--with-sys-contact="root@localhost"
CONFIGURE_OPTIONS  +=	--with-sys-location=Unknown
CONFIGURE_OPTIONS  +=	--with-logfile=$(VARDIR)/log/snmpd.log
CONFIGURE_OPTIONS  +=	--with-persistent-directory=$(VARDIR)/net-snmp
CONFIGURE_OPTIONS  += --sysconfdir=$(ETCDIR)/net-snmp
CONFIGURE_OPTIONS  +=	--with-mibdirs=$(ETCDIR)/net-snmp/snmp/mibs
CONFIGURE_OPTIONS  +=	--datadir=$(ETCDIR)/net-snmp
CONFIGURE_OPTIONS  +=	--enable-agentx-dom-sock-only
CONFIGURE_OPTIONS  +=	--enable-ucd-snmp-compatibility
CONFIGURE_OPTIONS  +=	--enable-ipv6
CONFIGURE_OPTIONS  +=	--enable-mfd-rewrites
CONFIGURE_OPTIONS  +=	--with-openssl=/lib/openssl
CONFIGURE_OPTIONS  +=	--with-transports="UDP TCP UDPIPv6 TCPIPv6"

# Which MIB modules do we want to build
MIB_MODULES.sparc = ucd-snmp/lmSensors
MIB_MODULES.i386 = ucd-snmp/lmSensors
MIB_MODULES = host disman/event-mib ucd-snmp/diskio udp-mib tcp-mib if-mib
MIB_MODULES += $(MIB_MODULES.$(MACH))
CONFIGURE_OPTIONS  +=	--with-mib-modules="$(MIB_MODULES)"

# Python bindings support.
PYTHON_ARGS =		--basedir=/usr/bin
CONFIGURE_OPTIONS  +=	--with-python-modules="$(PYTHON_ARGS)"

# Only build 64 bit Perl support
PERL_ARGS =			DESTDIR=$(PROTO_DIR) INSTALLDIRS=vendor
CONFIGURE_OPTIONS.32  +=	--disable-embedded-perl
CONFIGURE_OPTIONS.32  +=	--without-perl-modules
CONFIGURE_OPTIONS.64  +=	PERLPROG="$(PERL.5.24)"
CONFIGURE_OPTIONS.64  +=  --disable-embedded-perl
CONFIGURE_OPTIONS.64  +=  --with-perl-modules="$(PERL_ARGS)"

# parallel build not supported
COMPONENT_BUILD_ARGS=

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D); $(CLONEY) $(COMPONENT_DIR)/sun $(@D)/sun;)

ARCH=32
ARCH=$(BITS:64=$(MACH64))

CCSMAKE_ARGS =	CC="$(CC)" CFGPREFIX=$(USRDIR) CFGLIB64=$(USRLIBDIR64)
CCSMAKE_ARGS +=	CFGLIB=$(USRLIBDIR) ARCH=$(ARCH) ROOT=$(PROTO_DIR)

COMPONENT_INSTALL_ARGS += PYTHON_VENDOR_PACKAGES=$(PYTHON_VENDOR_PACKAGES.32)

COMPONENT_TEST_DIR =		$(BUILD_DIR)/$(MACH$(BITS))/testing/
COMPONENT_TEST_CMD =		$(KSH93)
COMPONENT_TEST_TARGETS =	./RUNTESTS
COMPONENT_TEST_TRANSFORMS += \
	'-e "s|\(simple-\).*|\1XXXXXX|g"' \
	'-e "s|\(output (\)\(.*\)|\2|g"'
COMPONENT_TEST_MASTER =	$(COMPONENT_TEST_RESULTS_DIR)/results-$(BITS).master
# Get correct binaries from the proto area.
TEST_BINPATH.32 =       $(PROTOUSRBINDIR)/$(MACH32)
TEST_BINPATH.64 =       $(BUILD_DIR)/prototype/$(MACH64)$(USRBINDIR)
COMPONENT_TEST_ENV +=   PATH=$(TEST_BINPATH.$(BITS)):$(PATH)
# Get correct libraries from the proto area.
TEST_LIBPATH.32 =       $(PROTOUSRLIBDIR)
TEST_LIBPATH.64 =       $(BUILD_DIR)/prototype/$(MACH64)$(USRLIBDIR64)
COMPONENT_TEST_ENV +=   LD_LIBRARY_PATH=$(TEST_LIBPATH.$(BITS))

# perl man pages hiding here in 64-bit PROTO_DIR
PKG_PROTO_DIRS += $(BUILD_DIR)/prototype/$(MACH64)

$(BUILD_32): COMPONENT_POST_BUILD_ACTION= \
	(cd $(BUILD_DIR)/$(MACH32)/sun ; ls agent; $(CCSMAKE) -e $(CCSMAKE_ARGS))

$(BUILD_64): COMPONENT_POST_BUILD_ACTION= \
	(cd $(BUILD_DIR)/$(MACH64)/sun ; ls agent; $(CCSMAKE) -e $(CCSMAKE_ARGS))

$(INSTALL_32): COMPONENT_POST_INSTALL_ACTION= \
	($(MKDIR) -p $(BUILD_DIR)/prototype/$(MACH)/etc/net-snmp/snmp/mibs; \
	 cd $(BUILD_DIR)/$(MACH32)/sun ; ls agent; $(CCSMAKE) -e $(CCSMAKE_ARGS) install)

$(INSTALL_64): COMPONENT_INSTALL_ARGS += DESTDIR=$(BUILD_DIR)/prototype/$(MACH64)

$(INSTALL_64): COMPONENT_POST_INSTALL_ACTION= \
	($(MKDIR) -p $(BUILD_DIR)/prototype/$(MACH64)/etc/net-snmp/snmp/mibs; \
	 cd $(BUILD_DIR)/$(MACH64)/sun ; ls agent; $(CCSMAKE) -e $(CCSMAKE_ARGS) install)

# build the docs
$(BUILD_DIR_32)/.docs:
	(cd $(@D) ; $(ENV) srcdir=$(@D) $(DOXYGEN) -u $(@D)/doxygen.conf ; \
	    $(ENV) srcdir=$(@D) $(DOXYGEN) $(@D)/doxygen.conf)
	$(TOUCH) $@

# common targets
build:  $(BUILD_32) $(BUILD_64) $(BUILD_DIR_32)/.docs

install:  build $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

REQUIRED_PACKAGES += developer/documentation-tool/doxygen
# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += service/picl
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libpcap
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/management/snmp/net-snmp
