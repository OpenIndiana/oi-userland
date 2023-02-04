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
# Copyright (c) 2022, Niklas Poslovski
#

USE_OPENSSL11= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		bind
COMPONENT_VERSION=	9.16.37
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_PROJECT_URL=	https://www.isc.org/software/bind/
COMPONENT_ARCHIVE_HASH=	sha256:0e4661d522a2fe1f111c1f0685e7d6993d657f81dae24e7a75dbd8db3ef2e2ab
COMPONENT_ARCHIVE_URL=	https://ftp.isc.org/isc/bind9/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=			network/dns/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=	Applications/Internet
COMPONENT_LICENSE=	MPL v2.0
COMPONENT_LICENSE_FILE=	COPYRIGHT

include $(WS_MAKE_RULES)/common.mk

PKG_MACROS += PYVER=$(PYTHON_VERSION)

COMPONENT_PREP_ACTION= (cd $(@D) && autoreconf -fi)

# Missing files in build dir without this.
COMPONENT_PRE_CONFIGURE_ACTION= ($(CLONEY) $(SOURCE_DIR) $(@D))

CFLAGS += $(CPP_XPG6MODE)

# Build.
#
# FYI, The configure options are displayed by 'named -V'.  Previously
# that was overriden by setting CONFIGARGS to hide build server
# pathnames.

# DNS libraries are in usr/lib/dns - Override settings from configure.mk
CONFIGURE_LIBDIR.64= $(CONFIGURE_PREFIX)/lib/dns/$(MACH64)

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-libtool
CONFIGURE_OPTIONS += --sysconfdir=/etc
CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --with-openssl=/usr
CONFIGURE_OPTIONS += --enable-devpoll=yes
CONFIGURE_OPTIONS += --enable-fixed-rrset
CONFIGURE_OPTIONS += --with-pkcs11=/usr/lib/$(MACH64)/libpkcs11.so
CONFIGURE_OPTIONS += --with-libxml2
CONFIGURE_OPTIONS += --with-python-install-dir=$(PYTHON_VENDOR_PACKAGES.32)
CONFIGURE_OPTIONS += --with-json-c

CONFIGURE_ENV += PYTHON=$(PYTHON)

COMPONENT_BUILD_ENV += PYTHON_VENDOR_DIR=$(PYTHON_VENDOR_PACKAGES)
COMPONENT_INSTALL_ENV += PYTHON_VENDOR_DIR=$(PYTHON_VENDOR_PACKAGES)

# Install.
#
# Currently manual pages are distributed from pkg:/system/manual@.
# While there are some changes in our manuals, additions to named(1M) for SMF - that could be fixed
# by a patch.
#
# In addition to BIND deliverables we also deliver SMF files and
# migration notes.  There is no need to install these extras into the
# prototype directory, they are simply referenced in relevant manifest
# (p5m) file.

COMPONENT_TEST_ENV += PATH=$(PATH.gnu)
COMPONENT_TEST_ENV += LC_ALL=C.UTF-8
# The user running the test needs an profiles=Network Management entry in /etc/user_attr in order to successfully run the following ifconfig.sh up script:
COMPONENT_PRE_TEST_ACTION= ( cd $(BUILD_DIR_64)/bin/tests/system && pfexec sh ./ifconfig.sh up )
COMPONENT_POST_TEST_ACTION= ( cd $(BUILD_DIR_64)/bin/tests/system && pfexec sh ./ifconfig.sh down )
COMPONENT_TEST_TARGETS= test
COMPONENT_TEST_TRANSFORMS += \
	' -n ' \
	' -e "/^R:.*:FAIL/p"' \
	' -e "/^I:System test result summary/p"' \
	' -e "/^I:.* PASS$$/p"' \
	' -e "/^I:.* FAIL$$/p"' \
	' -e "/^I:.* SKIPPED$$/p"' \
	' -e "/^I:.* UNTESTED$$/p"'

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += database/lmdb
REQUIRED_PACKAGES += library/json-c
REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/libuv
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/gss
