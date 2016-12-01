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
# Copyright (c) 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS = 64
include ../../make-rules/shared-macros.mk

COMPONENT_NAME =	jq
COMPONENT_VERSION =	1.5
COMPONENT_PROJECT_URL =	https://github.com/stedolan/jq
COMPONENT_ARCHIVE_HASH =	\
    sha256:c4d2bfec6436341113419debf479d833692cc5cdab7eb0326b5a4d4fbe9f493c
COMPONENT_ARCHIVE_URL =	$(COMPONENT_PROJECT_URL)/releases/download/$(COMPONENT_NAME)-$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB =	utility/jq

TPNO =			27148

include $(WS_MAKE_RULES)/common.mk

COMPILER =		gcc

# noexbss causes onig.test to fail
LD_MAP_NOEXBSS.sparc =

# delete all this when build servers are installed with oniguruma
ONIG_PROTO =		$(WS_COMPONENTS)/oniguruma/build/prototype/$(MACH)
ONIG_LIBDIR =		$(ONIG_PROTO)$(USRLIBDIR64)
ONIG_INCDIR =		$(ONIG_PROTO)$(USRINCDIR)
CONFIGURE_ENV +=	CPPFLAGS="$(CPPFLAGS) -I$(ONIG_INCDIR)"
CONFIGURE_ENV +=	LDFLAGS="$(LDFLAGS) -L$(ONIG_LIBDIR)"
CONFIGURE_OPTIONS +=	--with-oniguruma=$(ONIG_PROTO)$(USRDIR)

# couldn't convince autotools to not include the proto runpath
COMPONENT_POST_INSTALL_ACTION += \
	( /usr/bin/elfedit -e 'dyn:delete RPATH' -e 'dyn:delete RUNPATH' \
		"$(PROTOUSRBINDIR)/jq" )

ONIG_MANIFEST =		manifest-$(MACH)-oniguruma.depend
DEPENDED +=		$(WS_COMPONENTS)/oniguruma/build/$(ONIG_MANIFEST)
PKG_PROTO_DIRS +=	$(WS_COMPONENTS)/oniguruma

COMPONENT_TEST_ENV +=	JQ="$(PROTOUSRBINDIR)/jq"
COMPONENT_TEST_ENV +=	LD_LIBRARY_PATH_64="$(ONIG_LIBDIR)"
COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/TOTAL/p" ' \
	'-e "/SKIP/p" ' \
	'-e "/PASS/p" ' \
	'-e "/XPASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/XFAIL/p" ' \
	'-e "/ERROR/p" '

# need proto to run tests
test: install

REQUIRED_PACKAGES +=	library/oniguruma
REQUIRED_PACKAGES +=	system/library
REQUIRED_PACKAGES +=	system/library/math
