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

COMPONENT_NAME=		sysstat
COMPONENT_VERSION=	20151012
COMPONENT_FMRI=		diagnostic/sysstat
COMPONENT_CLASSIFICATION=	Applications/System Utilities
COMPONENT_SUMMARY=	sysstat - tool for quick overview of various Solaris stats
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH=	sha256:4ec664956b557f7c3a01eb644f731314f976e6ff6b83afe55c2d6e8f73ae0736
COMPONENT_ARCHIVE_URL=	http://www.maier-komor.de/sysstat/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://www.maier-komor.de/sysstat.html
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	LICENSE
# Note: the website says the project is under GPLv2, but sources provide a
# copy of GPLv3 explicitly. Probably the page was not updated in this regard.

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

# WARNING: non-autoconf "configure" script here
COMPONENT_PRE_BUILD_ACTION = \
	( cd $(@D) && \
		./configure \
			-c "$(CC)" \
			-m "$(BITS)" \
			-P "$(MACH$(BITS))" \
			-K "$(MACH$(BITS))" \
			--prefix "$(PROTOUSRDIR)" \
	)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
