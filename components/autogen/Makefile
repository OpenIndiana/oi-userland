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
# Normally, 64-bit binaries are preferred over 32-bit ones, but we prefer
# 32-bit for this component to keep the historical defaults used by autogen for
# 32-bit and 64-bit.
BUILD_BITS= 32_and_64
# built in SFW with gcc and builds cleanly now only with gcc
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		autogen
COMPONENT_VERSION=	5.16.2
COMPONENT_ARCHIVE_HASH=	\
    sha256:aa51f5adbf49c2cb48a7d6de3dbab15b89e0a04e7152195fe6fb3380e05c4991
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/autogen/rel$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

TPNO=			11805

# Tests need to be built.
SYSTEM_TEST_TARGET= build $(SYSTEM_TEST_32_and_64)
include $(WS_MAKE_RULES)/gnu-component.mk

# build target is incorrect without this 
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

# strip the environment or install target fails
ENV +=	-i

# Replace all occurrences of "echo" with "/usr/gnu/bin/echo" in the two
# scripts used by autogen that munge the man and mdoc output. This prevents
# bogus conversions (like "\f" -> Control-L) happening.
# Adjust "tr" to "/usr/gnu/bin/tr" in the autoopts vendor.test.
# These changes now allow the autoopts tests to successfully complete.
COMPONENT_POST_UNPACK_ACTION = \
	$(GSED) -i -e 's|echo|/usr/gnu/bin/echo|' \
		$(SOURCE_DIR)/autoopts/tpl/mdoc2man.sh ; \
	$(GSED) -i -e 's|echo|/usr/gnu/bin/echo|' \
		$(SOURCE_DIR)/autoopts/tpl/texi2mdoc.sh ; \
	$(GSED) -i -e 's| tr | /usr/gnu/bin/tr |' \
		$(SOURCE_DIR)/autoopts/test/vendor.test

# Master test results are the same for both 32-bit and 64-bit, so override
# here, rather than create multiple identical master files.
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/SKIP/p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/passed/p" '

COMPONENT_SYSTEM_TEST_ENV +=	CLexe=$(USRBINDIR)/columns
COMPONENT_SYSTEM_TEST_ENV +=	GDexe=$(USRBINDIR)/getdefs
COMPONENT_SYSTEM_TEST_ENV +=	AGexe=$(USRBINDIR)/autogen

REQUIRED_PACKAGES += library/gmp
REQUIRED_PACKAGES += library/guile
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library/gcc/gcc-c-runtime
REQUIRED_PACKAGES += system/library/math
