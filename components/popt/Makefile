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
# Copyright (c) 2012, 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		popt
COMPONENT_VERSION=	1.7
COMPONENT_PROJECT_URL=	http://freecode.com/projects/popt/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:4e75cb28793f0d44134f71fae53057d5f250805e6268fbd9c9780654b73b0dc1
COMPONENT_ARCHIVE_URL=	http://sourceforge.net/projects/cross-stuff/files/cross-stuff/1.0/$(COMPONENT_ARCHIVE)/download
COMPONENT_BUGDB=	library/popt

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PREP_ACTION = \
        (cd $(@D) ; \
	$(TOUCH) config.rpath ; \
	libtoolize -f ; \
	aclocal -I . ; \
	autoconf ; \
	automake -a -c -f )

# Needed to get "gmake test" to work.
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

# Add /usr/gnu/bin at the front of $PATH for GNU gettext.
CONFIGURE_ENV +=	PATH=/usr/gnu/bin:$(PATH)

CONFIGURE_OPTIONS +=	--disable-nls

CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += LDFLAGS="$(LDFLAGS)"

PKG_PROTO_DIRS +=	$(COMPONENT_DIR)/files

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets
build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include ../../make-rules/depend.mk
