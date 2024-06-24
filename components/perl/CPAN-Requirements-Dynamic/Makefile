#
# This file and its contents are supplied under the terms of the
# Common Development and Distribution License ("CDDL"), version 1.0.
# You may only use this file in accordance with the terms of version
# 1.0 of the CDDL.
#
# A full copy of the text of the CDDL should have accompanied this
# source.  A copy of the CDDL is also available via the Internet at
# http://www.illumos.org/license/CDDL.
#

#
# This file was automatically generated using the following command:
#   $WS_TOOLS/perl-integrate-module CPAN::Requirements::Dynamic
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =		CPAN::Requirements::Dynamic
HUMAN_VERSION =			0.001
COMPONENT_SUMMARY =		CPAN::Requirements::Dynamic - Dynamic prerequisites in meta files
COMPONENT_CPAN_AUTHOR =		LEONT
COMPONENT_ARCHIVE_HASH =	\
	sha256:4b590e712b9aca680c3631855ee16a50b84fa0227c362e13b237a75a01489ef5
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

# CPAN::Meta::Requirements >= 2.143 is needed.  The CPAN::Meta::Requirements
# module is part of Perl core, however Perl <= 5.38 contains version 2.140 only.
PERL_VERSIONS := $(filter-out 5.36 5.38, $(PERL_VERSIONS))

include $(WS_MAKE_RULES)/common.mk

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-config
PERL_REQUIRED_PACKAGES += library/perl-5/extutils-hascompiler
PERL_REQUIRED_PACKAGES += runtime/perl
