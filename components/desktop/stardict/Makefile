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
# Copyright (c) 2014 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		stardict
COMPONENT_MJR_VERSION=	3.0.7
COMPONENT_VERSION=	$(COMPONENT_MJR_VERSION).2
HUMAN_VERSION=		3.0.7-2
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	International dictionary software
COMPONENT_PROJECT_URL=	https://stardict-4.sourceforge.net/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_MJR_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(HUMAN_VERSION)-src.7z
COMPONENT_ARCHIVE_HASH=	sha256:d766f4efb1ae868855a47f39b2def66dd7a3232ca54c651c9cb3327b1bec50ea
COMPONENT_ARCHIVE_URL=	https://sourceforge.net/projects/stardict-4/files/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)/download
COMPONENT_FMRI=		system/desktop/stardict
COMPONENT_CLASSIFICATION=	Applications/Accessories
COMPONENT_LICENSE=	GPL-3.0-only
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATH= $(PATH.gnu)

COMPONENT_PREP_ACTION = ( cd $(@D) && PATH="$(PATH)" autoreconf -fiv )

CONFIGURE_OPTIONS += --enable-deprecations
CONFIGURE_OPTIONS += --disable-festival
CONFIGURE_OPTIONS += --disable-advertisement
CONFIGURE_OPTIONS += --disable-gucharmap
CONFIGURE_OPTIONS += --disable-gnome-support
CONFIGURE_OPTIONS += --disable-flite
CONFIGURE_OPTIONS += --disable-espeak-ng

CPPFLAGS += -I$(MYSQL_INCDIR)
LDFLAGS += -L$(MYSQL_LIBDIR) -R$(MYSQL_LIBDIR)
LDFLAGS += -lnsl -lsocket

CPPFLAGS += $(XPG6MODE)

# https://sourceforge.net/p/stardict-4/tickets/12/
CPPFLAGS += -fpermissive

CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

# Manually added build dependencies
REQUIRED_PACKAGES += $(MYSQL_LIBRARY_PKG)

# Auto-generated dependencies
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += library/c++/sigcpp
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/json-glib
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/desktop/xdg/libcanberra
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/speech/espeak
REQUIRED_PACKAGES += library/spell-checking/enchant
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
