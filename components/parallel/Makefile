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
# Copyright (c) 2012, 2016, Oracle and/or its affiliates. All rights reserved.
#

include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		parallel
COMPONENT_VERSION=	20160222
# A leading "0." is included to make it easier to upgrade the package, should
# the maintainers decide to go to a more standard version numbering system.
IPS_COMPONENT_VERSION=  0.2016.2.22
COMPONENT_PROJECT_URL=	http://www.gnu.org/software/parallel/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.bz2
COMPONENT_ARCHIVE_HASH=	\
    sha256:8dfbe539036a6ff02f9f542751e8621f42d285b3c9a7d9245042a6cc6ddc55ea
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/$(COMPONENT_NAME)/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	utility/parallel

TPNO=			27217

include $(WS_MAKE_RULES)/prep.mk
include $(WS_MAKE_RULES)/configure.mk
include $(WS_MAKE_RULES)/ips.mk

# Set PATH to find the correct pod2man, so that the man pages can be
# automatically generated
COMPONENT_BUILD_ENV += \
	PATH="/usr/bin:/usr/gnu/bin:/usr/perl5/$(PERL_VERSION)/bin"

# Adjust the '#!/usr/bin/env perl' and '#!/usr/bin/perl' at the beginning of
# the Perl scripts to use '#!/usr/perl5/$(PERL_VERSION)/bin/perl'
COMPONENT_POST_INSTALL_ACTION += \
	$(GSED) -i -e 's?/usr/bin/perl?/usr/perl5/$(PERL_VERSION)/bin/perl?' \
		$(PROTOUSRBINDIR64)/niceload;
COMPONENT_POST_INSTALL_ACTION += \
	$(GSED) -i -e \
		's?/usr/bin/env perl?/usr/perl5/$(PERL_VERSION)/bin/perl?' \
		$(PROTOUSRBINDIR64)/parallel;
COMPONENT_POST_INSTALL_ACTION += \
	$(GSED) -i -e 's?/usr/bin/perl?/usr/perl5/$(PERL_VERSION)/bin/perl?' \
		$(PROTOUSRBINDIR64)/sql;

ASLR_MODE = $(ASLR_NOT_APPLICABLE)

configure:	$(CONFIGURE_64)

build:		$(BUILD_64)

install:	$(INSTALL_64)

test:		$(NO_TESTS)

system-test:    $(NO_TESTS)


REQUIRED_PACKAGES += $(PERL_PKG)
REQUIRED_PACKAGES += shell/which
REQUIRED_PACKAGES += system/core-os
