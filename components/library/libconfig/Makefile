#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 John Smith. All rights reserved.
#

BUILD_BITS= 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libconfig
COMPONENT_VERSION=	1.7.3
COMPONENT_REVISION= 1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://hyperrealm.github.io/libconfig
COMPONENT_ARCHIVE=	v$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:68757e37c567fd026330c8a8449aa5f9cac08a642f213f2687186b903bd7e94e
COMPONENT_ARCHIVE_URL=	https://github.com/hyperrealm/libconfig/archive/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		library/libconfig
COMPONENT_SUMMARY=	C/C++ library for processing configuration files
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	LGPLv2.1

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cd $(@D)  && \
				rm -f lib/scanner.{c,h} &&\
				autoreconf -f -i)

# Missing files in build dir for configure without this.
COMPONENT_PRE_CONFIGURE_ACTION = ( $(CLONEY) $(SOURCE_DIR) $(@D) )

COMPONENT_TEST_ENV += libtool_execute_magic=
COMPONENT_TEST_ENV += LD_LIBRARY_PATH=$(LD_LIBRARY_PATH)

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS += \
	'-e "s/[0-9]* Segmentation Fault/Segmentation Fault/" ' \
	'-e "/^make/d" ' \
	'-e "/\/usr\/gnu\/bin\/make/d" '

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
