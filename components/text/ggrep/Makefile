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
# Copyright (c) 2011, 2017, Oracle and/or its affiliates. All rights reserved.
# Copyright (c) 2020, Michal Nowak
#

BUILD_BITS=		64

include ../../../make-rules/shared-macros.mk

COMPONENT_NAME=		grep
COMPONENT_VERSION=	3.4
COMPONENT_FMRI=		text/gnu-grep
COMPONENT_SUMMARY= 	GNU grep utilities
COMPONENT_CLASSIFICATION= Applications/System Utilities
COMPONENT_PROJECT_URL=	http://gnu.org/software/grep/
COMPONENT_SRC=		$(COMPONENT_NAME)-$(COMPONENT_VERSION)
COMPONENT_ARCHIVE=	$(COMPONENT_SRC).tar.xz
COMPONENT_ARCHIVE_HASH=	\
	sha256:58e6751c41a7c25bfc6e9363a41786cff3ba5709cf11d5ad903cf7cce31cc3fb
COMPONENT_ARCHIVE_URL=	http://ftp.gnu.org/gnu/grep/$(COMPONENT_ARCHIVE)
COMPONENT_LICENSE=	GPLv3, FDLv1.3

include $(WS_MAKE_RULES)/common.mk

COMPONENT_PREP_ACTION = ( cd $(@D) && \
				aclocal -I m4 && \
				autoheader && \
				automake --add-missing --copy --force )

PATH=$(PATH.gnu)

# Needed for "gmake test" to work.
# SHELLOPTS is exported via make-rules/shared-macros.mk,
# causing the braceexpand option to be set.
# This option causes "$1: unbound variable" errors during the check-TESTS,
# and the gnulib-tests don't even run at all.
# Note that the below unexports SHELLOPTS, even for targets
# other than "test." 
unexport SHELLOPTS

# Test transforms retain only relevant results output.
COMPONENT_TEST_TRANSFORMS += \
	'-n ' \
	'-e "/TOTAL/p" ' \
	'-e "/SKIP/p" ' \
	'-e "/PASS/p" ' \
	'-e "/FAIL/p" ' \
	'-e "/ERROR/p" '

# Since version 3.4, GNU grep is needed for build.
REQUIRED_PACKAGES += text/gnu-grep
# Testsuite requirements
REQUIRED_PACKAGES += locale/tr
REQUIRED_PACKAGES += locale/ru-extra
# Auto-generated dependencies
REQUIRED_PACKAGES += library/libsigsegv
REQUIRED_PACKAGES += library/pcre
REQUIRED_PACKAGES += SUNWcs
REQUIRED_PACKAGES += system/library
