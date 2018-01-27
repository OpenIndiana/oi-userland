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
# Copyright 2013 Aurelien Larcher.  All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		zziplib
COMPONENT_VERSION=	0.13.67
COMPONENT_REVISION=	1
COMPONENT_SUMMARY=	Lightweight ZIP library
COMPONENT_PROJECT_URL=	http://zziplib.sourceforge.net/
COMPONENT_FMRI=		compress/zziplib
COMPONENT_CLASSIFICATION=Applications/System Utilities
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:1278178bdabac832da6bbf161033d890d335a2e38493c5af553ff5ce7b9b0220
COMPONENT_ARCHIVE_URL= \
	https://github.com/gdraheim/zziplib/archive/v$(COMPONENT_VERSION).tar.gz
COMPONENT_LICENSE=	GPLv2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATH=$(PATH.gnu)

CONFIGURE_OPTIONS+=	--enable-shared
CONFIGURE_OPTIONS+=	--disable-static
CONFIGURE_OPTIONS+=	--enable-largefile

CONFIGURE_ENV.64+=	lt_cv_sys_lib_dlsearch_path_spec="/lib/$(MACH64) /usr/lib/$(MACH64)"

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

# Build dependencies
REQUIRED_PACKAGES += text/xmlto

REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
