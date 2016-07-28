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
# Copyright 2015 Alexander Pyhalov
# Copyright 2016 Till Wegmueller
# Copyright 2016 Ken Mays
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mate-desktop
COMPONENT_VERSION=	1.14.1
COMPONENT_REVISION=	2
COMPONENT_PROJECT_URL=	http://www.mate-desktop.org
COMPONENT_SUMMARY=	Additional UI API for MATE Desktop
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:97b5067c3b9a0b96494cf189dc94e64ac852cd21cddc27961e7b744f550d5786
COMPONENT_ARCHIVE_URL=	http://pub.mate-desktop.org/releases/1.14/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= GPLv2, LGPLv2, FDLv1.1
COMPONENT_LICENSE_FILE= mate-desktop.license
COMPONENT_CLASSIFICATION = System/Libraries
COMPONENT_FMRI = library/desktop/mate/$(COMPONENT_NAME)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION = cd $(@D)  && NOCONFIGURE=1 ./autogen.sh


CONFIGURE_OPTIONS+= --sysconfdir=/etc
CONFIGURE_OPTIONS+= --libexecdir=/usr/lib/mate
CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --disable-scrollkeeper
CONFIGURE_OPTIONS+= --localstatedir=/var/lib

CONFIGURE_ENV+= PYTHON="$(PYTHON)"

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/desktop/mate/mate-common
REQIURED_PACKAGES += gnome/config/dconf
REQIURED_PACKAGES += x11/library/libpthread-stubs
REQIURED_PACKAGES += library/desktop/atk
REQIURED_PACKAGES += library/desktop/cairo
REQIURED_PACKAGES += library/desktop/gdk-pixbuf
REQIURED_PACKAGES += library/desktop/gtk2
REQIURED_PACKAGES += library/desktop/pango
REQIURED_PACKAGES += library/desktop/startup-notification
REQIURED_PACKAGES += library/glib2
REQIURED_PACKAGES += system/library/math
REQIURED_PACKAGES += x11/library/libx11
REQIURED_PACKAGES += x11/library/libxrandr
