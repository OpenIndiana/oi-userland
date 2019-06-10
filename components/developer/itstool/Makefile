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
# Copyright 2019, Tim Mooney. All rights reserved
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		itstool
COMPONENT_VERSION=	2.0.6
COMPONENT_SUMMARY=	W3C International Tag Set (ITS) translation tool
COMPONENT_FMRI=		developer/build/itstool
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
	sha256:6233cc22726a9a5a83664bf67d1af79549a298c23185d926c3677afa917b92a9
COMPONENT_ARCHIVE_URL=	http://files.itstool.org/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://itstool.org
COMPONENT_CLASSIFICATION=Development/GNOME and GTK+
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	GPLv3

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_ENV		+=	PYTHON="$(PYTHON)"

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/python/libxml2-27
REQUIRED_PACKAGES += runtime/python-27
