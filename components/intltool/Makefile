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
# Copyright (c) 2014 Alexander Pyhalov. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		intltool
COMPONENT_VERSION=	0.50.2
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	Translation Tools for GNOME Internationalization
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:67f25c5c6fb71d095793a7f895b245e65e829e8bde68c6c8b4c912144ff34406
COMPONENT_ARCHIVE_URL=	https://launchpad.net/intltool/trunk/$(COMPONENT_VERSION)/+download/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += developer/gnome/gettext
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
