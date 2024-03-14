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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

BUILD_BITS= 64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=         autoconf
COMPONENT_VERSION=      2.72
COMPONENT_SUMMARY=      GNU autoconf utility
COMPONENT_PROJECT_URL=  https://www.gnu.org/software/autoconf/
COMPONENT_SRC=          $(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=      $(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH= sha256:afb181a76e1ee72832f6581c0eddf8df032b83e2e0239ef79ebedc4467d92d6e
COMPONENT_ARCHIVE_URL=  https://ftp.gnu.org/gnu/autoconf/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=         developer/build/autoconf
COMPONENT_CLASSIFICATION=Development/GNU
COMPONENT_LICENSE=      GPLv2, GPLv3, autoconf exception

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PRE_CONFIGURE_ACTION= ( $(CLONEY) $(SOURCE_DIR) $(@D) )

CONFIGURE_OPTIONS += --srcdir=.
CONFIGURE_OPTIONS += --infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS += PERL="$(PERL)"

COMPONENT_TEST_TRANSFORMS += \
	' -n ' \
	' -e "/ok/p" ' \
	' -e "/skipped/p" ' \
	' -e "/expected/p" ' \
	' -e "/results/p" ' \
	' -e "/^autoreconf/p" ' \
	' -e "/^C low level/p" ' \
	' -e "/^Erlang/p" ' \
	' -e "/^Fortran/p" ' \
	' -e "/^Go /p" ' \
	' -e "/^Low level /p" ' \
	' -e "/^Testing/p" ' \
	' -e "/^Compatibility/p" ' \
	' -e "/^Autoconf/p" ' \
	' -e "/^Autoscan/p" ' \
	' -e "/^Autotest/p" ' \
	' -e "/^Executables/p" ' \
	' -e "/^M4sh/p" ' \
	' -e "/^M4sugar/p" ' \
	' -e "/^Semantics/p" ' \
	' -e "/----/p" '

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += developer/macro/gnu-m4
