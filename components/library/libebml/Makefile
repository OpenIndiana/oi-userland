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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=           libebml
COMPONENT_VERSION=        1.3.4
COMPONENT_PROJECT_URL=    http://matroska-org.github.io/libebml/
COMPONENT_SUMMARY=        Extensible Binary Markup Language
COMPONENT_SRC=            $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=        $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= \
  sha256:c50d3ecf133742c6549c0669c3873f968e11a365a5ba17b2f4dc339bbe51f387
COMPONENT_ARCHIVE_URL= \
  http://dl.matroska.org/downloads/libebml/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	LGPLv2.1
COMPONENT_LICENSE_FILE=	LICENSE.LGPL
COMPONENT_FMRI=		library/libebml
COMPONENT_CLASSIFICATION=	System/Libraries

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-4-runtime
REQUIRED_PACKAGES += system/library/gcc-4-runtime
