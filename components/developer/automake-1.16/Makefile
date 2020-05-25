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
# Copyright (c) 2012, Oracle and/or its affiliates. All rights reserved.
# Modified by Aurelien Larcher, 2015-2020.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		automake
COMPONENT_MAJOR_VERSION=1.16
COMPONENT_VERSION=	$(COMPONENT_MAJOR_VERSION).2
COMPONENT_FMRI=		developer/build/automake-116
COMPONENT_CLASSIFICATION=Development/GNU
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
  sha256:b2f361094b410b4acbf4efba7337bdb786335ca09eb2518635a09fb7319ca5c1
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/pub/gnu/automake/$(COMPONENT_ARCHIVE)
COMPONENT_SUMMARY=	A Makefile generator
COMPONENT_PROJECT_URL=  http://www.gnu.org/software/automake/ 
COMPONENT_LICENSE=	GPLv2 FDLv1.3

include $(WS_MAKE_RULES)/common.mk

PKG_MACROS+= COMPONENT_MAJOR_VERSION=$(COMPONENT_MAJOR_VERSION)

#CONFIGURE_OPTIONS  +=	--program-transform-name=s/$$/-$(COMPONENT_MAJOR_VERSION)/
CONFIGURE_OPTIONS  +=	--docdir=$(CONFIGURE_PREFIX)/share/doc/$(COMPONENT_NAME)-$(COMPONENT_MAJOR_VERSION)
CONFIGURE_OPTIONS  +=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS  +=	PERL="$(PERL)"

COMPONENT_TEST_ENV += -i PATH=$(GCC_BINDIR):$(PATH.gnu)

COMPONENT_TEST_TRANSFORMS += \
        '-n ' \
        '-e "/TOTAL:/p" ' \
        '-e "/SKIP:/p" ' \
        '-e "/PASS:/p" ' \
        '-e "/FAIL:/p" ' \
        '-e "/ERROR:/p" '

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += SUNWcs
