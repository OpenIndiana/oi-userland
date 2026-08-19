
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
# Copyright 2024 Andreas Wacknitz
#

BUILD_STYLE= cmake
USE_PARALLEL_BUILD= yes
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           wxmaxima
COMPONENT_VERSION=        26.8.0
HUMAN_VERSION=            26.08.0
COMPONENT_SUMMARY=        wxMaxima is a document based interface for the computer algebra system Maxima
COMPONENT_PROJECT_URL=    https://github.com/wxMaxima-developers/wxmaxima
COMPONENT_SRC=            $(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=    https://github.com/wxMaxima-developers/wxmaxima/archive/refs/tags/Version-$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=   sha256:7524487ddf858eaba8d9e4d0fc2062bdb1d177b21183e5adfa78fc27929e57ce
COMPONENT_FMRI=           application/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Applications/Office
COMPONENT_LICENSE=        GPLv2
COMPONENT_LICENSE_FILE=   COPYING

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_POST_UNPACK_ACTION= ( $(MV) $(COMPONENT_NAME)-Version-$(HUMAN_VERSION) $(COMPONENT_SRC) );

CFLAGS += $(XPG8MODE)

LDFLAGS += -lsocket -lnsl

CMAKE_OPTIONS += -DCMAKE_BUILD_TYPE=Release

# Testing needs an X server
# With a xvfb the tests are stuck at #6, with a real X server we get many segfaults
#TEST_REQUIRED_PACKAGES += x11/server/xvfb
#COMPONENT_PRE_TEST_ACTION += /usr/bin/Xvfb :1 >/dev/null 2>&1 &
#COMPONENT_TEST_ENV += DISPLAY=:1
#COMPONENT_POST_TEST_ACTION += /usr/bin/pkill -x Xvfb ;

# Manually added build dependencies
REQUIRED_PACKAGES += utility/bash-completion
TEST_REQUIRED_PACKAGES += library/math/maxima

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/fribidi
REQUIRED_PACKAGES += library/graphics/wxwidgets-3
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
