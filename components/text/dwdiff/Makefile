#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2024 Matthew R. Trower
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         dwdiff
COMPONENT_VERSION=      2.1.4
COMPONENT_SUMMARY=      dwdiff - a diff program that operates at the word level
COMPONENT_PROJECT_URL=  https://os.ghalkes.nl/dwdiff.html
COMPONENT_FMRI=         text/dwdiff
COMPONENT_CLASSIFICATION=System/Text Tools
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_URL=  https://os.ghalkes.nl/dist/$(COMPONENT_ARCHIVE)
COMPONENT_SIG_URL=      $(COMPONENT_ARCHIVE_URL).sig
COMPONENT_ARCHIVE_HASH= \
	sha256:df16fec44dcb467d65a4246a43628f93741996c1773e930b90c6dde22dd58e0a
COMPONENT_LICENSE=      GPLv3
COMPONENT_LICENSE_FILE= COPYING


TEST_TARGET=$(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# Provide standards-conforming versions of install(8) and getpwuid_r(3C)
CONFIGURE_OPTIONS+=	INSTALL=/usr/ucb/install
CONFIGURE_OPTIONS+=	CFLAGS=-D_POSIX_PTHREAD_SEMANTICS

# Wants to be built in-tree, so copy source tree to build dir
COMPONENT_PRE_CONFIGURE_ACTION=	( $(CLONEY) $(SOURCE_DIR) $(@D) )

# Build dependencies
REQUIRED_PACKAGES+= 	text/gnu-gettext

# Auto-generated dependencies
REQUIRED_PACKAGES += $(ICU_LIBRARY_PKG)
REQUIRED_PACKAGES += system/library
