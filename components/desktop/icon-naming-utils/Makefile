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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
#

BUILD_BITS = NO_ARCH
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= icon-naming-utils
COMPONENT_VERSION= 0.8.90
COMPONENT_REVISION =	2
COMPONENT_SUMMARY= Icon naming utils
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:b1378679df4485b4459f609a3304238b3e92d91e43744c47b70abbe690d883d5
COMPONENT_ARCHIVE_URL= https://tango.freedesktop.org/releases/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL= https://tango.freedesktop.org/
COMPONENT_FMRI=	library/desktop/xdg/icon-naming-utils
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Theming
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET = $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH = $(PATH.gnu)

CONFIGURE_OPTIONS += --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))

# Build dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/xml-parser

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
