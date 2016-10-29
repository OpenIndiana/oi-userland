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
#

include ../../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mate-icon-theme
COMPONENT_VERSION=	1.14.0
COMPONENT_PROJECT_URL=	http://www.mate-desktop.org
COMPONENT_SUMMARY=	Collection of icons for the MATE desktop
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:15bb2bed0046d7d4d8f770c04d00ffb55ffd72d601b05ac07f112265e9261eb5
COMPONENT_ARCHIVE_URL=	http://pub.mate-desktop.org/releases/1.14/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= GPLv2, LGPLv2, FDLv1.1
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license
COMPONENT_CLASSIFICATION = System/Libraries
COMPONENT_FMRI = desktop/mate/$(COMPONENT_NAME)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION= cd $(@D)  && NOCONFIGURE=1 ./autogen.sh

CONFIGURE_LOCALSTATEDIR =   $(VARDIR)/lib
CONFIGURE_LIBEXECDIR.32 =   $(USRLIBDIR)/mate
CONFIGURE_LIBEXECDIR.64 =   $(USRLIBDIR)/mate
### TODO: CONFIGURE_LIBEXECDIR.64 should be different? Original was:
###CONFIGURE_OPTIONS+=  --libexecdir=/usr/lib/mate

CONFIGURE_OPTIONS+= --disable-static
CONFIGURE_OPTIONS+= --disable-scrollkeeper

CONFIGURE_ENV+= PYTHON="$(PYTHON)"

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += library/desktop/xdg/icon-naming-utils
REQUIRED_PACKAGES += text/intltool
REQUIRED_PACKAGES += text/gnu-gettext
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += library/perl-5/xml-parser
