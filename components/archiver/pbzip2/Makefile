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
# Copyright (c) 2013, 2016, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2016, Jim Klimov
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		pbzip2
COMPONENT_VERSION=	1.1.13
COMPONENT_REVISION=	1
COMPONENT_PROJECT_URL=	http://compression.ca/pbzip2/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:8fd13eaaa266f7ee91f85c1ea97c86d9c9cc985969db9059cdebcb1e1b7bdbe6
COMPONENT_ARCHIVE_URL=	https://launchpad.net/pbzip2/1.1/$(COMPONENT_VERSION)/+download/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/pbzip2

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

#ASLR_MODE = $(ASLR_ENABLE)

# Trailing flags are those our CXXFLAGS override in original project Makefile
CXXFLAGS += $(CPP_LARGEFILES) -DUSE_STACKSIZE_CUSTOMIZATION -pthread -D_POSIX_PTHREAD_SEMANTICS

COMPONENT_POST_INSTALL_ACTION = \
	( $(MKDIR) $(PROTOUSRBINDIR)/$(MACH$(BITS)) && \
	  $(MV) $(PROTOUSRBINDIR)/pbzip2 $(PROTOUSRBINDIR)/$(MACH$(BITS))/pbzip2 )

COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_ARGS += CXX="$(CXX)"
COMPONENT_BUILD_ARGS += CXXFLAGS="$(CXXFLAGS)"

# common targets
build:		$(BUILD_32_and_64)

install:	$(INSTALL_32_and_64)

test:		$(NO_TESTS)

REQUIRED_PACKAGES += compress/bzip2
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/g++-6-runtime
REQUIRED_PACKAGES += $(GCC_RUNTIME_PKG)
REQUIRED_PACKAGES += system/library/math
