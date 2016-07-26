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
# Copyright (c) 2016 Sergey Avseyev
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		redshift
COMPONENT_VERSION=	1.11
COMPONENT_PROJECT_URL=	http://jonls.dk/redshift/
COMPONENT_SUMMARY=	Redshift adjusts the color temperature of your screen according to your surroundings
COMPONENT_FMRI=         x11/redshift
COMPONENT_CLASSIFICATION=       System/X11
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
    sha256:10e350f93951c0521dd6f103d67a485972c307214f036e009acea2978fe4f359
COMPONENT_ARCHIVE_URL=	https://github.com/jonls/redshift/releases/download/v$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPL-3
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PYTHON_VERSION	= 3.4

CONFIGURE_ENV	+= XGETTEXT=/usr/gnu/bin/xgettext
CONFIGURE_ENV	+= MSGFMT=/usr/gnu/bin/msgfmt
CONFIGURE_ENV	+= PYTHON=$(PYTHON)

CONFIGURE_OPTIONS	+= am_cv_python_pythondir="$(PYTHON_VENDOR_PACKAGES)"
CONFIGURE_OPTIONS	+= --enable-gui

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk
