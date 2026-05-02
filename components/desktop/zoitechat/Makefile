#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Marcel Telka <marcel@telka.sk>
# Copyright 2020 Michal Nowak
#

BUILD_STYLE= meson
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		zoitechat
COMPONENT_VERSION=	2.18.0
COMPONENT_SUMMARY=	ZoiteChat IRC client
COMPONENT_PROJECT_URL=	hhttps://zoitechat.org/ttps://hexchat.github.io/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).zip
COMPONENT_ARCHIVE_HASH= sha256:e186d2d591320ad0a7f7ffecc794d652ecf1aaf545cff899e5556bdb9b01fbd5
COMPONENT_ARCHIVE_URL=	https://github.com/ZoiteChat/zoitechat/archive/refs/tags/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		desktop/irc/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= Applications/Internet
COMPONENT_LICENSE= GPLv2
COMPONENT_LICENSE_FILE= COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

# zoitechat-zoitechat-2.18.0/src/common/zoitechat.c:685:17: error: implicit declaration of function 'kill' [-Wimplicit-function-declaration]
CFLAGS += -Wno-error=implicit-function-declaration
# zoitechat-zoitechat-2.18.0/src/common/outbound.c:1795:14: error: assignment to 'char *' from 'int' makes pointer from integer without a cast [-Wint-conversion]
CFLAGS += -Wno-error=int-conversion
# zoitechat-zoitechat-2.18.0/src/common/url.c:153:55: error: 'strcasecmp' undeclared (first use in this function); did you mean 'g_strcasecmp'?
CFLAGS += $(XPG7MODE)

CONFIGURE_OPTIONS += -Dwith-python=python-$(PYTHON_VERSION)
CONFIGURE_OPTIONS += -Dwith-lua=false
# plugins/perl/meson.build:48: WARNING: Project targets '>= 0.55.0' but uses feature introduced in '1.0.0': "in" string operator.
# plugins/perl/meson.build:95:2: ERROR: Problem encountered: found perl not suitable for plugin
CONFIGURE_OPTIONS += -Dwith-perl=false
CONFIGURE_ENV += AR="/usr/gnu/bin/ar"

# Auto-generated dependencies
REQUIRED_PACKAGES += $(OPENSSL_PKG)
REQUIRED_PACKAGES += desktop/library/libayatana-appindicator
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libarchive
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/libdbus-glib
