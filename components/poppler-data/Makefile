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

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		poppler-data
COMPONENT_VERSION=	0.4.6
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:f306901dfa5bda90cd6663d4eedb1c773c3c709de78018c79f1282b2c8f90afa
COMPONENT_ARCHIVE_URL= \
     http://poppler.freedesktop.org/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://poppler.freedesktop.org/
COMPONENT_AUTOGEN_MANIFEST=	yes
COMPONENT_FMRI=		library/libpoppler-data
COMPONENT_SUMMARY=	Poppler is a PDF rendering library based on the xpdf-3.0 code base (encoding data)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING


include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

COMPONENT_INSTALL_ARGS += datadir=/usr/share

build: $(BUILD_32)

install: $(INSTALL_32)
