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
# Copyright (c) 2013, 2017, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2020, Aurelien Larcher
# Copyright (c) 2022 Tim Mooney.  All rights reserved.
#
BUILD_BITS=32_and_64
BUILD_STYLE=makemaker
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		XML-NamespaceSupport
COMPONENT_VERSION=	1.12
HUMAN_VERSION=		1.12
COMPONENT_REVISION=	1
COMPONENT_FMRI=		library/perl-5/xml-namespacesupport
COMPONENT_CLASSIFICATION=Development/Perl
COMPONENT_SRC=		$(COMPONENT_NAME)-$(HUMAN_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_ARCHIVE_HASH=	\
    sha256:47e995859f8dd0413aa3f22d350c4a62da652e854267aa0586ae544ae2bae5ef
COMPONENT_ARCHIVE_URL=	https://cpan.metacpan.org/authors/id/P/PE/PERIGRIN/$(COMPONENT_ARCHIVE)
COMPONENT_PROJECT_URL=	https://metacpan.org/pod/XML::NamespaceSupport
COMPONENT_LICENSE=	Artistic
COMPONENT_LICENSE_FILE=	xml-namespacesupport.license

# until all perl modules have been rebuilt with 5.34, each module sets
# this manually, before including common.mk
PERL_VERSIONS = 5.22 5.24 5.34
PERL_64_ONLY_VERSIONS = 5.24 5.34

include $(WS_MAKE_RULES)/common.mk

# man pages go in the common area
COMPONENT_INSTALL_ENV += INSTALLVENDORMAN3DIR=$(USRSHAREMAN3DIR)

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master
COMPONENT_TEST_TRANSFORMS += \
	'-e "/^PERL_DL_NONLAZY/d" ' \
	'-e "s|\(^Files=1,\sTests=49\).*|\1|" '

# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
