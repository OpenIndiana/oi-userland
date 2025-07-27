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
# Copyright (c) 2022-2023 Niklas Poslovski
#

USE_PARALLEL_BUILD = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		MEGAsync
COMPONENT_VERSION=	4.9.5.0
COMPONENT_REVISION=	1
_REL=Linux
GIT_TAG=v$(COMPONENT_VERSION)_$(_REL)
COMPONENT_SUMMARY=	Easy automated syncing between your computers and your MEGA cloud drive
COMPONENT_SRC=		$(COMPONENT_NAME)-$(GIT_TAG)
COMPONENT_GIT_URL=		https://github.com/meganz
COMPONENT_PROJECT_URL=	$(COMPONENT_GIT_URL)/$(COMPONENT_NAME)
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)_$(_REL)
COMPONENT_SUBDIR=		src
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=  $(COMPONENT_PROJECT_URL)/archive/refs/tags/$(GIT_TAG).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:33e0d4e26492ef7ffd965a739f1d050b634aef69110d85af693f823e98718976
COMPONENT_FMRI=	network/megasync
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_LICENSE=	custom:MEGA LIMITED CODE REVIEW LICENCE
COMPONENT_LICENSE_FILE=	LICENCE.md

GIT_BRANCH_1=0f6531827ff7b15d1955f2e5843d44f90efd6f8d
COMPONENT_SRC_1=		sdk-$(GIT_BRANCH_1)
COMPONENT_ARCHIVE_1=      $(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_URL_1=  $(COMPONENT_GIT_URL)/sdk/archive/$(GIT_BRANCH_1).tar.gz
COMPONENT_ARCHIVE_HASH_1= sha256:21dd9e2f502f42566419bfc53a2b4214e3adaf052c771eb6d47d6401e2b37491

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/encumbered.mk
include $(WS_MAKE_RULES)/common.mk

PATH=$(QT5_BINDIR):$(GNUBIN):$(USRBINDIR$(BITS)):$(USRBINDIR):$(USRSBINDIR$(BITS)):$(USRSBINDIR):$(PERL5BINDIR)
COMPONENT_POST_UNPACK_ACTION_1= \
	$(MV) $(COMPONENT_SRC_1)/* $(SOURCE_DIR)/src/MEGASync/mega
CONFIGURE_OPTIONS += with_pcre=$(USRDIR)
CONFIGURE_OPTIONS += with_libmediainfo=$(USRDIR)
CONFIGURE_OPTIONS += with_freeimage=yes
CONFIGURE_OPTIONS += --disable-silent-rules
CONFIGURE_OPTIONS += --disable-curl-checks
CONFIGURE_OPTIONS += --disable-megaapi
CONFIGURE_OPTIONS += --disable-posix-threads
CONFIGURE_OPTIONS += --disable-examples
CONFIGURE_OPTIONS += --prefix="$(@D)/MEGAsync/src/MEGASync/mega/bindings/qt/3rdparty"
CONFIGURE_SCRIPT = configure
CLONEY_MODE = copy
COMPONENT_PRE_CONFIGURE_ACTION += \
	cd $(@D)$(COMPONENT_SUBDIR:%=/%) && $(ENV) PATH=$(PATH) ./autogen.sh ;
COMPONENT_PRE_BUILD_ACTION += \
	cd $(@D)$(COMPONENT_SUBDIR:%=/%) && $(ENV) PATH=$(PATH) $(QT5_BINDIR)/qmake "CONFIG += FULLREQUIREMENTS" "QMAKE_LFLAGS += -lelf -ljpegxr -lsocket -Wl,-z,ignore -Wl,-z,redlocsym -fPIC" "QMAKE_CC = $(CC)" "QMAKE_CXX = $(CXX)" MEGA.pro && $(ENV) $(QT5_BINDIR)/lrelease MEGASync/MEGASync.pro ;
COMPONENT_POST_BUILD_ACTION += \
	$(MV) $(BUILD_DIR)/amd64/LICENCE.md $(SOURCE_DIR)/LICENCE.md ;
COMPONENT_INSTALL_ARGS += INSTALL_ROOT=$(PROTO_DIR)
COMPONENT_POST_INSTALL_ACTION += \
	cd $(@D)$(COMPONENT_SUBDIR:%=/%) && $(MKDIR) $(PROTOUSRBINDIR) && $(INSTALL) -Dm 755 MEGASync/megasync $(PROTOUSRBINDIR) ;

$(BUILD_DIR)/%/.configured:	COMPONENT_SUBDIR = src/MEGASync/mega

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(ICU_LIBRARY_PKG)
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += developer/ffmpeg-7
REQUIRED_PACKAGES += developer/icu
REQUIRED_PACKAGES += library/cryptopp
REQUIRED_PACKAGES += library/ffmpeg-7
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
