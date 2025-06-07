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

COMPONENT_NAME=           sunpinyin
COMPONENT_VERSION=        3.0.0
COMPONENT_GIT_REV=	e4be7e64e4a168a684b26679b7e076118a2c97f7
COMPONENT_SUMMARY=        sunpinyin - A statistical language model based Chinese input method
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_GIT_REV)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=   sha256:3d36ed3203e88b5abd25145178c47609c68f5baf135caced72e072f55f88a96f
COMPONENT_ARCHIVE_URL=    https://codeload.github.com/sunpinyin/$(COMPONENT_NAME)/tar.gz/$(COMPONENT_GIT_REV)
COMPONENT_FMRI=           system/input-method/library/sunpinyin
COMPONENT_CLASSIFICATION= System/Localizations
COMPONENT_LICENSE=        CDDLv1.0,LGPLv2.1
COMPONENT_LICENSE_FILE=   COPYING
COMPONENT_PROJECT_URL=    https://github.com/sunpinyin/sunpinyin/

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

SCONS = /usr/bin/scons

LIBDIR.32 =	/usr/lib
LIBDIR.64 =	/usr/lib/$(MACH64)

CXXFLAGS += -fpermissive
COMPONENT_BUILD_CMD = $(SCONS)
COMPONENT_BUILD_ARGS += --prefix=/usr
COMPONENT_BUILD_ARGS += --libdir=$(LIBDIR.$(BITS))

COMPONENT_INSTALL_CMD  = $(SCONS)
COMPONENT_INSTALL_ARGS += --prefix=/usr
COMPONENT_INSTALL_ARGS += --libdir=$(LIBDIR.$(BITS))
COMPONENT_INSTALL_ARGS += --install-sandbox=$(PROTO_DIR)

PATH= $(PATH.gnu)

COMPONENT_POST_BUILD_ACTION += (cd $(@D)/src && ./sunpinyin-dictgen )
COMPONENT_POST_INSTALL_ACTION = \
	( $(MKDIR) $(PROTO_DIR)/usr/share/sunpinyin;\
	 cd $(@D)/src ; $(CP) lm_sc.t3g pydict_sc.bin $(PROTO_DIR)/usr/share/sunpinyin\
	) ;

# Manually added build dependencies
PYTHON_REQUIRED_PACKAGES += runtime/python
REQUIRED_PACKAGES += developer/build/scons
# Needed for sunpinyin-dictgen
REQUIRED_PACKAGES += system/library/iconv/unicode

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
