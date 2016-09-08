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

COMPONENT_NAME=		gawk
COMPONENT_VERSION=	4.1.3
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:e3cf55e91e31ea2845f8338bedd91e40671fc30e4d82ea147d220e687abda625

# Adjust references to section 3am to be section 3 in the extensions man pages.
COMPONENT_POST_CONFIGURE_ACTION = \
	(cd $(SOURCE_DIR)/extension ; \
	mlist=`/usr/bin/find . -name '*.3am'` ; \
	for f in $$mlist ; do \
		$(GSED) -i -e 's|3am|3|g' $$f ; \
	done)

# The additional gawk specific set of transforms to be applied to the
# test results to try to normalize them.
COMPONENT_TEST_TRANSFORMS += \
        '-e "s|\(^/usr/gnu/bin/make\).*|\1|" ' 

TPNO=			26217	

# must build tests before using
SYSTEM_TEST_TARGET= build $(SYSTEM_TEST_64)
include $(WS_MAKE_RULES)/gnu-component.mk

# Utility executables are intentionally delivered to the 32-bit lib directory.
CONFIGURE_LIBDIR.64 =   $(CONFIGURE_PREFIX)/lib

CONFIGURE_OPTIONS	+=	--infodir=$(CONFIGURE_INFODIR)
CONFIGURE_OPTIONS	+=	--libexecdir=$(CONFIGURE_LIBDIR.$(BITS))

COMPONENT_SYSTEM_TEST_ARGS = AWKPROG=$(USRBINDIR)/gawk

REQUIRED_PACKAGES += library/libsigsegv
REQUIRED_PACKAGES += library/readline
REQUIRED_PACKAGES += shell/ksh93
REQUIRED_PACKAGES += system/library/math
