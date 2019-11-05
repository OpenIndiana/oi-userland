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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		librsync
COMPONENT_VERSION=	0.9.7
COMPONENT_REVISION=	1
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://librsync.sourceforge.net/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:6633e4605662763a03bb6388529cbdfd3b11a9ec55b8845351c1bd9a92bc41d6
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/$(COMPONENT_NAME)/files/librsync/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download

# librsync documentation as originally found at:
# http://librsync.sourcefrog.net/doc/librsync.html
# http://librsync.sourcefrog.net/doc/librsync.pdf
# The files there are not in an easily downloadable format so a local
# archive has been created for them.
COMPONENT_NAME_1=	librsync-docs
COMPONENT_SRC_1=	$(COMPONENT_NAME_1)
COMPONENT_ARCHIVE_1=	$(COMPONENT_NAME_1)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH_1=	\
    sha256:e805819272f71b06823ee13f2dd7ddb92e75d75de18c33b7fd32133847c52afe
COMPONENT_ARCHIVE_URL_1=	http://dlc.openindiana.org/oi-build/source-archives/$(COMPONENT_ARCHIVE_1)
CLEAN_PATHS += $(COMPONENT_NAME_1)

CONFIGURE_FIX_LIBTOOL_RPATH = no

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

COMPONENT_PREP_ACTION = (cd $(@D) && libtoolize -f && autoreconf -fi)

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D)) ; \
	tar -xvf $(USERLAND_ARCHIVES)$(COMPONENT_ARCHIVE_1)

CONFIGURE_OPTIONS  +=	--enable-shared

CONFIGURE_ENV.64 += LT_SYS_LIBRARY_PATH="/lib/$(MACH64):/usr/lib/$(MACH64)"

PROTOUSRSHAREDOCDIR = $(PROTOUSRSHAREDIR)/doc/librsync-0.9.7

PATCH_LEVEL = 1

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
	$(MKDIR) -p $(PROTOUSRSHAREDOCDIR) ; \
	$(CP) librsync-docs/librsync.pdf $(PROTOUSRSHAREDOCDIR) ; \
	$(CP) -r librsync-docs/html $(PROTOUSRSHAREDOCDIR)

test: $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += library/popt
REQUIRED_PACKAGES += system/library
