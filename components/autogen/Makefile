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
# Copyright (c) 2011, 2013, Oracle and/or its affiliates. All rights reserved.
#
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		autogen
COMPONENT_VERSION=	5.16.2
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/autogen/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:aa51f5adbf49c2cb48a7d6de3dbab15b89e0a04e7152195fe6fb3380e05c4991
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/autogen/rel$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/autogen

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

# build target is incorrect without this 
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

# built in SFW with gcc and builds cleanly now only with gcc
COMPILER = gcc

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

CONFIGURE_ENV.64 += PATH=/usr/bin/$(MACH64):/usr/bin

# Enable ASLR for this component
ASLR_MODE = $(ASLR_ENABLE)

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(TEST_32_and_64)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
