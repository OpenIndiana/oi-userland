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
# Copyright 2018 Harry Liebel
# Copyright 2019 Michal Nowak
# Copyright 2021, 2022 Nona Hansel
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tig
COMPONENT_VERSION=	2.5.12
COMPONENT_SUMMARY=	Text-mode interface for git
COMPONENT_DESCRIPTION=	Tig is an ncurses-based text-mode interface for git. It functions mainly as a Git repository browser, but can also assist in staging changes for commit at chunk level and act as a pager for output from various Git commands.
COMPONENT_PROJECT_URL=	https://jonas.github.io/$(COMPONENT_NAME)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:5dda8a098810bb499096e17fc9f69c0a5915a23f46be27209fc8195d7a792108
COMPONENT_ARCHIVE_URL=	https://github.com/jonas/$(COMPONENT_NAME)/releases/download/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		developer/versioning/tig
COMPONENT_CLASSIFICATION= Development/Source Code Management
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

# This runs configure but configure doesn't generate a Makefile.
# Instead a Makefile comes with tig.
# Use cloney to copy a set of files to build.
# Same behaviour as the 'git' package
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

CFLAGS += -I/usr/include/ncurses

COMPONENT_INSTALL_TARGETS = install install-doc

# GNU grep is expected
COMPONENT_TEST_ENV += PATH=$(PATH.gnu)
COMPONENT_TEST_TARGETS = test

# Manually added build dependencies
REQUIRED_PACKAGES += text/asciidoc

# Auto-generated dependencies
REQUIRED_PACKAGES += $(READLINE_PKG)
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += system/library
