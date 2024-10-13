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
# Copyright 2021 Jake Goerzen
#

USE_PARALLEL_BUILD= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		freeciv
COMPONENT_VERSION=	3.1.3
COMPONENT_SUMMARY=	Free and Open Source empire-building strategy game inspired by the history of human civilization.
COMPONENT_PROJECT_URL=	https://www.freeciv.org
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:741086fa94574374c7c27480f77ee68e5b538bfb2eff85004fa8c87b312c7f2f
COMPONENT_ARCHIVE_URL=  https://prdownloads.sourceforge.net/freeciv/$(COMPONENT_SRC).tar.xz?download
COMPONENT_FMRI=		games/freeciv
COMPONENT_CLASSIFICATION=	Applications/Games
COMPONENT_LICENSE=	GPLv2.0
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)
CONFIGURE_OPTIONS += --disable-sdl-mixer
CONFIGURE_OPTIONS += --disable-dependency-tracking
CONFIGURE_OPTIONS += --enable-ipv6=test

# Auto-generated dependencies
REQUIRED_PACKAGES += $(ICU_LIBRARY_PKG)
REQUIRED_PACKAGES += $(READLINE_PKG)
REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += compress/xz
REQUIRED_PACKAGES += compress/zstd
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += image/imagemagick
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += runtime/lua-54
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += web/curl
