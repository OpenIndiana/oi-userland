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
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		logrotate
COMPONENT_VERSION=	3-9-1
IPS_COMPONENT_VERSION=	$(subst -,.,$(COMPONENT_VERSION))
COMPONENT_PROJECT_URL=	https://github.com/logrotate/logrotate
COMPONENT_SUMMARY=	Logrotate - Rotates and compresses log files
COMPONENT_SRC=		$(COMPONENT_NAME)-r$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:5bf8e478c428e7744fefa465118f8296e7e771c981fb6dffb7527856a0ea3617
COMPONENT_ARCHIVE_URL=	https://github.com/logrotate/logrotate/archive/r$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE_FILE=	COPYING
COMPONENT_LICENSE=	GPLv2
COMPONENT_FMRI=		system/file/logrotate
COMPONENT_CLASSIFICATION=	System/Administration and Configuration

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=/usr/gnu/bin:/usr/bin

COMPONENT_PREP_ACTION =        ( cd $(@D)  && \
				$(TOUCH) NEWS README AUTHORS ChangeLog &&\
				libtoolize --copy --force &&\
				aclocal -I. &&\
				automake -c -f -a &&\
				autoconf )

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)
