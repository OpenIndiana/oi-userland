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
#   $WS_TOOLS/perl-integrate-module Perl-Critic
#

BUILD_STYLE = modulebuild

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Perl-Critic
HUMAN_VERSION =			1.156
COMPONENT_REVISION =		1
COMPONENT_SUMMARY =		Critique Perl source code for best-practices.
COMPONENT_CPAN_AUTHOR =		PETDANCE
COMPONENT_ARCHIVE_HASH =	\
	sha256:572a7c8758ba1c0ab6daf0bd40297c4f0dcf1516f084522df2c2bf04d525e232
COMPONENT_LICENSE =		Artistic-1.0 OR GPL-1.0-or-later
COMPONENT_LICENSE_FILE =	LICENSE

include $(WS_MAKE_RULES)/common.mk

# Normalize out Perl version
COMPONENT_TEST_TRANSFORMS += "-e 's|\(perl5/vendor_perl/\)$(shell echo $(PERL_VERSION) | sed -e 's/\./\\\\./')/|\1\$$(PERLVER)/|'"

# Auto-generated dependencies
PERL_REQUIRED_PACKAGES += library/perl-5/b-keywords
PERL_REQUIRED_PACKAGES += library/perl-5/config-tiny
PERL_REQUIRED_PACKAGES += library/perl-5/exception-class
PERL_REQUIRED_PACKAGES += library/perl-5/file-path
PERL_REQUIRED_PACKAGES += library/perl-5/file-temp
PERL_REQUIRED_PACKAGES += library/perl-5/file-which
PERL_REQUIRED_PACKAGES += library/perl-5/getopt-long
PERL_REQUIRED_PACKAGES += library/perl-5/list-someutils
PERL_REQUIRED_PACKAGES += library/perl-5/module-build
PERL_REQUIRED_PACKAGES += library/perl-5/module-pluggable
PERL_REQUIRED_PACKAGES += library/perl-5/parent
PERL_REQUIRED_PACKAGES += library/perl-5/perl-tidy
PERL_REQUIRED_PACKAGES += library/perl-5/pod-parser
PERL_REQUIRED_PACKAGES += library/perl-5/pod-spell
PERL_REQUIRED_PACKAGES += library/perl-5/pod-usage
PERL_REQUIRED_PACKAGES += library/perl-5/ppi
PERL_REQUIRED_PACKAGES += library/perl-5/ppix-quotelike
PERL_REQUIRED_PACKAGES += library/perl-5/ppix-regexp
PERL_REQUIRED_PACKAGES += library/perl-5/ppix-utils
PERL_REQUIRED_PACKAGES += library/perl-5/readonly
PERL_REQUIRED_PACKAGES += library/perl-5/scalar-list-utils
PERL_REQUIRED_PACKAGES += library/perl-5/string-format
PERL_REQUIRED_PACKAGES += library/perl-5/term-ansicolor
PERL_REQUIRED_PACKAGES += library/perl-5/test-simple
PERL_REQUIRED_PACKAGES += library/perl-5/text-parsewords
PERL_REQUIRED_PACKAGES += library/perl-5/version
PERL_REQUIRED_PACKAGES += runtime/perl
TEST_REQUIRED_PACKAGES.perl += library/perl-5/test-simple
