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
# Copyright 2016 Till Wegmueller
# Copyright 2016 Ken Mays
# Copyright 2018 Michal Nowak
#

PREFERRED_BITS=64

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mate-themes
COMPONENT_VERSION=	3.22.18
COMPONENT_PROJECT_URL=	http://www.mate-desktop.org
COMPONENT_SUMMARY=	MATE Themes
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:d5b15adfeee09cb1e2266db8b10b64814b7f380753ae5ebd09b7ea88115f6814
COMPONENT_ARCHIVE_URL=	http://pub.mate-desktop.org/releases/themes/3.22/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= GPLv2, LGPLv2, FDLv1.1
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license
COMPONENT_CLASSIFICATION = System/Libraries
COMPONENT_FMRI = desktop/mate/$(COMPONENT_NAME)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION=	cd $(@D)  && NOCONFIGURE=1 ./autogen.sh

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_OPTIONS+=     --libexecdir=/usr/lib/mate
CONFIGURE_OPTIONS+=	--localstatedir=/var/lib

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

# common targets
build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/desktop/xdg/icon-naming-utils
REQUIRED_PACKAGES += text/intltool
REQUIRED_PACKAGES += text/gnu-gettext
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += library/perl-5/xml-parser
