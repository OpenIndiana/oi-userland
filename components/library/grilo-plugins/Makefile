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
# Copyright 2019 Tim Mooney.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		grilo-plugins
COMPONENT_VERSION=	0.3.4
COMPONENT_FMRI=		library/desktop/grilo/plugins
COMPONENT_SUMMARY=	plugins for use with the grilo media discovery framework
COMPONENT_CLASSIFICATION= System/Multimedia Libraries
COMPONENT_PROJECT_URL=	https://wiki.gnome.org/Projects/Grilo
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
  sha256:990282a518968c52f6a67b96c6b708e236a59da1c7c920ed45e6316ab49ddeb5
COMPONENT_ARCHIVE_URL= \
  http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/0.3/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	LGPL 2.1
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION += ( $(CLONEY) $(SOURCE_DIR) $(@D) )

PATH=$(PATH.gnu)

CONFIGURE_SCRIPT=	$(@D)/configure

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--disable-static

# Tell g-ir-scanner about compiler
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += CC="$(CC)"

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Build dependencies
REQUIRED_PACKAGES += text/itstool

# Auto-generated dependencies
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += library/desktop/grilo
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/desktop/libgdata
REQUIRED_PACKAGES += library/desktop/search/tracker
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/gmime
REQUIRED_PACKAGES += library/gom
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += library/libmediaart
REQUIRED_PACKAGES += library/liboauth
REQUIRED_PACKAGES += library/libsoup
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/media-player/totem-pl-parser
REQUIRED_PACKAGES += runtime/lua-53
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/network/avahi
