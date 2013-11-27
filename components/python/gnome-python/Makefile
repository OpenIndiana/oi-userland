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
# Copyright (c) 2013 Alexander Pyhalov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gnome-python
COMPONENT_VERSION=	2.28.1
COMPONENT_PROJECT_URL=	http://www.gnome.org
COMPONENT_SUMMARY=	Python bindings for various GNOME libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:759ce9344cbf89cf7f8449d945822a0c9f317a494f56787782a901e4119b96d8
COMPONENT_ARCHIVE_URL=	http://ftp.gnome.org/pub/GNOME/sources/$(COMPONENT_NAME)/2.28/$(COMPONENT_ARCHIVE)

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

gcc_OPT		= -O2

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_ENV+=		PYTHON=$(PYTHON)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

include $(WS_TOP)/make-rules/depend.mk
