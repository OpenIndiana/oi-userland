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
# Copyright (c) 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2013  Erol Zavidic. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		webalizer
COMPONENT_VERSION=	2.23.5
HUMAN_VERSION=		2.23-05
COMPONENT_PROJECT_URL=	http://www.webalizer.org/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-src.tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:afc88b8ee0927d9ed004962cb7e3d3054ef7628c7bc8a7b2e3ea1d758a47885a
COMPONENT_ARCHIVE_URL=	ftp://ftp.mrunix.net/pub/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/webalizer

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D)); (cd $(SOURCE_DIR); $(GSED) -i -e 's/u_int64_t/uint64_t/g' *.c *.h configure.in configure)

# Adjust the log file pathname in the sample configuration file.
COMPONENT_PRE_BUILD_ACTION += \
	$(GSED) -i -e 's?lib/httpd/logs/?apache2/2.2/logs/?' \
		$(SOURCE_DIR)/sample.conf

CFLAGS += -I/usr/gnu/include
LDFLAGS += -L$(GNULIB) -L$(GNULIB64)

CONFIGURE_OPTIONS +=	--enable-dns
CONFIGURE_OPTIONS +=	--enable-bz2
CONFIGURE_OPTIONS +=	--with-gd=/usr/include/gd2
CONFIGURE_OPTIONS +=	--sysconfdir=$(ETCDIR)

# Needed to correctly build that 64-bit library.
LDFLAGS += $(CC_BITS)

# common targets
build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include ../../make-rules/depend.mk
