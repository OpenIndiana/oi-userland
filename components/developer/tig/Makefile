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
#

PREFERRED_BITS=64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		tig
COMPONENT_VERSION=	2.4.1
COMPONENT_FMRI=		developer/versioning/tig
COMPONENT_PROJECT_URL=	https://jonas.github.io/$(COMPONENT_NAME)
COMPONENT_SUMMARY=	Text-mode interface for git
COMPONENT_DESCRIPTION=	Tig is an ncurses-based text-mode interface for git. It functions mainly as a Git repository browser, but can also assist in staging changes for commit at chunk level and act as a pager for output from various Git commands.
COMPONENT_CLASSIFICATION= Development/Source Code Management
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:b6b6aa183e571224d0e1fab3ec482542c1a97fa7a85b26352dc31dbafe8558b8
COMPONENT_ARCHIVE_URL=	https://github.com/jonas/$(COMPONENT_NAME)/releases/download/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# This runs configure but configure doesn't generate a Makefile.
# Instead a Makefile comes with tig.
# Use cloney to copy a set of files to build.
# Same behaviour as the 'git' package
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

# Place the config file in /etc
CONFIGURE_OPTIONS += --sysconfdir=$(ETCDIR)

CFLAGS +=	-I/usr/include/ncurses

COMPONENT_INSTALL_TARGETS = install install-doc

# GNU grep is expected
COMPONENT_TEST_ENV += PATH=$(PATH.gnu)

COMPONENT_TEST_TARGETS = test

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

REQUIRED_PACKAGES += text/asciidoc
# Auto-generated dependencies
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += system/library
