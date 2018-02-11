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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME= fbreader
COMPONENT_VERSION= 0.12.10
COMPONENT_SUMMARY= Powerful e-book reader
COMPONENT_PROJECT_URL = http://www.fbreader.org/
COMPONENT_FMRI= desktop/fbreader
COMPONENT_CLASSIFICATION= Applications/Office
COMPONENT_SRC= $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-sources-$(COMPONENT_VERSION).tgz
COMPONENT_ARCHIVE_HASH= \
  sha256:328aec454db80e225aa0b5c31adef74bf62a14357482947e87e9731686b3c624
COMPONENT_ARCHIVE_URL= \
  http://www.fbreader.org/files/sources/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(GCC_ROOT)/bin:$(PATH.gnu)

COMPONENT_BUILD_ENV += TARGET_ARCH=desktop
COMPONENT_BUILD_ENV += UI_TYPE=gtk
COMPONENT_BUILD_ENV += TARGET_STATUS=release
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

build: $(BUILD_32)

install: $(INSTALL_32)

# Auto-generated dependencies
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/fribidi
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libunibreak
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
