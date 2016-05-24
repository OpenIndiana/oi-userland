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
# Copyright (c) 2016 Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		dumb
COMPONENT_VERSION=	0.9.3
COMPONENT_PROJECT_URL=	http://dumb.sourceforge.net/
COMPONENT_SUMMARY=	DUMB is a library for playing MOD, IT, XM and S3M music files
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:8d44fbc9e57f3bac9f761c3b12ce102d47d717f0dd846657fb988e0bb5d1ea33
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/dumb/files/dumb/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=	library/audio/libdumb
COMPONENT_LICENSE =	DUMB
COMPONENT_LICENSE_FILE =	licence.txt
COMPONENT_CLASSIFICATION =	System/Multimedia Libraries

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

USRLIBDIR.32 = $(USRLIBDIR)
USRLIBDIR.64 = $(USRLIBDIR64)
USRBINDIR.32 = $(USRBINDIR)
USRBINDIR.64 = $(USRBINDIR64)

COMPONENT_PRE_BUILD_ACTION = \
    ($(CLONEY) $(SOURCE_DIR) $(@D) && $(CP) $(COMPONENT_DIR)/files/config.txt $(@D)/make/ )

COMPONENT_BUILD_ARGS += PREFIX="$(USRDIR)"
COMPONENT_BUILD_ARGS += LIBDIR="$(USRLIBDIR.$(BITS))"
COMPONENT_BUILD_ARGS += BINDIR="$(USRBINDIR.$(BITS))"
COMPONENT_BUILD_ARGS += LDFLAGS_CUSTOM="$(LDFLAGS) $(LDFLAGS.$(BITS))"
COMPONENT_BUILD_ARGS += CFLAGS_CUSTOM="$(CFLAGS) $(CFLAGS.$(BITS))"

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)
