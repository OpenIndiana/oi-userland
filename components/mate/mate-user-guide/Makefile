#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2015 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mate-user-guide
COMPONENT_VERSION=	1.12.0
COMPONENT_PROJECT_URL=	http://mate-desktop.org
COMPONENT_SUMMARY=	MATE documentation
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:ffefae8d87e1d58aa4526071c80051da3c31cf85c2a9359dedf425064205166c
COMPONENT_ARCHIVE_URL=	https://github.com/mate-desktop/mate-user-guide/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE= FDLv1.1
COMPONENT_LICENSE_FILE= COPYING
COMPONENT_CLASSIFICATION = Desktop (GNOME)/Documentation
COMPONENT_FMRI = mate/mate-user-guide


include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
					$(ENV) NOCONFIGURE=1 mate-autogen )

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))
CONFIGURE_SCRIPT = $(@D)/configure


CONFIGURE_OPTIONS+=	--sysconfdir=/etc

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
