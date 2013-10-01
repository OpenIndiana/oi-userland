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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		snort
COMPONENT_VERSION=	2.9.2
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:04d375b627dd256d6257f2cbe5a770e4552e3f35d5e2100b97f75426b600d8cb
COMPONENT_PROJECT_URL=	http://www.snort.org/
COMPONENT_ARCHIVE_URL=	$(COMPONENT_PROJECT_URL)dl/snort-current/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/snort

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATH=/usr/gnu/bin:/usr/bin

# Need to recreate the configure script for gethrtime checks.
COMPONENT_PREP_ACTION +=	(cd $(@D); autoconf);

CONFIGURE_OPTIONS +=	--with-libpcre-libraries="/usr/lib"
CONFIGURE_OPTIONS +=	--with-dnet-libraries="/usr/lib"
CONFIGURE_OPTIONS +=	--without-mysql
CONFIGURE_OPTIONS +=	--without-postgresql
CONFIGURE_OPTIONS +=	--enable-zlib
CONFIGURE_OPTIONS +=	--enable-ipv6
CONFIGURE_OPTIONS +=	--disable-static-daq
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	LDFLAGS="$(LDFLAGS)"

# Move snort shared objects to 64-bit path to stop pkglint bitching.
#COMPONENT_POST_INSTALL_ACTION += \
#	$(MV) $(PROTOUSRLIBDIR)/snort_dynamicengine $(PROTOUSRLIBDIR64); \
#	$(MV) $(PROTOUSRLIBDIR)/snort_dynamicpreprocessor $(PROTOUSRLIBDIR64) ;

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
