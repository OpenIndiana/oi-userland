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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS =            64_and_32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		p11-kit
COMPONENT_VERSION=	0.23.2
COMPONENT_PROJECT_URL=	http://p11-glue.freedesktop.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:ba726ea8303c97467a33fca50ee79b7b35212964be808ecf9b145e9042fdfaf0
COMPONENT_ARCHIVE_URL=	http://p11-glue.freedesktop.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	gnome/security

TPNO=			32885	

# Needs header updates from ON, available in S12 but not S11.
ifeq ($(BUILD_TYPE), evaluation)
BUILD_32_and_64=
INSTALL_32_and_64=
PUBLISH_STAMP=
endif

include $(WS_MAKE_RULES)/common.mk

studio_C99MODE=$(studio_C99_ENABLE)

# Needed due to patch to automake-related files.
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv);

CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += --enable-doc
CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS.32 += --with-module-path=/usr/lib/security
CONFIGURE_OPTIONS.64 += --with-module-path=/usr/lib/security/$(MACH64)
CONFIGURE_OPTIONS += --with-trust-paths=/etc/certs/ca-certificates.crt

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(BITS).master
COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/TOTAL:/p" ' \
        '-e "/SKIP:/p" ' \
        '-e "/PASS:/p" ' \
        '-e "/FAIL:/p" ' \
        '-e "/ok/p" ' \
        '-e "/ERROR:/p" '

REQUIRED_PACKAGES += developer/build/automake-115
REQUIRED_PACKAGES += developer/build/gnu-make
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc 
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/libtasn1
REQUIRED_PACKAGES += library/libxslt
