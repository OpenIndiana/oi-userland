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
include ../../make-rules/shared-targets.mk

COMPONENT_NAME=		psutils
COMPONENT_VERSION=	p17
COMPONENT_PROJECT_URL=	http://knackered.knackered.org/angus/psutils/
COMPONENT_SRC=		$(COMPONENT_NAME)
COMPONENT_ARCHIVE=	$(COMPONENT_NAME)-$(COMPONENT_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:3853eb79584ba8fbe27a815425b65a9f7f15b258e0d43a05a856bdb75d588ae4
COMPONENT_ARCHIVE_URL= http://gd.tuwien.ac.at/publishing/tex/tex-utils/psutils/$(COMPONENT_ARCHIVE)
#COMPONENT_ARCHIVE_URL= ftp://ftp.knackered.org/pub/psutils/psutils.tar.gz
# Official ftp sources are currently unavailable, so I'm using mirror I found.
# I made sure that the tarball is equal to the one present in SFW

include ../../make-rules/prep.mk
include ../../make-rules/justmake.mk
include ../../make-rules/ips.mk

# Can't use 'p17' since that is not accepted by pkg. And homepage
# http://knackered.knackered.org/angus/psutils/ states that development version
# is pre-2.0
IPS_COMPONENT_VERSION=1.17

# to stay compatible with nevada settings, letter is default paper size
CFLAGS += -DPAPER=\\\"letter\\\" -DUNIX

COMPONENT_BUILD_ENV += CC=$(CC)
COMPONENT_BUILD_ENV += CFLAGS="$(CFLAGS)"
COMPONENT_BUILD_ENV += INCLUDEDIR=$(PROTO_DIR)/usr/share/psutils
COMPONENT_BUILD_ENV += PERL=$(PERL)

# slightly hacky, since COMPONENT_BUILD_TARGETS are just arguments passed to
# make
COMPONENT_BUILD_ARGS = -e -f Makefile.unix

COMPONENT_INSTALL_ENV += BINDIR=$(PROTO_DIR)/usr/bin
COMPONENT_INSTALL_ENV += INCLUDEDIR=$(PROTO_DIR)/usr/share/psutils
COMPONENT_INSTALL_ENV += MANDIR=$(PROTO_DIR)/usr/share/man/man1
COMPONENT_INSTALL_ENV += PERL=$(PERL)
COMPONENT_INSTALL_ENV += INSTALL="$(INSTALL) -m 0555"
COMPONENT_INSTALL_ENV += INSTALLMAN="$(INSTALL) -m 0444"

# slightly hacky, since COMPONENT_BUILD_TARGETS are just arguments passed to
# make
COMPONENT_INSTALL_ARGS = -e -f Makefile.unix

build:		$(BUILD_32)

install:	$(INSTALL_32)

$(INSTALL_32):	$(PROTOUSRSHAREMAN1DIR) $(PROTOUSRBIN)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
