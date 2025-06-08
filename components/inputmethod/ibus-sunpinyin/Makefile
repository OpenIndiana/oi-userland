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
# Copyright 2025 Jiwon Na
#

BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           ibus-sunpinyin
COMPONENT_VERSION=        3.0.0
COMPONENT_GIT_REV=	e4be7e64e4a168a684b26679b7e076118a2c97f7
COMPONENT_SUMMARY=        iBus Chinese IME - SunPinyin
COMPONENT_SRC=		sunpinyin-$(COMPONENT_GIT_REV)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=   sha256:3d36ed3203e88b5abd25145178c47609c68f5baf135caced72e072f55f88a96f
COMPONENT_ARCHIVE_URL=    https://codeload.github.com/sunpinyin/sunpinyin/tar.gz/$(COMPONENT_GIT_REV)
COMPONENT_FMRI=           system/input-method/ibus/sunpinyin
COMPONENT_CLASSIFICATION= System/Localizations
COMPONENT_LICENSE=        CDDLv1.0,LGPLv2.1
COMPONENT_LICENSE_FILE=   COPYING
COMPONENT_PROJECT_URL=    https://github.com/sunpinyin/sunpinyin/

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

SCONS = /usr/bin/scons

LIBDIR.32 =	/usr/lib
LIBDIR.64 =	/usr/lib/$(MACH64)

COMPONENT_BUILD_CMD = $(SCONS)
COMPONENT_BUILD_ARGS += --prefix=/usr
COMPONENT_BUILD_ARGS += --libexecdir=/usr/libexec

COMPONENT_INSTALL_CMD  = $(SCONS)
COMPONENT_INSTALL_ARGS += --prefix=/usr
COMPONENT_INSTALL_ARGS += --libexecdir=/usr/libexec
COMPONENT_INSTALL_ARGS += --install-sandbox=$(PROTO_DIR)

PATH= $(PATH.gnu)

COMPONENT_SUBDIR =		wrapper/ibus

# Manually added build dependencies
REQUIRED_PACKAGES += developer/build/scons
PYTHON_REQUIRED_PACKAGES += runtime/python

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/input-method/ibus
REQUIRED_PACKAGES += system/input-method/library/sunpinyin
REQUIRED_PACKAGES += system/library
