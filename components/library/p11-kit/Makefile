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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		p11-kit
COMPONENT_VERSION=	0.23.1
COMPONENT_FMRI=	library/desktop/p11-kit
COMPONENT_SUMMARY=	p11-kit provides a way to load and enumerate PKCS\#11 modules
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_PROJECT_URL=	http://p11-glue.freedesktop.org/
COMPONENT_SRC=	$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:e57371669f3b157141b86c429bd9c29741994b2f5ff115fcb8a03e751b0f6ac4
COMPONENT_ARCHIVE_URL=	http://p11-glue.freedesktop.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= BSD-like
COMPONENT_LICENSE_FILE= p11-kit.license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CFLAGS += -D_POSIX_PTHREAD_SEMANTICS
LDFLAGS += -lsocket -lnsl

# Needed due to patch to automake-related files.
COMPONENT_PREP_ACTION += (cd $(@D); autoreconf -fiv);

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

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64) 

REQUIRED_PACKAGES += developer/build/automake-115
REQUIRED_PACKAGES += developer/build/gnu-make
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc 
REQUIRED_PACKAGES += file/gnu-coreutils
REQUIRED_PACKAGES += library/libffi
REQUIRED_PACKAGES += library/libtasn1
REQUIRED_PACKAGES += library/libxslt
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
