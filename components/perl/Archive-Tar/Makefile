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
#   $WS_TOOLS/perl-integrate-module Archive-Tar
#

BUILD_STYLE = makemaker

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME =		Archive-Tar
HUMAN_VERSION =			3.06
COMPONENT_SUMMARY =		Manipulates TAR archives
COMPONENT_CPAN_AUTHOR =		BINGOS
COMPONENT_ARCHIVE_HASH =	\
	sha256:107d18917695d9d96834308e004ec463c24f459a0ed72bee7722749c1c625ad7
COMPONENT_LICENSE =		Artistic-1.0-Perl OR GPL-1.0-or-later

include $(WS_MAKE_RULES)/common.mk

# The t/02_methods.t test expects there are no symlinks
CLONEY_MODE = copy

# Auto-generated dependencies
REQUIRED_PACKAGES.perl += library/perl-5/extutils-makemaker
REQUIRED_PACKAGES.perl += library/perl-5/io-compress
REQUIRED_PACKAGES.perl += library/perl-5/io-compress-lzma
REQUIRED_PACKAGES.perl += library/perl-5/io-zlib
REQUIRED_PACKAGES.perl += library/perl-5/test-harness
REQUIRED_PACKAGES.perl += library/perl-5/test-simple
REQUIRED_PACKAGES.perl += runtime/perl
