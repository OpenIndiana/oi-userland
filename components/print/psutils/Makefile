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
# Copyright (c) 2019 Nona Hansel
#

BUILD_STYLE= justmake

include ../../../make-rules/shared-macros.mk
include $(WS_MAKE_RULES)/shared-targets.mk

COMPONENT_NAME=		psutils
# At the homepage it is stated that development version is pre-2.0
COMPONENT_VERSION= 1.17
HUMAN_VERSION= p17
COMPONENT_REVISION=	4
COMPONENT_SUMMARY=	Collection of utilities for manipulating PostScript documents
COMPONENT_PROJECT_URL= http://knackered.knackered.org/angus/psutils/
COMPONENT_SRC= $(COMPONENT_NAME)
COMPONENT_ARCHIVE= $(COMPONENT_NAME)-$(HUMAN_VERSION).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:3853eb79584ba8fbe27a815425b65a9f7f15b258e0d43a05a856bdb75d588ae4
COMPONENT_ARCHIVE_URL= http://knackered.knackered.org/angus/download/psutils/$(COMPONENT_ARCHIVE)
COMPONENT_CLASSIFICATION=	System/Printing
COMPONENT_FMRI=	print/psutils
COMPONENT_LICENSE=	psutils
COMPONENT_LICENSE_FILE=	LICENSE

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

# to stay compatible with nevada settings, letter is default paper size
CFLAGS += -DPAPER=\\\"letter\\\" -DUNIX

COMPONENT_BUILD_ENV += CCFLAGS="$(LDFLAGS)"
COMPONENT_BUILD_ENV += INCLUDEDIR=$(PROTO_DIR)/usr/share/psutils
# We need to point to some Perl otherwise build is unable to find one.  Since
# psutils does not depend on any particular Perl version we use generic
# unversioned Perl.
COMPONENT_BUILD_ENV += PERL=/usr/bin/perl

# slightly hacky, since COMPONENT_BUILD_TARGETS are just arguments passed to
# make
COMPONENT_BUILD_ARGS= -e -f Makefile.unix

COMPONENT_INSTALL_ENV += BINDIR=$(PROTO_DIR)/usr/bin
COMPONENT_INSTALL_ENV += INCLUDEDIR=$(PROTO_DIR)/usr/share/psutils
COMPONENT_INSTALL_ENV += MANDIR=$(PROTO_DIR)/usr/share/man/man1
COMPONENT_INSTALL_ENV += INSTALL="$(INSTALL) -m 0555"
COMPONENT_INSTALL_ENV += INSTALLMAN="$(INSTALL) -m 0444"

# slightly hacky, since COMPONENT_BUILD_TARGETS are just arguments passed to
# make
COMPONENT_INSTALL_ARGS= -e -f Makefile.unix

$(INSTALL_$(MK_BITS)):	$(PROTOUSRSHAREMAN1DIR) $(PROTOUSRBINDIR)

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
