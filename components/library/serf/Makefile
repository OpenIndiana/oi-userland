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
# Copyright (c) 2016, 2017, Oracle and/or its affiliates. All rights reserved.
#
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		serf
COMPONENT_VERSION=	1.3.9
COMPONENT_REVISION=	2
COMPONENT_SUMMARY=	high performance C-based HTTP client library
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_PROJECT_URL=	http://serf.apache.org/
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:549c2d21c577a8a9c0450facb5cca809f26591f048e466552240947bdf7a87cc
COMPONENT_ARCHIVE_URL=	https://www.apache.org/dist/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_ANITYA_ID=	1720
COMPONENT_FMRI=	library/libserf
COMPONENT_DESCRIPTION= The serf library is a high performance C-based HTTP client library. \
It is built upon the Apache Portable Runtime (APR) library.  Features include multiplexed, \
asynchronous connections; SSL/TLS support; full HTTP pipelining; multiple authentication \
modes (Basic, Digest, Kerberos/NTLM); zero-copy support for increased throughput.
COMPONENT_CLASSIFICATION=Web Services/Application and Web Servers
COMPONENT_LICENSE= 	Apache v2.0

include $(WS_MAKE_RULES)/prep.mk
# Needed by the test: target. We override build and install.
include $(WS_MAKE_RULES)/justmake.mk
include $(WS_MAKE_RULES)/ips.mk

USED_APR =		/usr/apr
USED_APU =		/usr/apr-util

APR_32 =		$(USED_APR)/bin/apr-1-config
APR_64 =		$(USED_APR)/bin/$(MACH64)/apr-1-config
APU_32 =		$(USED_APU)/bin/apu-1-config
APU_64 =		$(USED_APU)/bin/$(MACH64)/apu-1-config
SERFLIBPATH_32 =	-R$(USED_APR)/lib -R$(USED_APU)/lib
SERFLIBPATH_64 =	-R$(USED_APR)/lib/64 -R$(USED_APU)/lib/64
SERFLIBDIR_32 =		/usr/lib
SERFLIBDIR_64 =		/usr/lib/64

# We have to roll our own as serf is built with scons.
SCONS =			/usr/bin/scons
COMPONENT_BUILD_ARGS += CC="$(CC)"
COMPONENT_BUILD_ARGS +=	CPPFLAGS=-D__EXTENSIONS__
COMPONENT_BUILD_ARGS +=	CFLAGS="$(CC_BITS) $(COMPILER_PIC)"
COMPONENT_BUILD_ARGS +=	LINKFLAGS="$(CC_BITS) $(SERFLIBPATH_$(BITS))"
COMPONENT_BUILD_ARGS += APR=$(APR_$(BITS))
COMPONENT_BUILD_ARGS += APU=$(APU_$(BITS))
COMPONENT_BUILD_ARGS += PREFIX=/usr
COMPONENT_BUILD_ARGS += LIBDIR=$(SERFLIBDIR_$(BITS))

COMPONENT_TEST_CMD =	$(SCONS)
COMPONENT_TEST_MASTER =	$(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += '-ne "/error/s/^[0-9]\+//p"'
COMPONENT_TEST_TRANSFORMS += '-ne "/failure/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^[0-9]\+)/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^Runs:/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^ERRROR:/p" '
COMPONENT_TEST_TRANSFORMS += '-ne "/^==/p" '

$(BUILD_DIR)/%/.built:  $(SOURCE_DIR)/.prep
	$(RM) -r $(@D) ; $(MKDIR) $(@D)
	$(CLONEY) $(SOURCE_DIR) $(@D)
	(cd $(@D) ; $(SCONS) $(COMPONENT_BUILD_ARGS))
	$(TOUCH) $@

configure:	$(CONFIGURE_32_and_64)

build:		$(BUILD_32_and_64)

# As there aren't many files, just get them out of the build directory.
install:	build

test:		$(TEST_32_and_64)

# Build dependencies
REQUIRED_PACKAGES += developer/build/scons

# Auto-generated dependencies
REQUIRED_PACKAGES += library/apr
REQUIRED_PACKAGES += library/apr-util
REQUIRED_PACKAGES += library/expat
REQUIRED_PACKAGES += library/openldap
REQUIRED_PACKAGES += library/security/openssl
REQUIRED_PACKAGES += library/zlib
REQUIRED_PACKAGES += system/library
REQUIRED_PACKAGES += system/library/math
