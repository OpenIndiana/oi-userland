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
# Copyright (c) 2019, Michal Nowak
#

BUILD_BITS=		32_and_64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		autogen
COMPONENT_VERSION=	5.18.16
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/autogen/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:e23c5bbd0ac83079ae2ef6eb3fd1948fecce718ac853025607a3ab0395538406
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/autogen/rel$(COMPONENT_VERSION)/$(COMPONENT_ARCHIVE)

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION= (cd $(@D) && autoreconf -I config -fi)

# build target is incorrect without this 
COMPONENT_PRE_CONFIGURE_ACTION =        ($(CLONEY) $(SOURCE_DIR) $(@D))

# built in SFW with gcc and builds cleanly now only with gcc
COMPILER = gcc

# strip the environment or install target fails
ENV +=	-i

CONFIGURE_OPTIONS += --disable-dependency-tracking

# Replace all occurrences of "echo" with "/usr/gnu/bin/echo" in the two
# scripts used by autogen that munge the man and mdoc output. This prevents
# bogus conversions (like "\f" -> Control-L) happening.
#
# Adjust "tr" to "/usr/gnu/bin/tr" in the autoopts vendor.test.
# These changes now allow the autoopts tests to successfully complete.
#
# Replace a GNU-specifix option for mktemp.
COMPONENT_POST_UNPACK_ACTION = \
	$(CHMOD) -R u+w $(SOURCE_DIR) ; \
	$(GSED) -i -e 's|echo|/usr/gnu/bin/echo|' \
		$(SOURCE_DIR)/autoopts/tpl/texi2mdoc.sh ; \
	$(GSED) -i -e 's| tr | /usr/gnu/bin/tr |' \
		$(SOURCE_DIR)/autoopts/test/vendor.test ; \
	$(GSED) -i -e 's|mktemp --suffix=|g&|' $(SOURCE_DIR)/agen5/mk-stamps.sh \
		$(SOURCE_DIR)/build-aux/run-ag.sh \
		$(SOURCE_DIR)/config/mk-shdefs.in ;

CONFIGURE_ENV.64 += PATH=/usr/bin/$(MACH64):/usr/bin

AUTOGEN_PATH.32 = $(PATH.illumos)
AUTOGEN_PATH.64 = /usr/bin/$(MACH64):$(PATH.illumos)
PERL.32 = $(PERL.5.22)
PERL.64 = $(PERL.5.24)
COMPONENT_BUILD_ENV += PATH=$(AUTOGEN_PATH.$(BITS)) PERL=$(PERL.$(BITS))
COMPONENT_INSTALL_ENV += PATH=$(AUTOGEN_PATH.$(BITS)) PERL=$(PERL.$(BITS))
COMPONENT_TEST_ENV += PATH=$(AUTOGEN_PATH.$(BITS)) PERL=$(PERL.$(BITS))

COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/TOTAL/p" ' \
	'-e "/SKIP/p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/ERROR/p" '

REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += file/gnu-coreutils
# Auto-generated dependencies
REQUIRED_PACKAGES += library/guile
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
