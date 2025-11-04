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

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         npth
COMPONENT_VERSION=      1.8
COMPONENT_SUMMARY=      The New GNU Portable Threads Library
COMPONENT_DESCRIPTION=	A portable library that uses the system's standard threads library to provid non-preemptive priority-based scheduling for multiple threads using the npth API
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=  https://www.gnupg.org/related_software/npth/
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH= sha256:8bd24b4f23a3065d6e5b26e98aba9ce783ea4fd781069c1b35d149694e90ca3e
COMPONENT_ARCHIVE_URL=  https://gnupg.org/ftp/gcrypt/npth/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         library/npth
COMPONENT_CLASSIFICATION=System/Libraries
COMPONENT_LICENSE=		LGPLv2.1
COMPONENT_LICENSE_FILE=	COPYING.LIB

include $(WS_MAKE_RULES)/common.mk

# Enable C99 mode + -Xc for its additional warnings.
CFLAGS += -std=gnu99
CFLAGS += $(XPG6MODE)
CFLAGS += -fPIC

CPPFLAGS += $(CPP_LARGEFILES)

LDFLAGS= -lpthread -lposix4 -lrt

CONFIGURE_OPTIONS += --localstatedir=$(VARDIR)
CONFIGURE_OPTIONS += --with-pic

CONFIGURE_ENV += LD="$(CC) $(CFLAGS) $(LDFLAGS)"
CONFIGURE_ENV += CPP="$(CC) $(CPPFLAGS) $(CFLAGS) -E"
CONFIGURE_ENV += INSTALL="$(INSTALL)"

# Auto-generated dependencies
REQUIRED_PACKAGES += system/library
