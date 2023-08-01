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
# Copyright 2015 Alexander Pyhalov
# Copyright 2022 Niklas Poslovski
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         soundtouch
COMPONENT_VERSION=      2.3.1
COMPONENT_REVISION=     2
COMPONENT_SUMMARY=      Audio Processing Library
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:6900996607258496ce126924a19fe9d598af9d892cf3f33d1e4daaa9b42ae0b1
COMPONENT_ARCHIVE_URL=  \
	https://www.surina.net/soundtouch/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=  https://www.surina.net/soundtouch
COMPONENT_LICENSE=      LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING.TXT
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_FMRI=         library/audio/soundtouch

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
					$(CONFIG_SHELL) bootstrap )

CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --disable-x86-optimizations

CONFIGURE_ENV += AM_CXXFLAGS="$(CXXFLAGS)"

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
