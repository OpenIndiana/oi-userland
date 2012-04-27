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
# Copyright (c) 2011, 2012, Oracle and/or its affiliates. All rights reserved.
#

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		XML-Simple
COMPONENT_VERSION=	2.18
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:a54967c188cda3e20f496c83be4de3f1740eeaa83c0380712ecd969ad8766826
COMPONENT_ARCHIVE_URL=	http://www.cpan.org/authors/id/G/GR/GRANTM/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	http://search.cpan.org/~grantm/

include $(WS_TOP)/make-rules/prep.mk
include $(WS_TOP)/make-rules/ips.mk
include $(WS_TOP)/make-rules/makemaker.mk

# man pages go in the common area
COMPONENT_INSTALL_ENV += INSTALLVENDORMAN3DIR=$(USRSHAREMAN3DIR)

# look in XML::Parser's proto area
PERL_FLAGS = -I$(COMPONENT_DIR)/../xml-parser/build/prototype/$(MACH)/usr/perl5/vendor_perl/$(PERL_VERSION)/$(PERL_ARCH)


build:		$(BUILD_32)

install:	$(INSTALL_32)

# The tests with perl 5.8.4 are clean.
# Perl 5.12.3 has lots of failures and issues.
COMPONENT_TEST_TARGETS = test
test:		$(TEST_32)

# special targets; need xml-parser built and installed first
../xml-parser/build/5.8.4/.installed ../xml-parser/build/5.12/.installed:
	(cd ../xml-parser ; $(GMAKE) install)

$(BUILD_32):	../xml-parser/build/5.8.4/.installed \
		../xml-parser/build/5.12/.installed

BUILD_PKG_DEPENDENCIES =	$(BUILD_TOOLS)

include $(WS_TOP)/make-rules/depend.mk
