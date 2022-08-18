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
# Copyright 2013 Adam Stevko. All right reserved.
# Copyright 2017 Andreas Grueninger, Grueninger GmbH, (grueni). All rights reserved.
#

BUILD_STYLE=configure
BUILD_BITS=64
USE_OPENSSL11=yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         libesmtp
COMPONENT_VERSION=      1.0.6
COMPONENT_REVISION=     2
COMPONENT_FMRI=         library/$(COMPONENT_NAME)
COMPONENT_CLASSIFICATION=Development/C
COMPONENT_PROJECT_URL=  http://www.stafford.uklinux.net/libesmtp
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:c99907a63c1135db2659e60e53eaa46723e22e31c9affc054a0a61941f2c1bab
COMPONENT_ARCHIVE_URL=  http://github.com/grueni/$(COMPONENT_NAME)/archive/v${COMPONENT_VERSION}.tar.gz
COMPONENT_LICENSE=      GPLv2
COMPONENT_SUMMARY=      libESMTP - A Library for Posting Electronic Mail

include $(WS_MAKE_RULES)/common.mk

CFLAGS= $(CC_BITS) -D__EXTENSIONS__ \
	-D_POSIX_PTHREAD_SEMANTICS \
	-DNAME_MAX=255 -DHOST_NAME_MAX=255 \
        -L$(OPENSSL_LIBDIR.$(BITS)) -R$(OPENSSL_LIBDIR.$(BITS))

CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += LDLAGS="-L$(OPENSSL_LIBDIR.$(BITS)) -R$(OPENSSL_LIBDIR.$(BITS))"
CONFIGURE_OPTIONS += LT_SYS_LIBRARY_PATH="$(OPENSSL_LIBDIR.$(BITS))"
CONFIGURE_OPTIONS += --disable-isoc

COMPONENT_PREP_ACTION=(cd $(SOURCE_DIR); mkdir m4; $(AUTORECONF) -i)

COMPONENT_PRE_CONFIGURE_ACTION=($(CLONEY) $(SOURCE_DIR) $(@D))

# Auto-generated dependencies
REQUIRED_PACKAGES += library/security/openssl-11
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
