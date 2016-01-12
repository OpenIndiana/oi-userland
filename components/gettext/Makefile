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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gettext
COMPONENT_VERSION=	0.19.3
IPS_PKG_NAME=		text/gnu-gettext
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/gettext/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:f6fdb29c9ee8ce85c7e574f60ff64fa91cf0f4f018437dfe800227d15595db46
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/pub/gnu/gettext/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/gnu-gettext

TPNO=			20141

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_OPTIONS  +=		--disable-java
CONFIGURE_OPTIONS  +=		--disable-libasprintf
CONFIGURE_OPTIONS  +=		--without-emacs
CONFIGURE_OPTIONS  +=		--disable-openmp
CONFIGURE_OPTIONS  +=		--disable-static
CONFIGURE_OPTIONS  +=		--disable-shared
CONFIGURE_OPTIONS  +=		CFLAGS="$(CFLAGS)"

# Fixes coredump in gnulib-test/test-localename test
CONFIGURE_OPTIONS  +=		ac_cv_func_newlocale=no

# Commands go under /usr/bin so set bindir correctly.
CONFIGURE_BINDIR.64 =	$(CONFIGURE_PREFIX)/bin

# Tests should run in a clean environment
COMPONENT_TEST_ENV =	-i
COMPONENT_TEST_ENV +=	PATH=${PATH}:$(SPRO_VROOT)/bin

# Strip compilation lines from test output
COMPONENT_TEST_TRANSFORMS += \
    '-e "s|^.*$(CC).*$$|XXX_CC_XXX|g" ' \
    '-e "s|^.*source=.*libtool=no.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^.*DEPDIR=.deps.*$$|XXX_CC_XXX|g" ' \
    '-e "/^XXX_CC_XXX$$/d" '

ASLR_MODE = $(ASLR_ENABLE)

# common targets
configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)


REQUIRED_PACKAGES += developer/icu
REQUIRED_PACKAGES += developer/vala
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/icu
REQUIRED_PACKAGES += library/libcroco
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += source/locale/localedef
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += system/locale/extra
