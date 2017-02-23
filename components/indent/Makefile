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
# Copyright (c) 2013, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		indent
COMPONENT_VERSION=	2.2.10
COMPONENT_ARCHIVE_HASH=	\
    sha256:8a9b41be5bfcab5d8c1be74204b10ae78789fc3deabea0775fdced8677292639
COMPONENT_BUGDB=	utility/gnu-indent
COMPONENT_ANITYA_ID=	1378

TPNO=			28115

TEST_TARGET= install $(TEST_64)
SYSTEM_TEST_TARGET= configure $(SYSTEM_TEST_64)
include $(WS_MAKE_RULES)/gnu-component.mk

# Needed to get "gmake test" working.
COMPONENT_PRE_CONFIGURE_ACTION =	($(CLONEY) $(SOURCE_DIR) $(@D))

CONFIGURE_OPTIONS +=	--infodir=$(CONFIGURE_INFODIR)

# Previous versions of indent included a pre-made indent.1 man page that
# was then easy to patch. Now we need to forceably create indent.1 from
# indent.1.in. We also need to copy ../doc/version.texi into the man
# directory in the build area so that it's correctly included when
# texinfo2man processes the indent.texinfo file.
COMPONENT_POST_BUILD_ACTION = \
	$(CP) $(SOURCE_DIR)/doc/version.texi $(BUILD_DIR_$(BITS))/man/ ; \
	cd $(BUILD_DIR_$(BITS))/man ; $(GMAKE) -B indent.1

COMPONENT_TEST_TRANSFORMS += \
	'-e "s|^make.*: Leaving directory.*$$|XXX_CC_XXX|g" ' \
	'-e "s|^make.*: Entering directory.*$$|XXX_CC_XXX|g" ' \
	'-e "/^XXX_CC_XXX$$/d" '

COMPONENT_TEST_DIR =		$(@D)/regression
# Need to put /usr/gnu/bin at the front of $PATH for GNU diff.
COMPONENT_TEST_CMD =		./TEST
COMPONENT_TEST_ENV +=		PATH=$(GNUBIN):$(USRBINDIR)
COMPONENT_TEST_TARGETS =

COMPONENT_SYSTEM_TEST_DIR =	$(@D)/regression
COMPONENT_SYSTEM_TEST_CMD =	./TEST
# Need to put /usr/gnu/bin at the front of $PATH for GNU diff.
COMPONENT_SYSTEM_TEST_ENV +=	PATH=$(GNUBIN):$(USRBINDIR)
COMPONENT_SYSTEM_TEST_ENV +=	INDENT_BIN=$(USRBINDIR)/indent
COMPONENT_SYSTEM_TEST_TARGETS =
