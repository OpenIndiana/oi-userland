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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright 2020, Michal Nowak
# Copyright 2021, Andreas Wacknitz
#

BUILD_BITS=		32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		bison
COMPONENT_MAJOR_VERSION=	3.8
COMPONENT_MAJOR_VERSION_=   $(subst .,,$(COMPONENT_MAJOR_VERSION))
COMPONENT_VERSION=	$(COMPONENT_MAJOR_VERSION).2
COMPONENT_REVISION=	3
COMPONENT_SUMMARY=	bison - A YACC Replacement
COMPONENT_DESCRIPTION=  A general-purpose parser generator that converts an annotated context-free grammar into an LALR(1) or GLR parser for that grammar
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/bison/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:9bba0214ccf7f1079c5d59210045227bcf619519840ebfa80cd3849cff5a5bf2
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/bison/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		developer/parser/bison-$(COMPONENT_MAJOR_VERSION_)
COMPONENT_CLASSIFICATION=	Development/Other Languages
COMPONENT_LICENSE=  GPLv2, FDLv1.2

include $(WS_MAKE_RULES)/common.mk

PKG_MACROS+= COMPONENT_MAJOR_VERSION=$(COMPONENT_MAJOR_VERSION)

# Tests need this
COMPONENT_PRE_CONFIGURE_ACTION = ( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_LIBDIR.32 =   $(GNULIB)/$(COMPONENT_NAME)-$(COMPONENT_MAJOR_VERSION)/
CONFIGURE_LIBDIR.64 =   $(GNULIB)/$(MACH64)/$(COMPONENT_NAME)-$(COMPONENT_MAJOR_VERSION)/

CONFIGURE_OPTIONS +=    --program-transform-name=s/$$/-$(COMPONENT_MAJOR_VERSION)/
CONFIGURE_OPTIONS +=    --datarootdir=$(CONFIGURE_PREFIX)/share/$(COMPONENT_NAME)-$(COMPONENT_MAJOR_VERSION)/
CONFIGURE_OPTIONS +=    --docdir=$(CONFIGURE_PREFIX)/share/doc/$(COMPONENT_NAME)-$(COMPONENT_MAJOR_VERSION)/
# We set the localedir here because this is the latest version and thus it will be used in the bison-runtime package.
# Info and locale files will be filtered out from the bison-$(COMPONENT_MAJOR_VERSION) manifests.
CONFIGURE_OPTIONS +=	--localedir=$(CONFIGURE_PREFIX)/share/locale/
# We set the infodir here because this is the latest version
CONFIGURE_OPTIONS +=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS +=	--disable-silent-rules
CONFIGURE_OPTIONS += 	--disable-dependency-tracking
CONFIGURE_OPTIONS +=	--disable-yacc

# the shared library we create needs to be built pic
COMPONENT_BUILD_ARGS += CC_PIC="$(CC_PIC)"

# this is cheesy but the tests don't seem to
# get compiled with the CFLAGS we built bison
# with, so they are 32-bit otherwise.
CONFIGURE_OPTIONS +=	WARN_CXXFLAGS_TEST="$(CFLAGS)"

CONFIGURE_ENV += 	M4="/usr/bin/gm4"
CONFIGURE_ENV +=	RANLIB="/usr/bin/ranlib"

# Strip compilation lines from test output
# and strange backslash lines. and random output,
# including rm complaints over nfs
COMPONENT_TEST_TRANSFORMS += \
	$(CONFIGURE_TEST_TRANSFORMS) \
	' -e "/^\#/p" ' \
	' -e "/^[\s]*[0-9][0-9]*:/p" ' \
	' -e "/tests were/p" ' 

$(INSTALL_32):	$(INSTALL_64)

GENERATE_EXTRA_CMD += | \
	$(GSED) -e 's/bison-$(shell echo $(COMPONENT_MAJOR_VERSION) | $(GSED) -e 's/\./\\./g')/bison-$$(COMPONENT_MAJOR_VERSION)/'

# Two test suite cases utilitize Doxygen
TEST_REQUIRED_PACKAGES += developer/documentation-tool/doxygen

# Auto-generated dependencies
REQUIRED_PACKAGES += developer/macro/gnu-m4
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += text/gnu-gettext
