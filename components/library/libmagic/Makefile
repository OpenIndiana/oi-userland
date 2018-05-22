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
# Copyright 2016 Jim Klimov
#
include ../../../make-rules/shared-macros.mk

# Note: The primary component we deliver initially is libmagic here
# There is already a "file" utility with true Unix legacy in our OS
# Still, for the sake of completeness and to match GNU/Linux userland
# we ALSO deliver a "gfile" built from darwinsys sources, as a bonus.
COMPONENT_NAME=		file
COMPONENT_FMRI=		library/magic
COMPONENT_VERSION=	5.33
COMPONENT_PROJECT_URL=	http://www.darwinsys.com/file/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha256:1c52c8c3d271cd898d5511c36a68059cda94036111ab293f01f83c3525b737c6
COMPONENT_ARCHIVE_URL=	ftp://ftp.astron.com/pub/file/$(COMPONENT_ARCHIVE)
COMPONENT_SUMMARY=	libmagic for recognizing the type of data contained in a computer file using magic numbers
COMPONENT_CLASSIFICATION=	System/Libraries
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	BSD

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
