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
# Copyright 2019 Michal Nowak
# Copyright 2022 Daniel Chan
#

BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		fbreader
COMPONENT_VERSION=	0.99.4
COMPONENT_REVISION=	7
COMPONENT_SUMMARY=	Powerful e-book reader
COMPONENT_PROJECT_URL=	https://www.fbreader.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-sources-$(COMPONENT_VERSION).tgz
COMPONENT_ARCHIVE_HASH= sha256:3d7c31d5ea314589d2a963290ad16f4d3d631a41e802b8b39f8be0c9f71eb8e9
COMPONENT_ARCHIVE_URL= $(COMPONENT_PROJECT_URL)/files/desktop/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	desktop/fbreader
COMPONENT_CLASSIFICATION=	Applications/Office
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu):$(QT5_BINDIR)

ENV += TARGET_ARCH=desktop
ENV += UI_TYPE=qt4
ENV += TARGET_STATUS=release
ENV += CFLAGS="$(CFLAGS)"
ENV += LDFLAGS="$(LDFLAGS)"
ENV += PKG_CONFIG_PATH="$(PKG_CONFIG_PATH):$(QT5_PKG_CONFIG_PATH)"
ENV += QT_NO_OPENSSL=1
ENV += ZLSHARED=no

COMPONENT_POST_INSTALL_ACTION = \
	/usr/bin/elfedit -e 'dyn:value -s RUNPATH "$(GCC_LIBDIR):$(QT5_LIBDIR)"' $(PROTO_DIR)/usr/bin/FBReader; \
	/usr/bin/elfedit -e 'dyn:value -s RPATH   "$(GCC_LIBDIR):$(QT5_LIBDIR)"' $(PROTO_DIR)/usr/bin/FBReader;

REQUIRED_PACKAGES += web/curl

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/fribidi
REQUIRED_PACKAGES += library/libunibreak
REQUIRED_PACKAGES += library/qt5
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
