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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		librsync
COMPONENT_VERSION=	0.9.7
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://librsync.sourceforge.net/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:d575eb5cae7a815798220c3afeff5649d3e8b4ab
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/$(COMPONENT_NAME)/files/librsync/$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)/download

# librsync documentation as originally found at:
# http://librsync.sourcefrog.net/doc/librsync.html
# http://librsync.sourcefrog.net/doc/librsync.pdf
# The files there are not in an easily downloadable format so a local
# archive has been created for them.
COMPONENT_NAME_1=	librsync-docs
COMPONENT_SRC_1=	$(COMPONENT_NAME_1)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE_1=	$(COMPONENT_SRC_1).tar.gz
COMPONENT_ARCHIVE_HASH_1=	sha1:87b947aa4312bcf776d442abc23e142eb35c16da
COMPONENT_ARCHIVE_URL_1=	$(EXTERNAL_ARCHIVE_MIRROR)/$(COMPONENT_ARCHIVE_1)
CLOBBER_PATHS += $(COMPONENT_NAME_1)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D)) ; \
	tar -xvf $(COMPONENT_ARCHIVE_1)

CFLAGS += -features=no%extinl

CONFIGURE_ENV += CFLAGS="$(CFLAGS)"

CONFIGURE_OPTIONS  +=	--enable-shared

PROTOUSRSHAREDOCDIR = $(PROTOUSRSHAREDIR)/doc/librsync-0.9.7

PATCH_LEVEL = 1

build: $(BUILD_32_and_64)

install: $(INSTALL_32_and_64)
	$(MKDIR) -p $(PROTOUSRSHAREDOCDIR) ; \
	$(CP) librsync-docs/librsync.pdf $(PROTOUSRSHAREDOCDIR) ; \
	$(CP) -r librsync-docs/html $(PROTOUSRSHAREDOCDIR)

test: $(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES = $(BUILD_TOOLS)

include ../../make-rules/depend.mk
