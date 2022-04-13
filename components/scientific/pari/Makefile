#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2021,2022 David Stes
#


#
# Package Makefile for the "Pari/GP" Computer Algebra System
# See  https://pari.math.u-bordeaux.fr
#

BUILD_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pari
COMPONENT_VERSION=	2.13.4
COMPONENT_SUMMARY=	The PARI Computer Algebra System
COMPONENT_PROJECT_URL=	https://pari.math.u-bordeaux.fr
COMPONENT_FMRI=		library/math/pari
COMPONENT_CLASSIFICATION=	Development/Other Languages

COMPONENT_SRC=		pari-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:bcde9eceae1592814381c1697cdb7063567b6504201b1be47bb58920f3bce185
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/pub/pari/unix/$(COMPONENT_ARCHIVE)

COMPONENT_LICENSE=     	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(TEST_64)

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# Configure complains when built outside of source tree
# The PARI script config/genfunclist uses find -type f and fails on symlinks
COMPONENT_PRE_CONFIGURE_ACTION= ($(CLONEY) $(SOURCE_DIR) $(@D))

# PARI/gp Configure is not autoconf 
CONFIGURE_SCRIPT= 	$(SOURCE_DIR)/Configure

# reset all options because Configure does not understand --sbindir= only --dir
CONFIGURE_OPTIONS=     --prefix=$(CONFIGURE_PREFIX)

# PARI/gp installs its 64bit library in /usr/lib
CONFIGURE_OPTIONS+=	--libdir=$(USRLIBDIR64)

# PARI/gp can be compiled with GMP but does not find gmp.h in /usr/include/gmp
# CONFIGURE_OPTIONS=	--with-gmp-include=/usr/include/gmp
# our choice is to use the native kernel i.e., compile without GMP 
CONFIGURE_OPTIONS+=	--without-gmp

CONFIGURE_OPTIONS+=	--with-readline

CONFIGURE_ENV+= 	CFLAGS="$(CFLAGS)"

# all does not work because documentation requires Tex typesetting
COMPONENT_BUILD_TARGETS = gp

COMPONENT_TEST_TARGETS = test-all

# Auto-generated dependencies
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
