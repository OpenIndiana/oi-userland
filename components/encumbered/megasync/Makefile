#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#

#
# Copyright (c) 2022, Daniel Chan
#

BUILD_BITS=			64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		MEGAsync
COMPONENT_VERSION=	4.6.6
COMPONENT_REVISION= 2
_REL=Linux
GIT_TAG=v$(COMPONENT_VERSION).0_$(_REL)
COMPONENT_SUMMARY=	Easy automated syncing between your computers and your MEGA cloud drive
COMPONENT_SRC=		$(COMPONENT_NAME)-$(GIT_TAG)
COMPONENT_GIT_URL=		https://github.com/meganz
COMPONENT_PROJECT_URL=	$(COMPONENT_GIT_URL)/$(COMPONENT_NAME)
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION).0_$(_REL)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/archive/refs/tags/$(GIT_TAG).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:dc40151095031533250253b0fe6a7439c845d3881e19d194b2090870236948ed
COMPONENT_FMRI=	network/megasync
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_LICENSE=	custom:MEGA LIMITED CODE REVIEW LICENCE
COMPONENT_LICENSE_FILE=	LICENCE.md

GIT_BRANCH_1=4b40fcbf58cd7b0ccb4a9604f08693fc5ed62bf2
COMPONENT_SRC_1=		sdk-$(GIT_BRANCH_1)
COMPONENT_ARCHIVE_1=      $(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_URL_1=  $(COMPONENT_GIT_URL)/sdk/archive/$(GIT_BRANCH_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= sha256:850973860197be5328324970572844fbd833439e65f14e23b78fd15a1c8a6fad

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

PATH=$(QT5_BINDIR):$(GNUBIN):$(USRBINDIR$(BITS)):$(USRBINDIR):$(USRSBINDIR$(BITS)):$(USRSBINDIR):$(PERL5BINDIR)
COMPONENT_POST_UNPACK_ACTION_1= \
	mv $(COMPONENT_SRC_1)/* $(SOURCE_DIR)/src/MEGASync/mega
CONFIGURE_OPTIONS += with_pcre=/usr
CONFIGURE_OPTIONS += with_libmediainfo=/usr
CONFIGURE_OPTIONS += with_freeimage=yes
CONFIGURE_OPTIONS += --disable-silent-rules
CONFIGURE_OPTIONS += --disable-curl-checks
CONFIGURE_OPTIONS += --disable-megaapi
CONFIGURE_OPTIONS += --disable-posix-threads
CONFIGURE_OPTIONS += --disable-examples
CONFIGURE_OPTIONS += --prefix="$(@D)/MEGAsync/src/MEGASync/mega/bindings/qt/3rdparty"
CONFIGURE_SCRIPT = configure
COMPONENT_PRE_CONFIGURE_ACTION= \
	(mv $(SOURCE_DIR)/* $(@D)); \
	cd $(@D)/src/MEGASync/mega && ./autogen.sh
COMPONENT_PRE_BUILD_ACTION= \
	cd $(@D)/src && qmake "CONFIG += FULLREQUIREMENTS" "QMAKE_LFLAGS += -lelf -ljpegxr -lsocket -Wl,-z,ignore -Wl,-z,redlocsym -fPIC" "QMAKE_CC = $(CC)" "QMAKE_CXX = $(CXX)" MEGA.pro && lrelease MEGASync/MEGASync.pro
COMPONENT_POST_BUILD_ACTION= \
	mv $(BUILD_DIR)/amd64/LICENCE.md $(SOURCE_DIR)/LICENCE.md
COMPONENT_INSTALL_ARGS += INSTALL_ROOT=$(PROTO_DIR)
COMPONENT_POST_INSTALL_ACTION = \
	cd $(@D)/src/ && mkdir -p $(PROTO_DIR)/usr/bin/ && ginstall -Dm 755 MEGASync/megasync $(PROTO_DIR)/usr/bin/

$(BUILD_DIR)/%/.configured:	$(SOURCE_DIR)/.prep
	($(RM) -rf $(@D) ; $(MKDIR) $(@D))
	$(COMPONENT_PRE_CONFIGURE_ACTION)
	(cd $(@D) ; cd $(@D)/src/MEGASync/mega && $(ENV) $(CONFIGURE_ENV) $(CONFIG_SHELL) \
		$(CONFIGURE_SCRIPT) $(CONFIGURE_OPTIONS))
	$(COMPONENT_POST_CONFIGURE_ACTION)
	$(TOUCH) $@

$(BUILD_DIR)/%/.built:	$(BUILD_DIR)/%/.configured
	$(COMPONENT_PRE_BUILD_ACTION)
	(cd $(@D) ; cd $(@D)/src && $(ENV) $(COMPONENT_BUILD_ENV) \
		$(GMAKE) $(COMPONENT_BUILD_GMAKE_ARGS) $(COMPONENT_BUILD_ARGS) \
		$(COMPONENT_BUILD_TARGETS))
	$(COMPONENT_POST_BUILD_ACTION)
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
	-$(PARFAIT) build
endif
	$(TOUCH) $@

$(BUILD_DIR)/%/.installed:	$(BUILD_DIR)/%/.built
	$(COMPONENT_PRE_INSTALL_ACTION)
	(cd $(@D) ; cd $(@D)/src && $(ENV) $(COMPONENT_INSTALL_ENV) $(GMAKE) \
			$(COMPONENT_INSTALL_ARGS) $(COMPONENT_INSTALL_TARGETS))
	$(COMPONENT_POST_INSTALL_ACTION)
	$(TOUCH) $@

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += image/library/libraw
REQUIRED_PACKAGES += library/cryptopp
REQUIRED_PACKAGES += library/libcares
REQUIRED_PACKAGES += library/libfreeimage
REQUIRED_PACKAGES += library/libmediainfo
REQUIRED_PACKAGES += library/libuv
REQUIRED_PACKAGES += library/libzen
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += library/security/libsodium
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += video/ffmpeg
REQUIRED_PACKAGES += web/curl
REQUIRED_PACKAGES += x11/library/libxcb
