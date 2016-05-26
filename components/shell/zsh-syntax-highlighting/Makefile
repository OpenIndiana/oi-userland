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

COMPONENT_NAME=		zsh-syntax-highlighting
COMPONENT_VERSION=	0.4.1
COMPONENT_SUMMARY=	Fish shell like syntax highlighting for Zsh.
COMPONENT_PROJECT_URL=	https://github.com/zsh-users/zsh-syntax-highlighting
COMPONENT_FMRI=		utility/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Shells
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	https://github.com/zsh-users/zsh-syntax-highlighting/archive/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:971b9c1e881a8d60442e40003c9e4c98bd1d5243a32fdf386a217c4cd7815197
COMPONENT_LICENSE=	Various
COMPONENT_LICENSE_FILE= $(COMPONENT_NAME).license

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_INSTALL_ENV+= PREFIX="/usr"

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)
