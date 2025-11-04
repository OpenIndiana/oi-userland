#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2018 Alexander Pyhalov
#

BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		cups-pdf
COMPONENT_VERSION=	3.0.2
COMPONENT_SUMMARY=	Virtual printer for CUPS to produce PDF files
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	https://www.cups-pdf.de/
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)_$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:56284001f40da9854e56215527e292de4811ce349e27d7a3e8add35c72da2f95
COMPONENT_ARCHIVE_URL=	https://www.cups-pdf.de/src/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		print/cups-pdf
COMPONENT_CLASSIFICATION=System/Printing
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cp $(COMPONENT_DIR)/files/Makefile $(COMPONENT_SRC) )

COMPONENT_BUILD_ENV += CC="$(CC)"
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += LDFLAGS="$(LDFLAGS)"

# Auto-generated dependencies
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += system/library
