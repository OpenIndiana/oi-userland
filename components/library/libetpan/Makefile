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
# Copyright (c) 2016 Sergey Avseyev
# Copyright (c) 2020 Andreas Wacknitz
#
BUILD_BITS=			32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libetpan
COMPONENT_VERSION=	1.9.4
COMPONENT_PROJECT_URL=	https://www.etpan.org/libetpan.html
COMPONENT_SUMMARY=	A portable, efficient framework for different kinds of mail access: IMAP, SMTP, POP and NNTP
COMPONENT_FMRI=         library/libetpan
COMPONENT_CLASSIFICATION=       System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:82ec8ea11d239c9967dbd1717cac09c8330a558e025b3e4dc6a7594e80d13bb1
COMPONENT_ARCHIVE_URL=	https://github.com/dinhviethoa/libetpan/archive/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	BSD-3-Clause
COMPONENT_LICENSE_FILE=	COPYRIGHT

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION+= (cd $(@D) && NOCONFIGURE=1 ./autogen.sh)

CONFIGURE_OPTIONS += --with-sasl
CONFIGURE_OPTIONS += --disable-static

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libsasl
REQUIRED_PACKAGES += web/curl
