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

BUILD_BITS=32
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		autossh
COMPONENT_FMRI=		network/autossh
COMPONENT_CLASSIFICATION=	System/Security
COMPONENT_VERSION=	1.4g
IPS_COMPONENT_VERSION=	1.4.7
COMPONENT_LICENSE=	BSD-like
COMPONENT_PROJECT_URL=	http://www.harding.motd.ca/$(COMPONENT_NAME)
COMPONENT_SUMMARY=	autossh tunnel maintainer
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	sha256:5fc3cee3361ca1615af862364c480593171d0c54ec156de79fc421e31ae21277
COMPONENT_ARCHIVE_URL=	http://www.harding.motd.ca/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)

TEST_TARGET=$(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = \
		(cd $(@D) &&\
		aclocal -I . &&\
		autoheader &&\
		autoconf &&\
		$(RM) config.h )

COMPONENT_PRE_CONFIGURE_ACTION = \
		($(CLONEY) $(SOURCE_DIR) $(@D))

REQUIRED_PACKAGES += system/library
