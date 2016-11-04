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
# Copyright 2016 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		drm
COMPONENT_VERSION=	0.5.11
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	https://hg.java.net/hg/solaris-x11~x-s12-clone
COMPONENT_SUMMARY=	DRM Kernel Drivers
COMPONENT_SRC=		$(COMPONENT_NAME)
COMPONENT_ARCHIVE_HASH=	\
    sha256:3435a7a2ab1506629b2b9ee65232f66ea9b03d355006773b9abb65a316811a97
COMPONENT_FMRI=		driver/graphics/drm
COMPONENT_CLASSIFICATION=	Drivers/Display
COMPONENT_LICENSE=	MIT

include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin:/opt/onbld/bin/i386

LDFLAGS=-$(BITS)
LD_OPTIONS=

COMMON_ENV += CC="$(CC)"
COMMON_ENV += CFLAGS="$(CFLAGS)"
COMMON_ENV += LD="$(LD)"
COMMON_ENV += EXTRA_LDFLAGS="$(LDFLAGS)"
COMMON_ENV += MACH=$(MACH)
COMMON_ENV += MACH64=$(MACH64)

COMPONENT_BUILD_ENV += $(COMMON_ENV)

COMPONENT_BUILD_ARGS =
COMPONENT_BUILD_TARGETS = all

COMPONENT_INSTALL_ENV += $(COMMON_ENV)

# common targets
download::

clobber: clean

$(SOURCE_DIR)/.prep:
	$(TOUCH) $@

build: $(BUILD_64)

install: $(INSTALL_64)

clean::
	$(RM) $(SOURCE_DIR)/.prep


REQUIRED_PACKAGES += developer/build/onbld
REQUIRED_PACKAGES += system/header/header-agp
