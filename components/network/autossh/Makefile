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
# Copyright 2016 Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		autossh
COMPONENT_VERSION=	1.4.7
HUMAN_VERSION=		1.4g
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=	autossh tunnel maintainer
COMPONENT_PROJECT_URL=	https://www.harding.motd.ca/$(COMPONENT_NAME)
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	sha256:5fc3cee3361ca1615af862364c480593171d0c54ec156de79fc421e31ae21277
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		network/autossh
COMPONENT_CLASSIFICATION=	System/Security
COMPONENT_LICENSE=	BSD-like

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = \
		(cd $(@D) &&\
		aclocal -I . &&\
		autoheader &&\
		autoreconf --force --install &&\
		$(RM) config.h )

COMPONENT_PRE_CONFIGURE_ACTION = \
		($(CLONEY) $(SOURCE_DIR) $(@D))

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
