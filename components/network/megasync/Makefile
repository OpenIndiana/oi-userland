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
COMPONENT_VERSION=	4.6.3
COMPONENT_REVISION= 1
_REL=Linux
COMPONENT_PREP_GIT=yes
GIT_TAG=v$(COMPONENT_VERSION).0_$(_REL)
COMPONENT_SUMMARY=	Easy automated syncing between your computers and your MEGA cloud drive
COMPONENT_SRC=		$(COMPONENT_NAME)-$(GIT_TAG)
COMPONENT_PROJECT_URL=	https://github.com/meganz/MEGAsync
GIT_REPO=https://github.com/meganz/MEGAsync.git
GIT_COMMIT_ID=tags/$(GIT_TAG)
SDK_COMMIT_ID=995b5c9b599ae2e0b72ef0029775bd6c9a3c4326
SDK_REPO=https://github.com/meganz/sdk.git
COMPONENT_ARCHIVE_SRC=git
COMPONENT_FMRI=	network/megasync
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_LICENSE=	custom:MEGA LIMITED CODE REVIEW LICENCE
COMPONENT_LICENSE_FILE=	LICENCE.md

include $(WS_MAKE_RULES)/common.mk
QT5_ROOT=/usr/lib/qt/5.15
PATH=$(QT5_ROOT)/bin/amd64:$(GNUBIN):$(USRBINDIR$(BITS)):$(USRBINDIR):$(USRSBINDIR$(BITS)):$(USRSBINDIR):$(PERL5BINDIR)
COMPONENT_POST_UNPACK_ACTION= \
	git clone $(SDK_REPO) $(SOURCE_DIR)/src/MEGASync/mega; \
	cd $(SOURCE_DIR)/src/MEGASync/mega && git checkout $(SDK_COMMIT_ID)
CONFIGURE_OPTIONS += with_pcre=/usr
CONFIGURE_SCRIPT = configure
COMPONENT_PRE_CONFIGURE_ACTION= \
	(mv $(SOURCE_DIR)/* $(@D)); \
	cd $(@D)/src/MEGASync/mega && ./autogen.sh
COMPONENT_PRE_BUILD_ACTION= \
	cd $(@D)/src && qmake "CONFIG += FULLREQUIREMENTS" "QMAKE_LFLAGS += -Wl,-z,nodefs -Wl,-z,ignore -Wl,-z,redlocsym -fPIC" "QMAKE_CC = $(CC)" "QMAKE_CXX = $(CXX)" MEGA.pro && lrelease MEGASync/MEGASync.pro
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
REQUIRED_PACKAGES += web/curl
REQUIRED_PACKAGES += x11/library/libxcb
