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
# Copyright (c) 2015 Alexander Pyhalov
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=           libebml
COMPONENT_VERSION=        1.3.1
COMPONENT_PROJECT_URL=    http://matroska-org.github.io/libebml/
COMPONENT_SUMMARY=        Extensible Binary Markup Language
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=        \
    sha256:195894b31aaca55657c9bc157d744f23b0c25597606b97cfa5a9039c4b684295
COMPONENT_ARCHIVE_URL=        http://dl.matroska.org/downloads/libebml/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	LICENSE.LGPL
COMPONENT_FMRI=		library/libebml
COMPONENT_CLASSIFICATION=	System/Libraries

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)
