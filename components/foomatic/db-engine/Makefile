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

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		foomatic-db-engine
COMPONENT_VERSION=	4.0.13
COMPONENT_SUMMARY=	Foomatic Database Engine
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
	sha256:b5c89027aa26967d2e6db62e2af7db0c4039d2480d4fbf2476a6ddcf609a5faf
COMPONENT_ARCHIVE_URL=	https://www.openprinting.org/download/foomatic/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://openprinting.github.io/projects/02-foomatic/
COMPONENT_FMRI=		print/cups/filter/foomatic-db-engine
COMPONENT_CLASSIFICATION=	System/Printing
COMPONENT_LICENSE=	GPL-2.0-only
COMPONENT_LICENSE_FILE=	COPYING

TEST_TARGET = $(NO_TESTS)

include $(WS_MAKE_RULES)/common.mk

# Force known Perl version
CONFIGURE_OPTIONS += PERL=$(PERL)

# configure is not happy with /usr/bin/file and asks for astron file
CONFIGURE_OPTIONS += FILEUTIL=/usr/bin/gfile

# the build system does not support building outside of the source tree
COMPONENT_PRE_CONFIGURE_ACTION += $(CLONEY) $(SOURCE_DIR) $(@D) ;

# setup perl build
COMPONENT_PRE_CONFIGURE_ACTION += cd $(@D)/lib ; $(PERL) Makefile.PL ;

# Defaults.pm is not built by the perl module, but by external utility, so it's in wrong place
COMPONENT_POST_INSTALL_ACTION += \
	$(INSTALL) $(@D)/lib/Foomatic/Defaults.pm $(PROTOUSRDIR)/perl5/vendor_perl/$(PERL_VERSION)/Foomatic ;

# Convert absolute symlink to relative one
COMPONENT_POST_INSTALL_ACTION += \
	$(RM) $(PROTOUSRLIBDIR)/cups/driver/foomatic ; \
	$(SYMLINK) ../../../bin/foomatic-ppdfile $(PROTOUSRLIBDIR)/cups/driver/foomatic ;

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += runtime/perl
REQUIRED_PACKAGES += library/libxml2
REQUIRED_PACKAGES += shell/bash
REQUIRED_PACKAGES += system/library
