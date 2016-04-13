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
COMPONENT_VERSION=	0.19.6
IPS_PKG_NAME=		text/gnu-gettext
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/gettext/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:9b95816620fd1168cb4eeca0e9dc0ffd86e864fc668f76f5e37cc054d6982e51
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/pub/gnu/gettext/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/gnu-gettext

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CONFIGURE_OPTIONS  +=		--disable-java
CONFIGURE_OPTIONS  +=		--disable-libasprintf
CONFIGURE_OPTIONS  +=		--without-emacs
CONFIGURE_OPTIONS  +=		--disable-openmp
CONFIGURE_OPTIONS  +=		--disable-static
#CONFIGURE_OPTIONS  +=		--disable-shared

# Fixes coredump in gnulib-test/test-localename test
CONFIGURE_OPTIONS  +=		ac_cv_func_newlocale=no

# Tests should run in a clean environment
COMPONENT_TEST_ENV =	-i
COMPONENT_TEST_ENV +=	PATH=${PATH}

# Strip compilation lines from test output
COMPONENT_TEST_TRANSFORMS += \
    '-e "s|^.*$(CC).*$$|XXX_CC_XXX|g" ' \
    '-e "s|^.*source=.*libtool=no.*$$|XXX_CC_XXX|g" ' \
    '-e "s|^.*DEPDIR=.deps.*$$|XXX_CC_XXX|g" ' \
    '-e "/^XXX_CC_XXX$$/d" '


# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(TEST_32)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
