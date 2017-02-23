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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 32
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		hal-cups-utils
COMPONENT_VERSION=	0.6.19
COMPONENT_PROJECT_URL=	http://fedorahosted.org/hal-cups-utils/
COMPONENT_ARCHIVE_HASH=	\
    sha256:f40a7ebd1453d471a8a6bfd8c635708dd739a6160bb661813f936d936ba85618
COMPONENT_ARCHIVE_URL=	http://fedorahosted.org/releases/h/a/hal-cups-utils/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/hal-cups

TPNO=			8957

TEST_TARGET= $(NO_TESTS)
include $(WS_MAKE_RULES)/common.mk

PATCH_LEVEL = 0

CONFIGURE_OPTIONS += --datarootdir=$(ETCDIR)
CONFIGURE_OPTIONS += --libexecdir=$(USRLIBDIR)/hal

# Since we patch Makefile.am, we have to rebuild the autoconf generated files
# Just running automake does not work, since our automake is different from the one
# used by hal-cups-utils maintainer
COMPONENT_PREP_ACTION = ( \
	cd $(@D); \
	ACLOCAL=aclocal-1.11 AUTOMAKE=aclocal-1.11 autoreconf; \
	cd $(SOURCE_DIR); \
	$(PERL) -pi -e 's,^\#!.*?python,\#!$(USED_PYTHON), if $$.==1' systemv/hal_lpadmin ; \
) 

# ASLR disabled until sufficient testing can be performed.
ASLR_MODE= $(ASLR_DISABLE)

REQUIRED_PACKAGES += developer/build/automake-111
REQUIRED_PACKAGES += library/print/cups-libs
REQUIRED_PACKAGES += print/cups
REQUIRED_PACKAGES += system/hal
REQUIRED_PACKAGES += system/library/libdbus
