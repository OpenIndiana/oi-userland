#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# Copyright 2024 Marcel Telka
#

BUILD_STYLE=justmake
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=			unifdef
COMPONENT_VERSION=		2.12
COMPONENT_SUMMARY=		Remove preprocessor conditionals from code
COMPONENT_PROJECT_URL=		https://dotat.at/prog/unifdef/
COMPONENT_FMRI=			developer/unifdef
COMPONENT_CLASSIFICATION=	Development/C
COMPONENT_SRC=			$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=		$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=		$(COMPONENT_PROJECT_URL)$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=		sha256:43ce0f02ecdcdc723b2475575563ddb192e988c886d368260bc0a63aee3ac400
COMPONENT_LICENSE=		BSD-3-Clause
COMPONENT_LICENSE_FILE=		COPYING

#TEST_TARGET=$(NO_TESTS) # if no testsuite enabled
include $(WS_MAKE_RULES)/common.mk

# GNU diff is needed to run tests
PATH = $(PATH.gnu)

# Replace cc with full path to out compiler (gcc)
COMPONENT_POST_UNPACK_ACTION += $(GSED) -i -e 's|cc|$(CC)|' $(COMPONENT_SRC)/unifdefall.sh ;

# Install to /usr/gnu so we do not clash with illumos unifdef
COMPONENT_INSTALL_ARGS += prefix=$(GNUDIR)

# Use non-default test target
COMPONENT_TEST_TARGETS = test

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
