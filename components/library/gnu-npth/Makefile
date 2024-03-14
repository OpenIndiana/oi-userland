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
# Copyright (c) 2018, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
#

BUILD_BITS= 32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         npth
COMPONENT_VERSION=      1.6
COMPONENT_REVISION=     2
COMPONENT_SUMMARY=      The New GNU Portable Threads Library
COMPONENT_DESCRIPTION=	A portable library that uses the system's standard threads library to provid non-preemptive priority-based scheduling for multiple threads using the npth API
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://www.gnupg.org/related_software/npth/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:1393abd9adcf0762d34798dc34fdcf4d0d22a8410721e76f1e3afcd1daa4e2d1
COMPONENT_ARCHIVE_URL=  https://ftp.gnupg.org/gcrypt/npth/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/npth
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=		LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING.LIB

include $(WS_MAKE_RULES)/common.mk

# Enable C99 mode + -Xc for its additional warnings.
CFLAGS += -std=gnu99

# -xbuiltin=%none -- builtins have been known to be buggy
CFLAGS += -fno-builtin

CFLAGS += -D_XPG6
CFLAGS += $(CPP_POSIX)
CFLAGS += -fPIC

CPPFLAGS += $(CPP_LARGEFILES) $(CPP_POSIX)

LDFLAGS=	-lpthread -lposix4 -lrt

CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)
CONFIGURE_OPTIONS += --with-pic

CONFIGURE_ENV += LD="$(CC) $(CFLAGS) $(LDFLAGS)"
CONFIGURE_ENV += CPP="$(CC) $(CPPFLAGS) $(CFLAGS) -E"
CONFIGURE_ENV += INSTALL="$(INSTALL)"

COMPONENT_TEST_TRANSFORMS += '-e "s|\(^Pth:\).*|\1|" '

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
