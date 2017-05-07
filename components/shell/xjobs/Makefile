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
# Copyright 2016, Jim Klimov
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		xjobs
COMPONENT_VERSION=	20151016
COMPONENT_FMRI=		shell/xjobs
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_SUMMARY=	xjobs - shell tool for smart parallel execution of jobs
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	sha256:1b80abe5effe057db21897f897842dccd76e7812c1caaa80f9b8e85cca409251
COMPONENT_ARCHIVE_URL=	http://www.maier-komor.de/xjobs/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.maier-komor.de/xjobs.html
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION =  \
		($(CLONEY) $(SOURCE_DIR) $(@D))

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
