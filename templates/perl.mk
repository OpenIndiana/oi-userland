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
# Copyright 2022 <contributor>
#

BUILD_STYLE = makemaker
USE_COMMON_TEST_MASTER = yes

include ../../../make-rules/shared-macros.mk

COMPONENT_PERL_MODULE =
HUMAN_VERSION =
COMPONENT_SUMMARY =
COMPONENT_CPAN_AUTHOR =
COMPONENT_ARCHIVE_HASH =
COMPONENT_LICENSE =

include $(WS_MAKE_RULES)/common.mk

# Build dependencies
PERL_REQUIRED_PACKAGES +=
REQUIRED_PACKAGES +=

