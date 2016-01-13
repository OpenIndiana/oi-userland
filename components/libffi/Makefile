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
# Copyright (c) 2015, 2016, Oracle and/or its affiliates. All rights reserved.
#

COMPILER =	gcc

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libffi
COMPONENT_VERSION=	3.0.9
COMPONENT_PROJECT_URL=	http://sourceware.org/libffi/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= \
    sha256:589d25152318bc780cd8919b14670793f4971d9838dab46ed38c32b3ee92c452
COMPONENT_ARCHIVE_URL=	ftp://sources.redhat.com/pub/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libffi

TPNO=		5930

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

CC +=		$(CC_BITS)

CFLAGS += -DFFI_MMAP_EXEC_WRIT=1

CONFIGURE_OPTIONS += --enable-raw-api=no
CONFIGURE_ENV +=	CFLAGS="$(CFLAGS)"

ASLR_MODE = $(ASLR_ENABLE)

configure:	$(CONFIGURE_32_and_64)

build:          $(BUILD_32_and_64)

install:        $(INSTALL_32_and_64)

test:           $(NO_TESTS)

system-test:    $(NO_TESTS)

REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
