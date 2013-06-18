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
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		webalizer
COMPONENT_VERSION=	2.21.2
HUMAN_VERSION=		2.21-02
COMPONENT_PROJECT_URL=	http://www.mrunix.net/webalizer/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC)-src.tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:f2663d67f5820644a0b1c0b7dee4a5c764d829166fa28d5880442c28886729d9
COMPONENT_ARCHIVE_URL=	ftp://ftp.mrunix.net/pub/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/webalizer

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

COMPONENT_PRE_CONFIGURE_ACTION = \
	($(CLONEY) $(SOURCE_DIR) $(@D))

# Adjust the log file pathname in the sample configuration file.
COMPONENT_PRE_BUILD_ACTION += \
	$(GSED) -i -e 's?lib/httpd/logs/?apache2/2.2/logs/?' \
		$(SOURCE_DIR)/sample.conf

COMPILER =	gcc

CONFIGURE_OPTIONS +=	--enable-dns
CONFIGURE_OPTIONS +=	--with-gd=/usr/include/gd2
CONFIGURE_OPTIONS +=	CFLAGS="$(CFLAGS)"
CONFIGURE_OPTIONS +=	LDFLAGS="$(LDFLAGS)"

# webalizer is defining u_int64_t but also uses db.h
# which typedefs it, and parfait isn't happy.
# gcc4 may not be as well.
ifeq   ($(strip $(PARFAIT_BUILD)),yes)
CC += -Du_int64_t=uint64_t
CONFIGURE_OPTIONS +=	c_cv_type_u_int64_t=yes
endif

# Needed to correctly build that 64-bit library.
LDFLAGS += $(CC_BITS)

# common targets
build:          $(BUILD_64)

install:        $(INSTALL_64)

test:           $(NO_TESTS)

BUILD_PKG_DEPENDENCIES =        $(BUILD_TOOLS)

include ../../make-rules/depend.mk
