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
# Copyright 2011 EveryCity Ltd. All rights reserved.
# Copyright 2013, Jon Tibble.  All rights reserved.
# Copyright 2016, Jim Klimov
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		mbuffer
COMPONENT_VERSION=	20160613
COMPONENT_FMRI=		shell/mbuffer
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_SUMMARY=	mbuffer - tool for buffering data streams
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	sha256:67a92869c0a7e8da1bd96b70cc7de7233286a7ccba55ffc9b55d0d611df649fd
COMPONENT_ARCHIVE_URL=	http://www.maier-komor.de/software/mbuffer/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.maier-komor.de/mbuffer.html
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	LICENSE

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += library/security/libmhash
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
