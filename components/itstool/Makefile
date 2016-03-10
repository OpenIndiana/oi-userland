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
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		itstool
COMPONENT_VERSION=	2.0.2
COMPONENT_PROJECT_URL=	http://itstool.org
COMPONENT_SUMMARY=	ITS Tool allows you to translate your XML documents with PO files
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:bf909fb59b11a646681a8534d5700fec99be83bb2c57badf8c1844512227033a
COMPONENT_ARCHIVE_URL=	http://files.itstool.org/itstool/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		text/itstool
COMPONENT_CLASSIFICATION=	System/Text Tools
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING.GPL3

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

CONFIGURE_OPTIONS+=	--sysconfdir=/etc
CONFIGURE_ENV +=	PYTHON=$(PYTHON)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
