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
# Copyright (c) 2012, 2016, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		popt
COMPONENT_VERSION=	1.16
COMPONENT_PROJECT_URL=	http://freecode.com/projects/popt/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:e728ed296fe9f069a0e005003c3d6b2dde3d9cad453422a10d6558616d304cc8
COMPONENT_ARCHIVE_URL=	https://launchpad.net/$(COMPONENT_NAME)/head/$(COMPONENT_VERSION)/+download/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/popt

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/configure.mk
include $(WS_TOP)/make-rules/ips.mk

COMPONENT_PREP_ACTION = \
        (cd $(@D) && \
	$(TOUCH) config.rpath ) ;

# Needed to get "gmake test" to work.
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

# Add /usr/gnu/bin at the front of $PATH for GNU gettext.
CONFIGURE_ENV +=	PATH=/usr/gnu/bin:$(PATH)

CONFIGURE_OPTIONS +=	--disable-nls

PKG_PROTO_DIRS +=	$(COMPONENT_DIR)/files

build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

# api-sanity-autotest.pl is part of the API Sanity Checker
# http://ispras.linuxbase.org/index.php/API_Sanity_Autotest
# (which we don't have in Solaris), so expect that test to fail.
test:           $(TEST_32_and_64)

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
