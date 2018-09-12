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
# Copyright 2016 Alexander Pyhalov
#

PREFERRED_BITS= 64 

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mate-system-monitor
COMPONENT_MJR_VERSION=	1.18
COMPONENT_MNR_VERSION=	3
COMPONENT_VERSION=	$(COMPONENT_MJR_VERSION).$(COMPONENT_MNR_VERSION)
COMPONENT_PROJECT_URL=	http://www.mate-desktop.org
COMPONENT_SUMMARY=	MATE system monitor
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:560292c6e44f9b69c825acf99c923436488b25b644b2cf1dfddd5135d34e1d3e
COMPONENT_ARCHIVE_URL=	http://pub.mate-desktop.org/releases/$(COMPONENT_MJR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	desktop/system-monitor/mate-system-monitor
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_LICENSE= GPLv3
COMPONENT_LICENSE_FILE= COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

LDFLAGS = -lnsl -lsocket

COMPONENT_PREP_ACTION=  cd $(@D)  && NOCONFIGURE=1 ./autogen.sh

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--libexecdir=$(CONFIGURE_LIBDIR.$(BITS))
CONFIGURE_OPTIONS+=	--disable-static

CONFIGURE_ENV+= PYTHON="$(PYTHON)"

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += image/library/librsvg
REQUIRED_PACKAGES += library/c++/glibmm
REQUIRED_PACKAGES += library/c++/sigcpp
REQUIRED_PACKAGES += library/desktop/c++/gtkmm3
REQUIRED_PACKAGES += library/desktop/cairo
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk3
REQUIRED_PACKAGES += library/desktop/libwnck3
REQUIRED_PACKAGES += library/desktop/pango
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libgtop
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += $(GXX_RUNTIME_PKG)
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
