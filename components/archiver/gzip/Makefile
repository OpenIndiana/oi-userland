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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2018, Michal Nowak
#

USE_DEFAULT_TEST_TRANSFORMS= yes
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		gzip
COMPONENT_VERSION=	1.13
COMPONENT_SUMMARY=	The GNU Zip (gzip) compression utility
COMPONENT_PROJECT_URL=	https://www.gnu.org/software/gzip/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_URL=	https://ftp.gnu.org/gnu/gzip/$(COMPONENT_ARCHIVE)
COMPONENT_ARCHIVE_HASH= sha256:7454eb6935db17c6655576c2e1b0fabefd38b4d0936e0f87f48cd062ce91a057
COMPONENT_FMRI=		compress/gzip
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_LICENSE=	GPLv3, FDLv1.3

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cd $(SOURCE_DIR); $(AUTORECONF) -if )

# Fix references to Solaris renamed programs (z*->gz*) in man pages, info
# pages and in wrapper scripts.
COMPONENT_PRE_INSTALL_ACTION = \
	(cd $(COMPONENT_SRC) ; \
	 for file in `ls *.1 doc/*.info z*.in` ; do \
		mv $$file $$file.tmp ; \
		$(GSED) -f $(COMPONENT_DIR)/renaming.sed $$file.tmp > $$file ; \
		$(RM) $$file.tmp ; \
	 done)

# Rename installed programs and man pages in proto dir (z*->gz*).
COMPONENT_POST_INSTALL_ACTION = \
	(for dir in $(PROTOUSRBINDIR) $(PROTOUSRSHAREMAN1DIR) ; do \
		cd $$dir; \
	 	for zfile in `ls z*`; do \
			mv $$zfile g$$zfile ; \
		done ; \
	 done)

# Provide missing man pages.
GZGREP_MAN_VARIANTS += $(PROTOUSRSHAREMAN1DIR)/gzegrep.1
GZGREP_MAN_VARIANTS += $(PROTOUSRSHAREMAN1DIR)/gzfgrep.1

$(GZGREP_MAN_VARIANTS):
	$(RM) $@; echo ".so man1/gzgrep.1" > $@

ASLR_MODE = $(ASLR_ENABLE)

install:	$(INSTALL_64) $(GZGREP_MAN_VARIANTS)

# Note that the tests need to be run without extra privileges otherwise some tests may fail or skipped.
#
# If SHELLOPTS is exported (as it is by the userland makefiles),
# then all shell options get exported to child invocations of bash,
# which results in test failures due to nounset and xtrace being
# set unexpectedly, and errors such as "$1: unbound variable" and
# diffs failing due to script tracing in output files.
unexport SHELLOPTS

# Get the binaries to test from the component build area.
COMPONENT_TEST_ENV += PATH=$(BUILD_DIR_$(BITS)):$(PATH.gnu)
COMPONENT_TEST_TARGETS = check

# Auto-generated dependencies
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
