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
# Copyright 2016 Alexander Pyhalov
# Copyright 2018 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		glibmm
COMPONENT_VERSION=	2.58.0
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	glibmm - C++ Wrapper for the Glib2 Library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH= \
  sha256:d34189237b99e88228e6f557f7d6e62f767fe356f395a244f5ad0e486254b645
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/glibmm/2.58/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.gtkmm.org/
COMPONENT_FMRI=		library/c++/glibmm
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CXXFLAGS += -std=c++11

COMPONENT_PREP_ACTION = ( cd $(@D) && autoreconf -f -i)

PATH=$(PATH.gnu)

# for tests to pass
ENV=/usr/bin/env -i

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)

test: $(TEST_32_and_64)

# Build dependency
REQUIRED_PACKAGES += library/desktop/c++/mm-common

# Not found automatically
REQUIRED_PACKAGES += runtime/perl-522

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/sigcpp
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += system/library
