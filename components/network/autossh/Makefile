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
COMPONENT_FMRI=		network/autossh
COMPONENT_CLASSIFICATION=	System/Security
COMPONENT_VERSION=	1.4e
IPS_COMPONENT_VERSION=	1.4.5
COMPONENT_LICENSE=	BSD
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_PROJECT_URL=	http://www.harding.motd.ca/$(COMPONENT_NAME)
COMPONENT_SUMMARY=	autossh tunnel maintainer
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	sha256:9e8e10a59d7619176f4b986e256f776097a364d1be012781ea52e08d04679156
COMPONENT_ARCHIVE_URL=	http://www.harding.motd.ca/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = \
		(cd $(@D) &&\
		aclocal -I . &&\
		autoheader &&\
		autoconf &&\
		$(RM) config.h )

COMPONENT_PRE_CONFIGURE_ACTION = \
		($(CLONEY) $(SOURCE_DIR) $(@D))

build:		$(BUILD_32)

install:	$(INSTALL_32)

REQUIRED_PACKAGES += system/library
