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
# Copyright (c) 2015, 2017, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		liboauth
COMPONENT_VERSION=	1.0.3
COMPONENT_SUMMARY=	A library for processing data according to the oAuth standard
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  http://sourceforge.net/projects/liboauth
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:0df60157b052f0e774ade8a8bac59d6e8d4b464058cc55f9208d72e41156811f
COMPONENT_ARCHIVE_URL=  http://sourceforge.net/projects/$(COMPONENT_NAME)/files/$(COMPONENT_ARCHIVE)/download
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_FMRI=	library/liboauth
COMPONENT_LICENSE= MIT
COMPONENT_LICENSE_FILE= COPYING.MIT

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS += --disable-static
# Use NSS backend instead of OpenSSL backend due to GPL-licensed components
# that link against liboauth and thus would have to link against OpenSSL and
# cannot.
CONFIGURE_OPTIONS += --enable-nss
CONFIGURE_OPTIONS += --localstatedir="$(VARDIR)"
CONFIGURE_OPTIONS += --sysconfdir="$(ETCDIR)"
CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_ENV += SED="$(GSED)"

# Required to use generate and use non-broken version of libtool macros.
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv);

# for the tests
unexport SHELLOPTS
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_ARGS =   -k -i
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/TOTAL:/p" ' \
        '-e "/SKIP:/p" ' \
        '-e "/PASS:/p" ' \
        '-e "/FAIL:/p" ' \
        '-e "/ERROR:/p" '

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

# Build dependencies
REQUIRED_PACKAGES += developer/documentation-tool/doxygen
REQUIRED_PACKAGES += image/graphviz

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/mozilla-nss
REQUIRED_PACKAGES += web/curl
