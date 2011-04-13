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
# Copyright (c) 2011, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		hal-cups-utils
COMPONENT_VERSION=	0.6.19
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	sha1:14f79f1e8614d4f4a96d9a910ed79f554fbbaaa0
COMPONENT_ARCHIVE_URL=	http://fedorahosted.org/releases/h/a/hal-cups-utils/$(COMPONENT_ARCHIVE)

include ../../make-rules/prep.mk
include ../../make-rules/configure.mk
include ../../make-rules/ips.mk

PATCH_LEVEL = 0
USED_PYTHON=$(PYTHON.2.6.32)

CONFIGURE_ENV += PYTHON=$(USED_PYTHON)

CONFIGURE_OPTIONS += --datarootdir=$(ETCDIR)
CONFIGURE_OPTIONS += --libexecdir=$(USRLIBDIR)/hal

# Since we patch Makefile.am, we have to rebuild the autoconf generated files
# Just running automake does not work, since our automake is different from the one
# used by hal-cups-utils maintainer
COMPONENT_PREP_ACTION = ( \
	cd $(@D); \
	ACLOCAL=$(ACLOCAL) AUTOMAKE=$(AUTOMAKE) autoreconf; \
	cd $(SOURCE_DIR); \
	$(PERL) -pi -e 's,^\#!.*?python,\#!$(USED_PYTHON), if $$.==1' systemv/hal_lpadmin ; \
) 

build:		$(BUILD_32)

install:	$(INSTALL_32)

test:		$(NO_TESTS)

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include ../../make-rules/depend.mk
