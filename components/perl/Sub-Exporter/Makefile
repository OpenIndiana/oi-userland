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
# Copyright 2022 Niklas Poslovski
#

BUILD_STYLE=makemaker
BUILD_BITS=32_and_64
include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		Sub-Exporter
COMPONENT_VERSION=	0.988
#COMPONENT_REVISION=	1
COMPONENT_FMRI=		library/perl-5/sub-exporter
COMPONENT_SUMMARY=	Sub::Exporter - a sophisticated exporter for custom-built routines
COMPONENT_CLASSIFICATION=Development/Perl
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.gz
COMPONENT_PROJECT_URL=	https://metacpan.org/pod/Sub::Exporter
COMPONENT_ARCHIVE_HASH=	\
    sha256:23324887d6c590f145702f077d8ca42f1b2f26a3b76f08d66c2c1e21e606040c
COMPONENT_ARCHIVE_URL=	https://cpan.metacpan.org/authors/id/R/RJ/RJBS/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv1, Artistic

# until all perl modules have been rebuilt with 5.34, each module sets
# this manually, before including common.mk
PERL_VERSIONS = 5.22 5.24 5.34
PERL_64_ONLY_VERSIONS = 5.24 5.34

include $(WS_MAKE_RULES)/common.mk

#
# use the results for each perl version
#
COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-$(PERL_VERSION).master

#
# filter out all output up to and including the test_harness line
# filter out timing information and anything else that varies between builds
#
COMPONENT_TEST_TRANSFORMS += \
	'-e "1,/test_harness/d"' \
	'-e "s/,  *[0-9]* wallclock.*//"'

# Manually added dependencies
REQUIRED_PACKAGES += library/perl-5/data-optlist-522
REQUIRED_PACKAGES += library/perl-5/data-optlist-524
REQUIRED_PACKAGES += library/perl-5/data-optlist-534
REQUIRED_PACKAGES += library/perl-5/params-util-522
REQUIRED_PACKAGES += library/perl-5/params-util-524
REQUIRED_PACKAGES += library/perl-5/params-util-534
REQUIRED_PACKAGES += library/perl-5/sub-install-522
REQUIRED_PACKAGES += library/perl-5/sub-install-524
REQUIRED_PACKAGES += library/perl-5/sub-install-534


# Auto-generated dependencies
REQUIRED_PACKAGES += runtime/perl-522
REQUIRED_PACKAGES += runtime/perl-524
REQUIRED_PACKAGES += runtime/perl-534
