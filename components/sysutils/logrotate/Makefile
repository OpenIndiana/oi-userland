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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		logrotate
COMPONENT_VERSION=	3.15.0
COMPONENT_PROJECT_URL=	https://github.com/logrotate/logrotate
COMPONENT_SUMMARY=	Logrotate - Rotates and compresses log files
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:724da48020bb801ba02728bde4c5bdce2daae46ac360d163e40ebf6914bb9927
COMPONENT_ARCHIVE_URL=	https://github.com/logrotate/logrotate/releases/download/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	GPLv2
COMPONENT_FMRI=		system/file/logrotate
COMPONENT_CLASSIFICATION=	System/Administration and Configuration

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CONFIGURE_SBINDIR.64= $(CONFIGURE_SBINDIR.32)

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
				$(TOUCH) NEWS README AUTHORS ChangeLog && \
				libtoolize --copy --force && \
				aclocal -I. && \
				automake -c -f -a && \
				autoconf )

# Tests otherwise fail
unexport SHELLOPTS

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(TEST_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/popt
REQUIRED_PACKAGES += system/library
