#
# CDDL HEADER START
#
# The contents of this file are subject to the terms of the
# Common Development and Distribution License (the "License").
# You may not use this file except in compliance with the License.
#
# You can obtain a copy of the license at usr/src/OPENSOLARIS.LICENSE
# or http://www.opensolaris.org/os/licensing.
# See the License for the specific language governing permissions
# and limitations under the License.
#
# When distributing Covered Code, include this CDDL HEADER in each
# file and include the License file at usr/src/OPENSOLARIS.LICENSE.
# If applicable, add the following below this CDDL HEADER, with the
# fields enclosed by brackets "[]" replaced with your own identifying
# information: Portions Copyright [yyyy] [name of copyright owner]
#
# CDDL HEADER END
#
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME = libneon
COMPONENT_VERSION = 0.30.1
COMPONENT_PROJECT_URL=	http://www.webdav.org/neon/
COMPONENT_SRC_NAME = neon
COMPONENT_SRC = $(COMPONENT_SRC_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE = $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH = \
    sha256:00c626c0dc18d094ab374dbd9a354915bfe4776433289386ed489c2ec0845cdd
COMPONENT_ARCHIVE_URL = $(COMPONENT_PROJECT_URL)$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/neon

TPNO=			21902

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

PATCH_LEVEL = 0

CC += $(CC_BITS)
CPPFLAGS += $(CPP_LARGEFILES)

COMPONENT_TEST_MASTER = \
       $(COMPONENT_TEST_RESULTS_DIR)/results-libneon.master

COMPONENT_TEST_TRANSFORMS += \
     '-e "/libtool/d"' \
     '-e "/-m32/d"' \
     '-e "/-m64/d"' \
     '-e "/ld: warning/d"' \
     '-e "/warning/d"' \
     '-e "/prototype:/d"' \
     '-e "/argument/d"' \
     '-e "/Entering/d"' \
     '-e "/Leaving/d"' \
     '-e "/Nothing to be done/d"' \
     '-e "s/[0-9]\{1,\}\.[0-9]\{1,\} s, //g"' \
     '-e "s^[0-9]\{1,\} kB/s^^g"'  \
     '-e "s^[0-9]\{1,\}  kB/s^^g"'  \
     '-e "s^[0-9]\{1,\}\.[0-9]\{1,\}  MB/s^^g"' \
     '-e "s^[0-9]\{1,\}\.[0-9]\{1,\} MB/s^^g"' \
     '-e "s/([0-9]\{1,\} B)//g"' \
     '-e "s/([0-9]\{1,\}  B)//g"' \
     '-e "s/copied,/copied/g"'  \
     '-e "s/ \{1,\}copied/ copied/g"'  \
     '-e "s/copied $$/copied/g"'  \
     '-e "s/copied [0-9]\{1,\}\./copied/g"' 

CONFIGURE_ENV += CFLAGS="$(CFLAGS)"
CONFIGURE_ENV += CPPFLAGS="$(CPPFLAGS)"

CONFIGURE_OPTIONS += --localstatedir=/var
CONFIGURE_OPTIONS += --mandir=/usr/share/man
CONFIGURE_OPTIONS += --infodir=/usr/share/info
CONFIGURE_OPTIONS += --enable-shared
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --enable-webdav
CONFIGURE_OPTIONS += --enable-threadsafe-ssl=posix
CONFIGURE_OPTIONS += --enable-nls
CONFIGURE_OPTIONS += --disable-warnings
CONFIGURE_OPTIONS += --disable-ld-version-script
CONFIGURE_OPTIONS += --with-zlib
CONFIGURE_OPTIONS += --with-ssl=openssl
CONFIGURE_OPTIONS += --with-libproxy
CONFIGURE_OPTIONS += --with-gssapi
CONFIGURE_OPTIONS += --with-libxml2
CONFIGURE_OPTIONS += --with-pic

COMPONENT_TEST_ENV +=	PATH="$(GNUBIN):$(PATH)"

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

configure:	$(CONFIGURE_32_and_64)

build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

system-test:    $(SYSTEM_TESTS_NOT_IMPLEMENTED)

REQUIRED_PACKAGES += library/libproxy
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/security/gss
REQUIRED_PACKAGES += library/libproxy
