#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"). You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2016 Adam Stevko
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		scfdot
COMPONENT_VERSION=	20130322
COMPONENT_REVISION= 2
COMPONENT_COMMIT_ID=	8b61bb49223b7f576d4f0eac75b74d35c99771ab
COMPONENT_SUMMARY=	SMF Dependency Graph Generator
COMPONENT_PROJECT_URL=	https://java.net/projects/scfdot/
COMPONENT_FMRI=		sysutils/scfdot
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_COMMIT_ID)
COMPONENT_ARCHIVE=	$(COMPONENT_COMMIT_ID).zip
COMPONENT_ARCHIVE_URL=	https://github.com/xen0l/scfdot/archive/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:769f29e7f5005b82c061e89d644118691a3cb9d2820602e897f906b34a77881e
COMPONENT_LICENSE=	CDDL
COMPONENT_LICENSE_FILE=	$(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_BUILD_TARGETS= scfdot
COMPONENT_BUILD_ENV+= CC="$(CC) $(gcc_OPT)"

$(INSTALL_64):	$(BUILD_64)
		$(MKDIR) $(PROTOUSRBINDIR)

		$(INSTALL) -m 755 $(BUILD_DIR_64)/scfdot $(PROTOUSRBINDIR)

		$(TOUCH) $@

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += system/library
# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
