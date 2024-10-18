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
# Copyright 2022 Friedrich Kink
# Copyright 2023 Klaus Ziegler
# Copyright 2023 Niklas Poslovski
#

BUILD_BITS=64_and_32
USE_COMMON_TEST_MASTER=no

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		net-snmp
COMPONENT_VERSION=	5.9.4
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=	Net-SNMP Agent files and libraries
COMPONENT_PROJECT_URL=	http://www.net-snmp.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:8b4de01391e74e3c7014beb43961a2d6d6fa03acc34280b9585f4930745b0544
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/net-snmp/files/net-snmp/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		system/management/snmp/net-snmp
COMPONENT_CLASSIFICATION= System/Enterprise Management
COMPONENT_LICENSE=	BSD, BSD-like
COMPONENT_LICENSE_FILE=	COPYING

COMPONENT_FMRI.$(COMPONENT_NAME)-addons =	$(COMPONENT_FMRI)/addons
COMPONENT_SUMMARY.$(COMPONENT_NAME)-addons =	Net-SNMP addon libraries

COMPONENT_FMRI.$(COMPONENT_NAME)-demo =		$(COMPONENT_FMRI)/demo
COMPONENT_SUMMARY.$(COMPONENT_NAME)-demo =	Net-SNMP demo modules

COMPONENT_FMRI.$(COMPONENT_NAME)-32 =		$(COMPONENT_FMRI)/32
COMPONENT_SUMMARY.$(COMPONENT_NAME)-32 =	Net-SNMP 32-bit support

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

DOXYGEN= /usr/bin/doxygen

CONFIGURE_ENV.64 += PERL=$(PERL)

CONFIGURE_OPTIONS += --enable-static=no
# should not be used anylonger
CONFIGURE_OPTIONS += --disable-md5
CONFIGURE_OPTIONS += --with-default-snmp-version=3
CONFIGURE_OPTIONS += --with-sys-contact="root@localhost"
CONFIGURE_OPTIONS += --with-sys-location=Unknown
CONFIGURE_OPTIONS += --with-logfile=$(VARDIR)/log/snmpd.log
CONFIGURE_OPTIONS += --with-persistent-directory=$(VARDIR)/net-snmp
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)/net-snmp
CONFIGURE_OPTIONS += --with-mibdirs=$(ETCDIR)/net-snmp/snmp/mibs
CONFIGURE_OPTIONS += --datadir=$(ETCDIR)/net-snmp
CONFIGURE_OPTIONS += --enable-agentx-dom-sock-only
CONFIGURE_OPTIONS += --enable-ucd-snmp-compatibility
CONFIGURE_OPTIONS += --enable-ipv6
CONFIGURE_OPTIONS += --enable-mfd-rewrites
CONFIGURE_OPTIONS += --with-security-modules="usm ksm tsm"
CONFIGURE_OPTIONS += --without-systemd
CONFIGURE_OPTIONS += --without-kmem-usage #kmem does not work in a zone
CONFIGURE_OPTIONS += --without-rpm
CONFIGURE_OPTIONS += --with-openssl=$(OPENSSL_PREFIX)
CONFIGURE_OPTIONS += --with-transports="UDP TCP UDPIPv6 TCPIPv6 TLSTCP"

# Which MIB modules do we want to build
MIB_MODULES= host disman/event-mib ucd-snmp/diskio udp-mib tcp-mib if-mib mibII/mta_sendmail smux agentx ucd-snmp/lmSensors
CONFIGURE_OPTIONS += --with-mib-modules="$(MIB_MODULES)"

# Python bindings support.
PYTHON_ARGS= --basedir=/usr/bin
CONFIGURE_OPTIONS.64 += --with-python-modules="$(PYTHON_ARGS)"
CONFIGURE_OPTIONS.32 += --with-python-modules="no"

# Only build 64 bit Perl support
PERL_ARGS=		DESTDIR=$(PROTO_DIR) INSTALLDIRS=vendor
CONFIGURE_OPTIONS.64 += PERLPROG="$(PERL)"
CONFIGURE_OPTIONS.64 +=	--disable-embedded-perl
CONFIGURE_OPTIONS.64 += --with-perl-modules="$(PERL_ARGS)"
CONFIGURE_OPTIONS.32 += --disable-perl-cc-checks
CONFIGURE_OPTIONS.32 += --with-perl-modules="no"
CONFIGURE_OPTIONS.32 +=	--disable-embedded-perl

# We do not need agent, applications and scripts for 32-bit
CONFIGURE_OPTIONS.32 += --disable-agent
CONFIGURE_OPTIONS.32 += --disable-applications
CONFIGURE_OPTIONS.32 += --disable-scripts
# Manuals and MIBs built during the 64-bit build are enough.
# We do not need to build them twice.
CONFIGURE_OPTIONS.32 += --disable-manuals
CONFIGURE_OPTIONS.32 += --disable-mibs

COMPONENT_PRE_CONFIGURE_ACTION= \
	($(CLONEY) $(SOURCE_DIR) $(@D); $(CLONEY) $(COMPONENT_DIR)/sun $(@D)/sun;)

ARCH= $(BITS:64=$(MACH64))

CCSMAKE_ARGS= CC="$(CC)" CFLAGS="-I. -fpic $(gcc_OPT)" CFGPREFIX=$(USRDIR)
CCSMAKE_ARGS +=	CFGLIB64=$(USRLIBDIR64) ARCH=$(ARCH) ROOT=$(PROTO_DIR)

COMPONENT_INSTALL_ARGS += PYTHON_VENDOR_PACKAGES=$(PYTHON_VENDOR_PACKAGES)

COMPONENT_TEST_DIR= $(@D)/testing/
COMPONENT_TEST_CMD= $(KSH93)
COMPONENT_TEST_TARGETS= ./RUNTESTS
COMPONENT_TEST_TRANSFORMS += \
	'-e "s|\(simple-\).*|\1XXXXXX|g"' \
	'-e "s|\(output (\)\(.*\)|\2|g"'
# Get correct binaries from the proto area.
COMPONENT_TEST_ENV += PATH=$(PROTOUSRBINDIR):$(PATH)
# Get correct libraries from the proto area.
COMPONENT_TEST_ENV +=   LD_LIBRARY_PATH=$(PROTOUSRLIBDIR$(BITS))

COMPONENT_POST_BUILD_ACTION.64 += \
	(cd $(@D)/sun ; $(CCSMAKE) -e $(CCSMAKE_ARGS)) ;

COMPONENT_POST_INSTALL_ACTION.64 += \
	(cd $(@D)/sun ; $(CCSMAKE) -e $(CCSMAKE_ARGS) install) ;

COMPONENT_POST_INSTALL_ACTION.64 += \
	$(MKDIR) $(PROTOUSRSHAREDOCDIR)/$(COMPONENT_NAME) ; \
	$(CP) -a $(@D)/docs/html $(PROTOUSRSHAREDOCDIR)/$(COMPONENT_NAME) ;

# Install demo files
COMPONENT_POST_INSTALL_ACTION.64 += \
	$(MKDIR) $(PROTOUSRDIR)/demo ; \
	$(CP) -a $(COMPONENT_DIR)/sun/sdk/demo $(PROTOUSRDIR)/demo/net-snmp ; \
	$(CP) -a $(COMPONENT_DIR)/sun/agent/modules/entityMib/*.h $(PROTOUSRDIR)/demo/net-snmp/demo_module_11 ;

# Install the configuration file and smf service
COMPONENT_POST_INSTALL_ACTION.64 += \
	$(INSTALL) -D $(COMPONENT_DIR)/sun/snmpd.conf $(PROTOETCDIR)/net-snmp/snmp/ ; \
	$(INSTALL) -D $(COMPONENT_DIR)/sun/net-snmp.xml $(PROTOLIBDIR)/svc/manifest/application/management/net-snmp.xml ; \
	$(INSTALL) -D $(COMPONENT_DIR)/sun/svc-net-snmp $(PROTOLIBDIR)/svc/method/svc-net-snmp ;

# Drop 32-bit binaries
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOUSRBINDIR32) ;

COMPONENT_PRE_INSTALL_ACTION.64 += ( \
	cd $(@D) ; \
	$(ENV) srcdir=$(@D) $(DOXYGEN) -u $(@D)/doxygen.conf ; \
	$(ENV) srcdir=$(@D) $(DOXYGEN) $(@D)/doxygen.conf; \
	)

REQUIRED_PACKAGES += developer/documentation-tool/doxygen

# Without the picl headers, the build fails on a missing SPARC-specific file.
REQUIRED_PACKAGES += system/header/header-picl

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += service/picl
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libpcap
