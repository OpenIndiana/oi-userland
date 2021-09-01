# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright (c) 2021, Andreas Wacknitz. All rights reserved.
#

COMPONENT_VERSION=  $(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_PROJECT_URL=  https://www.mate-desktop.org
COMPONENT_ARCHIVE_URL=  https://pub.mate-desktop.org/releases/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_SRC=      $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=  $(COMPONENT_SRC).tar.xz
COMPONENT_LICENSE=	GPLv2, LGPLv2, FDLv1.1

TEST_TARGET=        $(NO_TESTS)

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION= cd $(@D)  && NOCONFIGURE=1 ./autogen.sh

CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --libexecdir=/usr/lib/mate
CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --localstatedir=/var/lib

CONFIGURE_ENV+= PYTHON="$(PYTHON)"

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

#
# Set defaults for Mate libraries
#
ifeq ($(strip $(MATE_CATEGORY)),LIB)
BUILD_BITS = 32_and_64
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_FMRI=     		library/desktop/mate/$(COMPONENT_NAME)
endif


#
# Set defaults for Mate applications
#
ifeq ($(strip $(MATE_CATEGORY)),APP)
BUILD_BITS = 64
PREFERRED_BITS=	64
COMPONENT_FMRI=     desktop/mate/$(COMPONENT_NAME)
endif

# Default build dependencies
REQUIRED_PACKAGES += developer/build/autoconf
REQUIRED_PACKAGES += developer/build/pkg-config
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc
REQUIRED_PACKAGES += library/desktop/mate/mate-common
