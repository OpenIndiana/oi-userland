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
# Copyright (c) 2011, 2015, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2019, Michal Nowak
#

BUILD_BITS= 64_and_32
USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gettext
COMPONENT_VERSION=	0.22
COMPONENT_SUMMARY=	GNU gettext - message handling utilities
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/gettext/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	sha256:0e60393a47061567b46875b249b7d2788b092d6457d656145bb0e7e6a3e26d93
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/pub/gnu/gettext/$(COMPONENT_ARCHIVE)
COMPONENT_FMRI=		text/gnu-gettext
COMPONENT_CLASSIFICATION=	Development/GNU
COMPONENT_LICENSE=	GPLv3
COMPONENT_LICENSE_FILE=	COPYING

include $(WS_MAKE_RULES)/common.mk

CONFIGURE_OPTIONS += --disable-java
CONFIGURE_OPTIONS += --disable-libasprintf
CONFIGURE_OPTIONS += --disable-openmp
CONFIGURE_OPTIONS += --disable-static
CONFIGURE_OPTIONS += --without-emacs

# Drop 32-bit binaries
COMPONENT_POST_INSTALL_ACTION.32 += $(RM) -r $(PROTOUSRBINDIR32) $(PROTOUSRLIBDIR32)/gettext ;
# Some files clash with those provided by illumos so move them to usr/gnu
COMPONENT_POST_INSTALL_ACTION.32 += \
	for f in gettext msgfmt xgettext ; do \
		$(RM) $(PROTOUSRSHAREMAN1DIR)/$$f.1 ; \
	done ;
COMPONENT_POST_INSTALL_ACTION.64 += \
	$(MKDIR) $(PROTOGNUBIN) $(PROTOGNUSHAREMAN1) ; \
	for f in gettext msgfmt xgettext ; do \
		$(MV) $(PROTOUSRBINDIR)/$$f $(PROTOGNUBIN) ; \
		$(MV) $(PROTOUSRSHAREMAN1DIR)/$$f.1 $(PROTOGNUSHAREMAN1) ; \
	done ;

# Tests should run in a clean environment
COMPONENT_TEST_ENV= -i PATH=${PATH}

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/=========/p" ' \
	'-e "/Testsuite summary for/p" '


# Manually added dependencies
REQUIRED_PACKAGES += library/libcroco
# for tests
TEST_REQUIRED_PACKAGES += library/guile
TEST_REQUIRED_PACKAGES += runtime/clisp
TEST_REQUIRED_PACKAGES += runtime/tcl-8

# Auto-generated dependencies
REQUIRED_PACKAGES += library/libunistring
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += library/ncurses
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
