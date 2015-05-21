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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libksba
COMPONENT_VERSION=	1.3.2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.gnupg.org/related_software/libksba/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:eb95537955dfc2845690a4cc3836074fa6d0a2c2ca2cbf1759364d3bd9868406
COMPONENT_ARCHIVE_URL=	ftp://ftp.gnupg.org/gcrypt/libksba/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/gnupg

TPNO=			21897

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Enable C99 mode + -Xc for its additional warnings.
studio_C99MODE = -Xc $(studio_C99_ENABLE)

# -xinline=%auto -- we like inlining where appropriate
CFLAGS += -xinline=%auto

# -xbuiltin=%none -- builtins have been known to be buggy
CFLAGS += -xbuiltin=%none

CFLAGS += $(CPP_LARGEFILES)
CFLAGS += $(XPG6MODE)
CFLAGS += $(CPP_POSIX)
CFLAGS += $(CPP_C99_EXTENDED_MATH)
CFLAGS += $(studio_PIC)

COMPONENT_TEST_MASTER = \
	$(COMPONENT_TEST_RESULTS_DIR)/results-libksba.master

CONFIGURE_ENV +=	CFLAGS="$(CFLAGS)"
CONFIGURE_ENV +=	INSTALL="$(INSTALL)"

CONFIGURE_OPTIONS  +=		--localstatedir=/var
CONFIGURE_OPTIONS  +=		--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=		--enable-shared
CONFIGURE_OPTIONS  +=		--disable-static
CONFIGURE_OPTIONS  +=		--disable-silent-rules
CONFIGURE_OPTIONS  +=		--with-gpg-error-prefix=$(CONFIGURE_PREFIX)
CONFIGURE_OPTIONS  +=		--with-pic

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

configure:	$(CONFIGURE_32_and_64)

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

REQUIRED_PACKAGES += library/security/libgpg-error
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
