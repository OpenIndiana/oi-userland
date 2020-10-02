#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL)". You may
# only use this file in accordance with the terms of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source. A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2015 Alexander Pyhalov
# Copyright 2019 Michal Nowak
#

BUILD_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		logrotate
COMPONENT_VERSION=	3.16.0
COMPONENT_PROJECT_URL=	https://github.com/logrotate/logrotate
COMPONENT_SUMMARY=	Logrotate - Rotates and compresses log files
COMPONENT_FMRI=		system/file/logrotate
COMPONENT_CLASSIFICATION=	System/Administration and Configuration
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:e1bae2c72115cf16007bb98ea38752d1120010cfb70addd9867d952c7529de3b
COMPONENT_ARCHIVE_URL=	https://github.com/logrotate/logrotate/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv2
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

# Tests otherwise fail
unexport SHELLOPTS

# Auto-generated dependencies
REQUIRED_PACKAGES += library/popt
REQUIRED_PACKAGES += system/library
