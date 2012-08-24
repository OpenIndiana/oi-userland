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

#
# Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		sg3_utils
COMPONENT_VERSION=	1.28
COMPONENT_PROJECT_URL=	http://sg.danny.cz/sg/sg3_utils.html
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tgz
COMPONENT_ARCHIVE_HASH= \
    sha256:da8bd627a6246b709e2a0321fa9d5ca09a33354a1ae40c74cd37efb69b9f8118
COMPONENT_ARCHIVE_URL=	http://sg.danny.cz/sg/p/$(COMPONENT_ARCHIVE)

COMPONENT_ARCHIVE_1 =	rescan-scsi-bus.sh-1.35
COMPONENT_ARCHIVE_HASH_1 = \
    sha256:324630d65ef85480f3fc57e8c1648dba2c79fa1927e26e6dfd1b64c7b8aba0b1
COMPONENT_ARCHIVE_URL_1 = http://www.garloff.de/kurt/linux/rescan-scsi-bus.sh-1.35

COMPONENT_POST_UNPACK_ACTION = \
	$(CP) $(COMPONENT_DIR)/rescan-scsi-bus.sh-1.35 \
		$(COMPONENT_SRC)/rescan-scsi-bus.sh

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

CPPFLAGS += -I$(COMPONENT_DIR)/$(COMPONENT_SRC)/include

CONFIGURE_OPTIONS +=	--disable-static
CONFIGURE_OPTIONS += CPPFLAGS="$(CPPFLAGS)"

# Don't use rpath!
COMPONENT_POST_CONFIGURE_ACTION = \
	(cd $(BUILD_DIR_32) ; \
	$(GSED) -i 's|^hardcode_libdir_flag_spec=.*|hardcode_libdir_flag_spec=""|g' libtool ; \
	$(GSED) -i 's|^runpath_var=LD_RUN_PATH|runpath_var=DIE_RPATH_DIE|g' libtool)

# Move the section 8 man pages into section 1m.
COMPONENT_POST_INSTALL_ACTION = \
	for f in $(PROTOUSRSHAREMANDIR)/man8/*; do \
		mv $$f $${f%.8}.1m; \
	done ; \
	$(MV) $(PROTOUSRSHAREMANDIR)/man8 $(PROTOUSRSHAREMANDIR)/man1m

PKG_PROTO_DIRS +=	$(COMPONENT_DIR)/files

# common targets
build:          $(BUILD_32)

install:        $(INSTALL_32)

test:           $(TEST_32)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include ../../make-rules/depend.mk
