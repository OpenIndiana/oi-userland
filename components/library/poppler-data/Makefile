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
# Copyright 2014, Andrzej Szeszo
#

BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		poppler-data
COMPONENT_VERSION=	0.4.12
COMPONENT_SUMMARY=	Poppler is a PDF rendering library based on the xpdf-3.0 code base (encoding data)
COMPONENT_PROJECT_URL=	https://poppler.freedesktop.org
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:c835b640a40ce357e1b83666aabd95edffa24ddddd49b8daff63adb851cdab74
COMPONENT_FMRI=		library/libpoppler-data
COMPONENT_CLASSIFICATION=	Desktop (GNOME)/Libraries
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_INSTALL_ARGS += datadir=$(USRSHAREDIR)

# Auto-generated dependencies
