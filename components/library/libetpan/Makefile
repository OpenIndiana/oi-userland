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
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		libetpan
COMPONENT_VERSION=	1.7
COMPONENT_PROJECT_URL=	http://www.etpan.org/libetpan.html
COMPONENT_SUMMARY=	A portable, efficient framework for different kinds of mail access: IMAP, SMTP, POP and NNTP
COMPONENT_FMRI=         library/libetpan
COMPONENT_CLASSIFICATION=       System/Libraries
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:47d0c049d8adcdcfd0698e9f1fcb85416b0b2f476eed1f52aae72c2883cf05b0
COMPONENT_ARCHIVE_URL=	https://github.com/dinhviethoa/libetpan/archive/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	BSD-3-Clause
COMPONENT_LICENSE_FILE=	COPYRIGHT

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION+= (cd $(@D) && NOCONFIGURE=1 ./autogen.sh)

CONFIGURE_OPTIONS += --with-sasl

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += database/berkeleydb-5
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/libsasl
REQUIRED_PACKAGES += web/curl
