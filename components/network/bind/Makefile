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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2020, Michal Nowak
#

BUILD_BITS=			64
USE_OPENSSL11=		yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		bind
COMPONENT_VERSION=	9.16.15
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_PROJECT_URL=	https://www.isc.org/software/bind/
COMPONENT_ARCHIVE_HASH=	sha256:98b6f432d878a7bf8f57eb7b3c28be27278cf6b9989154bfe6c81104b38e7839
COMPONENT_ARCHIVE_URL=	https://ftp.isc.org/isc/bind9/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	MPL v2.0
COMPONENT_LICENSE_FILE=	COPYRIGHT

include $(WS_MAKE_RULES)/common.mk

PYTHON_VERSION=3.5

COMPONENT_PREP_ACTION =	(cd $(@D) && autoreconf -fi)

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))

CFLAGS += $(CPP_XPG6MODE)

# Build.
#
# FYI, The configure options are displayed by 'named -V'.  Previously
# that was overriden by setting CONFIGARGS to hide build server
# pathnames.

# DNS libraries are in usr/lib/dns - Override settings from configure.mk
CONFIGURE_LIBDIR.64 =	$(CONFIGURE_PREFIX)/lib/dns/$(MACH64)

CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS +=	--with-libtool
CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--localstatedir=/var
CONFIGURE_OPTIONS +=	--with-openssl=/usr
CONFIGURE_OPTIONS +=	--enable-devpoll=yes
CONFIGURE_OPTIONS +=	--enable-fixed-rrset
CONFIGURE_OPTIONS +=	--with-pkcs11=/usr/lib/$(MACH64)/libpkcs11.so
CONFIGURE_OPTIONS +=	--with-libxml2
CONFIGURE_OPTIONS +=	--with-python-install-dir=$(PYTHON_VENDOR_PACKAGES.32)
CONFIGURE_OPTIONS +=	--with-json-c

CONFIGURE_ENV +=	PYTHON=$(PYTHON)

COMPONENT_BUILD_ENV += PYTHON_VENDOR_DIR=$(PYTHON_VENDOR_PACKAGES)
COMPONENT_INSTALL_ENV += PYTHON_VENDOR_DIR=$(PYTHON_VENDOR_PACKAGES)

# Install.
#
# Currently manual pages are distributed from pkg:/system/manual@.
# While there are some changes in our manuals, for example section
# numbering and additions to named(1M) for SMF - that could be fixed
# by patch.
#
# In addition to BIND deliverables we also deliver SMF files and
# migration notes.  There is no need to install these extras into the
# prototype directory, they are simply referenced in relevant manifest
# (p5m) file.

install: $(INSTALL_64)

COMPONENT_TEST_ENV += PATH=$(PATH.gnu)
COMPONENT_TEST_ENV += LC_ALL=C LC_TIME=C LC_MONETARY=C
COMPONENT_PRE_TEST_ACTION=	cd $(BUILD_DIR_64)/bin/tests/system ; pfexec sh ./ifconfig.sh up ;
COMPONENT_TEST_TARGETS=		test
COMPONENT_TEST_TRANSFORMS += \
	' -n ' \
	' -e "/^R:.*:FAIL/p"' \
	' -e "/^I:System test result summary/p"' \
	' -e "/^I:.* PASS$$/p"' \
	' -e "/^I:.* FAIL$$/p"' \
	' -e "/^I:.* SKIPPED$$/p"' \
	' -e "/^I:.* UNTESTED$$/p"'

# Use COMPONENT_TEST_ARGS to parallelize the task.
$(TEST_64):	$(INSTALL_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += database/lmdb
REQUIRED_PACKAGES += library/json-c
REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/libuv
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/zlib
#REQUIRED_PACKAGES += network/dns/bind
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/gss
