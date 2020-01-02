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
# Copyright (c) 2014 Alexander Pyhalov. All rights reserved
# Copyright (c) 2020 Michal Nowak
#

BUILD_BITS=		32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libgsasl
COMPONENT_VERSION=	1.8.1
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/gsasl/
COMPONENT_SUMMARY=	Implementation of the Simple Authentication and Security Layer framework 
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_URL=	ftp://ftp.gnu.org/gnu/gsasl/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH=	\
	sha256:19e2f90525c531010918c50bb1febef0d7115d620150cc66153b9ce73ff814e6
COMPONENT_FMRI=		library/libgsasl
COMPONENT_CLASSIFICATION= System/Libraries
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

PATH=$(PATH.gnu)

CFLAGS+= -I/usr/include/idn

CONFIGURE_OPTIONS.32 += --sysconfdir=/etc
CONFIGURE_OPTIONS.32 += --libexecdir=/usr/lib
CONFIGURE_OPTIONS.64 += --libexecdir=/usr/lib/$(MACH64)
CONFIGURE_OPTIONS += --disable-static

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libidn
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libgcrypt
