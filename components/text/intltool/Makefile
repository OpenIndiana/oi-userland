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
PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		intltool
COMPONENT_VERSION=	0.51.0
COMPONENT_FMRI=		text/intltool
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	Translation Tools for GNOME Internationalization
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:67c74d94196b153b774ab9f89b2fa6c6ba79352407037c8c14d5aeb334e959cd
COMPONENT_ARCHIVE_URL=\
  https://launchpad.net/intltool/trunk/$(COMPONENT_VERSION)/+download/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE= GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

COMPONENT_TEST_TRANSFORMS+= $(CONFIGURE_TEST_TRANSFORMS)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += developer/gnome/gettext
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
