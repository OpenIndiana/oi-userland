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
# Copyright (c) 2012, 2015, Oracle and/or its affiliates. All rights reserved.
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

TPNO=			7904

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk
include $(WS_MAKE_RULES)/lint-libraries.mk

COMPONENT_PREP_ACTION = \
        (cd $(@D) ; $(TOUCH) config.rpath) ;

# requires an older automake to reconfigure
COMPONENT_PREP_ACTION += \
	(cd $(@D) ; ACLOCAL=aclocal-1.11 AUTOMAKE=automake-1.11 autoreconf -fiv)

# Needed to get "gmake test" to work.
COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

# Add /usr/gnu/bin at the front of $PATH for GNU gettext.
CONFIGURE_ENV +=	PATH=/usr/gnu/bin:$(PATH)

CONFIGURE_OPTIONS +=	--disable-nls

CONFIGURE_OPTIONS += CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS += LDFLAGS="$(LDFLAGS)"

PKG_PROTO_DIRS +=	$(COMPONENT_DIR)/files

# Master test results are the same for 32-bit and 64-bit, so override
# here, rather than create multiple identical master files.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

# common targets
configure:	$(CONFIGURE_32_and_64)

build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(TEST_32_and_64)

REQUIRED_PACKAGES += system/library
