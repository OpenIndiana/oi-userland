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
# Copyright 2014 Alexander Pyhalov.  All rights reserved.
# Copyright 2020 Michal Nowak
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pdsh
COMPONENT_VERSION=	2.34
COMPONENT_REVISION =	1
COMPONENT_FMRI=		shell/pdsh
COMPONENT_SUMMARY=	Parallel distributed shell
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_PROJECT_URL=	https://github.com/chaos/pdsh/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= \
	sha256:b47b3e4662736ef44b6fe86e3d380f95e591863e69163aa0592e9f9f618521e9
COMPONENT_ARCHIVE_URL= \
	https://github.com/chaos/pdsh/releases/download/$(COMPONENT_SRC)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2

USE_DEFAULT_TEST_TRANSFORMS = yes

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# Required for the test suite
COMPONENT_PRE_CONFIGURE_ACTION = ($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --with-ssh
CONFIGURE_OPTIONS += --with-rsh
CONFIGURE_OPTIONS += --with-readline
CONFIGURE_OPTIONS += --with-dshgroups

COMPONENT_TEST_TRANSFORMS += '-e "/XFAIL:/p"'
COMPONENT_TEST_TRANSFORMS += '-e "/XPASS:/p"'

# Auto-generated dependencies
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += system/library
