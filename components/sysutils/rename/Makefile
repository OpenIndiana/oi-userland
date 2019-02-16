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
# Copyright 2019 Michal Nowak
#

PREFERRED_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		rename
COMPONENT_MAJOR_VERSION=2.33
COMPONENT_MINOR_VERSION=1
COMPONENT_VERSION=	$(COMPONENT_MAJOR_VERSION).$(COMPONENT_MINOR_VERSION)
COMPONENT_SUMMARY=	Various Linux utilities
COMPONENT_PROJECT_URL=	https://git.kernel.org/pub/scm/utils/util-linux/util-linux.git
COMPONENT_FMRI=		file/rename
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_SRC=		util-linux-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=	https://mirrors.edge.kernel.org/pub/linux/utils/util-linux/v$(COMPONENT_MAJOR_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	sha256:c14bd9f3b6e1792b90db87696e87ec643f9d63efa0a424f092a5a6b2f2dbef21
COMPONENT_LICENSE_FILE=	README.licensing
COMPONENT_LICENSE=	GPL-2.0-or-later, GPL-2.0, LGPL-2.1-or-later, BSD-3-Clause, BSD-4-Clause-UC, Public Domain

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH = $(PATH.gnu)

# Handpick stuff we want as most stuff won't build
CONFIGURE_OPTIONS +=	--disable-all-programs
CONFIGURE_OPTIONS +=	--enable-rename 

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
