# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2022, Andreas Wacknitz. All rights reserved.
#

BUILD_BITS= 64
BUILD_STYLE ?= configure

COMPONENT_VERSION=  $(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_PROJECT_URL=  https://www.mate-desktop.org
COMPONENT_ARCHIVE_URL=  https://pub.mate-desktop.org/releases/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.xz
COMPONENT_LICENSE=	GPLv2, LGPLv2, FDLv1.1

TEST_TARGET=        $(NO_TESTS)

PATH=$(PATH.gnu)

ifeq   ($(strip $(BUILD_STYLE)),configure)
COMPONENT_PREP_ACTION= cd $(@D)  && NOCONFIGURE=1 ./autogen.sh
endif

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --libexecdir=$(CONFIGURE_LIBDIR.$(BITS))/mate
ifeq   ($(strip $(BUILD_STYLE)),configure)
CONFIGURE_OPTIONS+= --disable-static
endif
CONFIGURE_OPTIONS+= --localstatedir=/var/lib

CONFIGURE_ENV+= PYTHON="$(PYTHON)"

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

#
# Set defaults for Mate libraries
#
ifeq ($(strip $(MATE_CATEGORY)),LIB)
COMPONENT_CLASSIFICATION ?=	System/Libraries
COMPONENT_FMRI ?=     		library/desktop/mate/$(COMPONENT_NAME)
endif

#
# Set defaults for Mate applications
#
ifeq ($(strip $(MATE_CATEGORY)),APP)
# APPs don't have a common COMPONENT_CLASSIFICATION and thus need to define it separately.
COMPONENT_FMRI ?=     desktop/mate/$(COMPONENT_NAME)
endif

# Default build dependencies
ifeq   ($(strip $(BUILD_STYLE)),configure)
USERLAND_REQUIRED_PACKAGES += developer/build/autoconf
endif
USERLAND_REQUIRED_PACKAGES += developer/build/pkg-config
USERLAND_REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
USERLAND_REQUIRED_PACKAGES += library/desktop/mate/mate-common
