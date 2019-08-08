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
#

PREFERRED_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		bind
COMPONENT_VERSION=	9.14.4
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	http://www.isc.org/software/bind/
COMPONENT_ARCHIVE_HASH=	 \
	sha256:312efb82a6889074f31ef2849af498b3ec97ca69acd5c4e5e4b4045a8fe6b83f
COMPONENT_ARCHIVE_URL=	\
	http://ftp.isc.org/isc/bind9/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	MPL v2.0
COMPONENT_LICENSE_FILE=	COPYRIGHT

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

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

CONFIGURE_OPTIONS +=	--with-libtool
CONFIGURE_OPTIONS +=	--sysconfdir=/etc
CONFIGURE_OPTIONS +=	--localstatedir=/var
CONFIGURE_OPTIONS +=	--with-openssl=/usr
CONFIGURE_OPTIONS +=	--enable-devpoll=yes
CONFIGURE_OPTIONS +=	--enable-fixed-rrset
CONFIGURE_OPTIONS +=	--with-pkcs11=/usr/lib/$(MACH64)/libpkcs11.so
# Bind configure will check for libxml2 versions 2.6.x/2.7.x/2.8.x.
# To make it use version 2.9.x we need to skip this check by
# specifying path where libxml2 is installed.
CONFIGURE_OPTIONS +=	--with-libxml2=/usr
CONFIGURE_OPTIONS +=	--with-python-install-dir=$(PYTHON_VENDOR_PACKAGES.32)

CONFIGURE_ENV +=	PYTHON=$(PYTHON)

COMPONENT_BUILD_ENV += PYTHON_VENDOR_DIR=$(PYTHON_VENDOR_PACKAGES)
COMPONENT_INSTALL_ENV += PYTHON_VENDOR_DIR=$(PYTHON_VENDOR_PACKAGES)

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

build:		$(BUILD_64)

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

# Test configuration.
# -------------------
# Target 'test' is run from PROTO_DIR, while 'system-test' uses root
# ("/") directory.
#
# BIND has its own test target which requires IP addresses 10.53.0.1
# through 10.53.0.8 to be configured.  Those are not normally
# configured on the build server so for now do some basic testing
# rather than $(NO_TESTS).
#
TEST_HOSTNAME := $(shell uname -n)
COMPONENT_TEST_TRANSFORMS +=    \
        '-e "s|$(PROTO_DIR)||g" ' \
        '-e "s|$(BUILD_DIR)|\\$$(BUILD_DIR)|g" ' \
        '-e "s|<id:[^>]*>$$|<id:REDACTED>|" ' \
        '-e "s| id: [0-9].*$$| id: REDACTED|g" ' \
        '-e "s| COOKIE: [^ ]* | COOKIE: REDACTED |g" ' \
        '-e "/;; WHEN:/d" ' \
        '-e "/;; Query time:/d" ' \
        '-e "/^REDACT:/d" ' \
        '-e "s|$(TEST_HOSTNAME)*[^$$ ]*|\\$$(HOSTNAME)|g" ' \
        '-e "s|rcvd: [0-9]*|rcvd: REDACTED|"g ' \
        '-e "s|bytes [0-9]*|bytes REDACTED|"g ' \
        '-e "s|$(COMPONENT_VERSION)|\\$$(COMPONENT_VERSION)|g" '

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_ENV +=   LD_LIBRARY_PATH=$(PROTO_DIR)$(CONFIGURE_LIBDIR.64)
COMPONENT_TEST_CMD =    ksh  $(COMPONENT_DIR)/Solaris/testing.ksh
COMPONENT_TEST_ARGS =   -d $(BUILD_DIR)/test/config
COMPONENT_TEST_ARGS +=  -p $(PROTO_DIR)

$(TEST_64):	$(INSTALL_64)

test: $(TEST_64)

.PHONY: test-version
test-version:
	@echo;echo 64 bit version
	-LD_LIBRARY_PATH=$(PROTO_DIR)$(CONFIGURE_LIBDIR.64) \
		$(PROTO_DIR)$(CONFIGURE_BINDIR.64)/named -V

.PHONY: test-clean
test-clean:
	$(RM) $(TEST_64) $(FULL_TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += database/lmdb
REQUIRED_PACKAGES += library/json-c
REQUIRED_PACKAGES += library/libedit
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/python-35
REQUIRED_PACKAGES += service/security/kerberos-5
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/gss
