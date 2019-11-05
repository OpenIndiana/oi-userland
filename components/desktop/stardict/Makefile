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
COMPONENT_VERSION=	3.0.4
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.stardict.org/
COMPONENT_SUMMARY=	A powerful dictionary platform written in GTK+2
COMPONENT_FMRI=		system/desktop/stardict
COMPONENT_CLASSIFICATION=	Applications/Accessories
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:c38b9d953fe0b2380a8aed4c98cb121ad83aff91a32af3c665198d8268b1dce8
COMPONENT_ARCHIVE_URL=	ftp://tux.rainside.sk/gentoo/distfiles/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(MYSQL_BINDIR):$(PATH.gnu)

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
                                        autoreconf  -f -i )

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--enable-deprecations
CONFIGURE_OPTIONS+=	--disable-festival
CONFIGURE_OPTIONS+=	--disable-advertisement
CONFIGURE_OPTIONS+=	--disable-gucharmap
CONFIGURE_OPTIONS+=	--disable-gnome-support

CPPFLAGS += -I$(MYSQL_INCDIR)
LDFLAGS += -L$(MYSQL_LIBDIR) -R$(MYSQL_LIBDIR)

CXXFLAGS += -std=c++11

LDFLAGS += -lnsl -lsocket

CONFIGURE_ENV += CPPFLAGS=$(CPPFLAGS)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += developer/gnome/gnome-doc-utils
REQUIRED_PACKAGES += $(MYSQL_BASEPKG)/library

REQUIRED_PACKAGES += library/c++/sigcpp
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/speech/espeak
REQUIRED_PACKAGES += library/spell-checking/enchant
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
REQUIRED_PACKAGES += x11/library/libx11
