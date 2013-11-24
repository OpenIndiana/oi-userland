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
# Copyright 2013, Aurelien Larcher. All rights reserved.
# 

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		bash-completion
COMPONENT_VERSION=	2.1
COMPONENT_FMRI=		utility/$(COMPONENT_NAME)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/bash/
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)_$(COMPONENT_VERSION).orig.tar.bz2
COMPONENT_ARCHIVE_HASH = \
    sha256:2b606804a7d5f823380a882e0f7b6c8a37b0e768e72c3d4107c51fbe8a46ae4f
COMPONENT_ARCHIVE_URL=	http://ftp.de.debian.org/debian/pool/main/b/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	$(COMPONENT_FMRI)
COMPONENT_SUMMARY=	Debian extensions to bash standard completion

COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CONFIGURE_PREFIX=	/usr

CONFIGURE_OPTIONS += --sysconfdir=/etc

build: $(BUILD_32)

install: $(INSTALL_32)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include $(WS_MAKE_RULES)/depend.mk

