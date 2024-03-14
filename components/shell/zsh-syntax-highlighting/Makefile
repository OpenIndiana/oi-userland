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
# Copyright 2018 Michal Nowak
# Copyright 2020 Andreas Wacknitz
#

BUILD_STYLE= justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		zsh-syntax-highlighting
COMPONENT_VERSION=	0.8.0
COMPONENT_SUMMARY=	Fish shell like syntax highlighting for Zsh
COMPONENT_PROJECT_URL=	https://github.com/zsh-users/zsh-syntax-highlighting
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/archive/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:5981c19ebaab027e356fe1ee5284f7a021b89d4405cc53dc84b476c3aee9cc32
COMPONENT_FMRI=		utility/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION= System/Shells
COMPONENT_LICENSE=	Various
COMPONENT_LICENSE_FILE=	COPYING.md

include $(WS_MAKE_RULES)/common.mk

COMPONENT_INSTALL_ENV += PREFIX=$(USRDIR)

COMPONENT_TEST_TARGETS= test

COMPONENT_TEST_TRANSFORMS= \
	'-ne "/^ok/p" ' \
	'-ne "/^not ok/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/zsh
