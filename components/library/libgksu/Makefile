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
# Copyright (c) 2020 Marco van Wieringen
#

BUILD_BITS= 32

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libgksu
COMPONENT_VERSION=	2.0.12
COMPONENT_REVISION=	5
COMPONENT_FMRI=		library/desktop/libgksu
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_PROJECT_URL=	http://www.nongnu.org/gksu/
COMPONENT_SUMMARY=	Simple API for embedded_su, pfexec and sudo (optional)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:22f9cfc3627dcb6774b9aff66c6ea6554f3b34b82bbfa2467b821e67874c3faf
COMPONENT_ARCHIVE_URL=	http://people.debian.org/~kov/gksu/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	LGPLv2

TEST_TARGET= $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
					$(TOUCH) NEWS  README&&\
					libtoolize --copy --force &&\
					aclocal &&\
					automake -a -c -f && \
                                        autoconf &&\
					intltoolize --force  --copy )

CONFIGURE_OPTIONS+=	--disable-static
CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=	--libexecdir=/usr/lib
CONFIGURE_OPTIONS+=	--disable-scrollkeeper

# Build dependencies
REQUIRED_PACKAGES += developer/documentation-tool/gtk-doc

# Auto-generated dependencies
REQUIRED_PACKAGES += gnome/config/gconf
REQUIRED_PACKAGES += library/desktop/atk
REQUIRED_PACKAGES += library/desktop/gdk-pixbuf
REQUIRED_PACKAGES += library/desktop/gtk2
REQUIRED_PACKAGES += library/desktop/startup-notification
REQUIRED_PACKAGES += library/glib2
REQUIRED_PACKAGES += library/libgtop
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += x11/library/libx11
