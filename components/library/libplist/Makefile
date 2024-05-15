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
# Copyright 2016 phorcys@126.com.  All rights reserved.
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= libplist
COMPONENT_VERSION= 2.6.0
COMPONENT_SUMMARY= A library to handle Apple Property List format in binary or XML
COMPONENT_PROJECT_URL = https://github.com/libimobiledevice/libplist
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:2c8aa303dac2d73fcf28ba90122e68480ca8cf7b00c5d44926ea4c1e8cf94368
COMPONENT_ARCHIVE_URL=	https://cgit.libimobiledevice.org/libplist.git/snapshot/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI= library/libplist
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE= GPLv2,LGPLv2.1

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# Without .tarball-version the build fails because of undefined PKG_VERSION.
COMPONENT_PREP_ACTION= ( cd  $(@D) && echo -n "$(COMPONENT_VERSION)" > .tarball-version  && NOCONFIGURE=true PATH="$(PATH.gnu)" sh autogen.sh )

# We use python vendor-packages instead of site-packages
COMPONENT_POST_INSTALL_ACTION += \
	cd $(PROTOUSRLIBDIR)/python$(PYTHON_VERSION) ; \
	$(RM) -r vendor-packages ; \
	$(MV) site-packages vendor-packages ;

CONFIGURE_ENV += PYTHON_SITE_PKG=/usr/lib/python$(PYTHON_VERSION)/vendor-packages

CONFIGURE_OPTIONS += --disable-static

# Manually added build dependencies
REQUIRED_PACKAGES += library/python/cython

# Auto-generated dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
