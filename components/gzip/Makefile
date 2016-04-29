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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		gzip
COMPONENT_VERSION=	1.8
COMPONENT_ARCHIVE_HASH=	\
    sha256:1ff7aedb3d66a0d73f442f6261e4b3860df6fd6c94025c2cb31a202c9c60fe0e

TPNO=			28039

INSTALL_TARGET=
SYSTEM_TEST_TARGET= configure $(SYSTEM_TEST_64)
include $(WS_MAKE_RULES)/gnu-component.mk

# Prevent gzip assembly code usage; which segv's with Studio 12.3 and 12.4.
CONFIGURE_OPTIONS +=	gzip_cv_assembler=no
CONFIGURE_OPTIONS +=	--infodir=$(CONFIGURE_INFODIR)

# Needed for "gmake test" to work successfully.
# If SHELLOPTS is exported (as it is by the userland makefiles),
# then all shell options get exported to child invocations of bash,
# which results in test failures due to nounset and xtrace being
# set unexpectedly, and errors such as "$1: unbound variable" and
# diffs failing due to script tracing in output files.
unexport SHELLOPTS

COMPONENT_PREP_ACTION = (cd $(SOURCE_DIR); $(AUTORECONF) -if)

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
GZGREP_MAN_VARIANTS+=$(PROTOUSRSHAREMAN1DIR)/gzegrep.1
GZGREP_MAN_VARIANTS+=$(PROTOUSRSHAREMAN1DIR)/gzfgrep.1

$(GZGREP_MAN_VARIANTS):
	$(RM) $@; echo ".so man1/gzgrep.1" > $@

# Get the binaries to test from the component build area.
COMPONENT_TEST_ENV +=	PATH=$(BUILD_DIR_$(BITS)):/usr/xpg4/bin:$(USRBINDIR)

# Use the installed gzip binary from /usr/bin.
COMPONENT_SYSTEM_TEST_ENV +=	PATH=/usr/xpg4/bin:$(USRBINDIR)

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" '

install:      $(INSTALL_64) $(GZGREP_MAN_VARIANTS)

REQUIRED_PACKAGES += runtime/python-27
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/xopen/xcu4
