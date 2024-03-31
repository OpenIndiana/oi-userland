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
COMPONENT_VERSION=      2.3.3
COMPONENT_SUMMARY=      Audio Processing Library
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=  https://www.surina.net/soundtouch
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:43b23dfac2f64a3aff55d64be096ffc7b73842c3f5665caff44975633a975a99
COMPONENT_FMRI=         library/audio/soundtouch
COMPONENT_CLASSIFICATION=System/Multimedia Libraries
COMPONENT_LICENSE=      LGPLv2.1
COMPONENT_LICENSE_FILE= COPYING.TXT

include $(WS_MAKE_RULES)/common.mk

# Rename unpacked source folder
COMPONENT_POST_UNPACK_ACTION= ( $(MV) $(COMPONENT_NAME) $(COMPONENT_SRC) )

COMPONENT_PREP_ACTION = ( cd $(@D) && \
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
