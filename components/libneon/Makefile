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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME = neon
COMPONENT_VERSION = 0.29.5
COMPONENT_SRC = $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE = $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH = sha1:46e85922b2dad60f50393e7d8d4075c880c7e03e
COMPONENT_ARCHIVE_URL = http://webdav.org/neon/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATCH_LEVEL = 0

CC += $(CC_BITS)
CPPFLAGS += $(CPP_LARGEFILES)

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
CONFIGURE_OPTIONS += --with-libxml2

build: $(BUILD_32) $(BUILD_64)

GSED =	/usr/gnu/bin/sed

include ../../make-rules/shared-targets.mk

install: $(INSTALL_32) $(INSTALL_64)
	$(GSED) -f oracleman-stability $(PROTOUSRSHAREMAN3DIR)/neon.3 > \
	    $(PROTOUSRSHAREMAN3DIR)/neon.3.sed
	cp -fp $(PROTOUSRSHAREMAN3DIR)/neon.3.sed \
	    $(PROTOUSRSHAREMAN3DIR)/neon.3
	rm -f $(PROTOUSRSHAREMAN3DIR)/neon.3.sed

test: $(BUILD_32_and_64)
	@cd $(BUILD_DIR_32); env PATH="$(GNUBIN):$(PATH)" $(GMAKE) check
	@cd $(BUILD_DIR_64); env PATH="$(GNUBIN):$(PATH)" $(GMAKE) check

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include ../../make-rules/depend.mk

