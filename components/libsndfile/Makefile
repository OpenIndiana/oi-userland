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
# Copyright (c) 2011, 2016, Oracle and/or its affiliates. All rights reserved.
#
BUILD_BITS= 64_and_32
COMPILER= gcc
include ../../make-rules/shared-macros.mk

COMPONENT_NAME=		libsndfile
COMPONENT_VERSION=	1.0.27
COMPONENT_PROJECT_URL=	http://www.mega-nerd.com/libsndfile/
COMPONENT_ARCHIVE_HASH=	\
    sha256:a391952f27f4a92ceb2b4c06493ac107896ed6c76be9a613a4731f076d30fac0
COMPONENT_ARCHIVE_URL=	http://www.mega-nerd.com/libsndfile/files/$(COMPONENT_ARCHIVE)
COMPONENT_BUGDB=	library/libsndfile

TPNO=			30616

include $(WS_MAKE_RULES)/common.mk

# Needed to get tests/header_test.c to compile successfully on SPARC.
gcc_XREGS.sparc=	-mapp-regs

# Need to use GNU sed otherwise we get a:
# Error : sfversion <version> and PACKAGE_VERSION <version> don't match."
# failure from the test_wrapper.sh script.
COMPONENT_TEST_ENV +=   PATH="$(GNUBIN):$(PATH)"

COMPONENT_TEST_MASTER = $(COMPONENT_TEST_RESULTS_DIR)/results-all.master

COMPONENT_TEST_TRANSFORMS += \
	'-e "s|\(^SunOS\).*|\1|" ' \
	'-e "s|^.* CC .*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^.* CXX .*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^.* CCLD .*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^.* CXXLD .*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^.*source=.*libtool=no.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^.*DEPDIR=.deps.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^config.status: .*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^.*common.h:.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^.*test_strncpy_crlf.c:.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^.*In file included.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^.*psf_strlcpy_crlf (.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^.*\^.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^.*argument:.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^.*prototype:.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^.*warning:.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^make.*: Nothing to be.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^make.*: Leaving directory.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "s|^make.*: Entering directory.*$$|XXX_REMOVE_XXX|g" ' \
	'-e "/^XXX_REMOVE_XXX$$/d" '

REQUIRED_PACKAGES += codec/flac
REQUIRED_PACKAGES += codec/ogg-vorbis
REQUIRED_PACKAGES += database/sqlite-3
REQUIRED_PACKAGES += system/library/math
